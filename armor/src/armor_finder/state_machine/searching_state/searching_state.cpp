//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>
#include <opencv2/highgui.hpp>
#include "image_process/image_process.h"
#include <log.h>
#include <show_images/show_images.h>

#include <options/options.h>

typedef std::vector<LightBlob> LightBlobs;

static double lw_rate(const cv::RotatedRect &rect){
    return (rect.size.height > rect.size.width)?
           (rect.size.height / rect.size.width):
           (rect.size.width / rect.size.height);
}

static bool isValidLightBlob(const cv::RotatedRect &rect){
    return (lw_rate(rect) > 1.2) &&
           ((rect.size.width * rect.size.height) < 3000) &&
           ((rect.size.width * rect.size.height) > 1);
}

static void pipelineLightBlobPreprocess(cv::Mat &src) {
    src -= 150;
    src *= 3.5;
    src -= 150;
    src *= 3.5;
}

static bool findLightBlobs(const cv::Mat &src, LightBlobs &light_blobs) {
    static cv::Mat src_bin;

    cv::threshold(src, src_bin, 80, 255, CV_THRESH_BINARY);
    std::vector<std::vector<cv::Point> > light_contours;
    cv::findContours(src_bin, light_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (auto &light_contour : light_contours) {
        cv::RotatedRect rect = cv::minAreaRect(light_contour);
        if(isValidLightBlob(rect)){
            light_blobs.emplace_back(rect);
        }
    }
    return light_blobs.size() >= 2;
}

bool angelJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {

    float angle_i = light_blob_i.rect.size.width > light_blob_i.rect.size.height ? light_blob_i.rect.angle :
                    light_blob_i.rect.angle - 90;
    float angle_j = light_blob_j.rect.size.width > light_blob_j.rect.size.height ? light_blob_j.rect.angle :
                    light_blob_j.rect.angle - 90;
    return abs(angle_i-angle_j)<10;
}
bool heightJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    cv::Point2f centers = light_blob_i.rect.center - light_blob_j.rect.center;

    return abs(centers.y)<30;
}

bool lengthJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    double side_length;
    cv::Point2f centers = light_blob_i.rect.center - light_blob_j.rect.center;
    side_length = sqrt(centers.ddot(centers));
//    std::cout << "side:" << side_length << " length:" << light_blob_i.length  << std::endl;
    return (side_length / light_blob_i.length < 6 && side_length / light_blob_i.length > 0.5);
}

bool lengthRatioJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
//    std::cout << "i:" << light_blob_i.length << " j:" << light_blob_j.length << std::endl;
    return (light_blob_i.length / light_blob_j.length < 2
            && light_blob_i.length / light_blob_j.length > 0.5);
}

bool isCoupleLight(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    if(!lengthRatioJudge(light_blob_i, light_blob_j)){
//        std::cout << "lengthRatioJudge" << std::endl;
        return false;
    }
    if(!lengthJudge(light_blob_i, light_blob_j)){
//        std::cout << "lengthJudge" << std::endl;
        return false;
    }
    if(!heightJudge(light_blob_i, light_blob_j)){
//        std::cout << "heightJudge" << std::endl;
        return false;
    }
    if(!angelJudge(light_blob_i, light_blob_j)){
//        std::cout << "angelJudge" << std::endl;
        return false;
    }
    return true;
    return lengthRatioJudge(light_blob_i, light_blob_j) &&
           lengthJudge(light_blob_i, light_blob_j) &&
           heightJudge(light_blob_i, light_blob_j) &&
           angelJudge(light_blob_i, light_blob_j);

}

double centerDistance(cv::Rect2d box){
    double dx = box.x-box.width/2 - 320;
    double dy = box.y-box.height/2 - 240;
    return dx*dx + dy*dy;
}

static bool findArmorBoxes(LightBlobs &light_blobs, std::vector<cv::Rect2d> &armor_boxes) {
    for (int i = 0; i < light_blobs.size() - 1; ++i) {
        for (int j = i + 1; j < light_blobs.size(); ++j) {
            if (!isCoupleLight(light_blobs.at(i), light_blobs.at(j))) {
                continue;
            }
            cv::Rect2d rect_left = light_blobs.at(static_cast<unsigned long>(i)).rect.boundingRect();
            cv::Rect2d rect_right = light_blobs.at(static_cast<unsigned long>(j)).rect.boundingRect();
            double min_x, min_y, max_x, max_y;
            min_x = fmin(rect_left.x, rect_right.x) - 5;
            max_x = fmax(rect_left.x + rect_left.width, rect_right.x + rect_right.width) + 5;
            min_y = fmin(rect_left.y, rect_right.y) - 5;
            max_y = fmax(rect_left.y + rect_left.height, rect_right.y + rect_right.height) + 5;
            if (min_x < 0 || max_x > 640 || min_y < 0 || max_y > 480) {
                continue;
            }
            armor_boxes.emplace_back(cv::Rect2d(min_x, min_y, max_x - min_x, max_y - min_y));
        }
    }
    if(armor_boxes.empty()){
        return false;
    }
    sort(armor_boxes.begin(), armor_boxes.end(), [](cv::Rect2d box1, cv::Rect2d box2)->bool{
        return centerDistance(box1) < centerDistance(box2);
    });
    return true;
}

bool judge_light_color(std::vector<LightBlob> &light, std::vector<LightBlob> &color, std::vector<LightBlob> &result) {
    for (auto &i:color) {
        for (auto &j:light) {
            cv::Rect2d a = i.rect.boundingRect2f();
            cv::Rect2d b = j.rect.boundingRect2f();
            cv::Rect2d ab = a & b;
            if (ab.area() / fmin(a.area(), b.area()) >= 0.2) {
                result.emplace_back(j);
                break;
            }
        }
    }
    return !result.empty();
}

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    cv::Mat split, pmsrc=src.clone();
    LightBlobs light_blobs, pm_light_blobs, light_blobs_real;
    std::vector<cv::Rect2d> armor_boxes;

//    cv::resize(src, pmsrc, cv::Size(320, 240));
    imageColorSplit(src, split, enemy_color);
    imagePreProcess(split);
    cv::resize(split, split, cv::Size(640, 480));
//    pipelineLightBlobPreprocess(pmsrc);
//    if(!findLightBlobs(pmsrc, pm_light_blobs)){
//        return false;
//    }
    if(!findLightBlobs(split, light_blobs)){
        return false;
    }
//    if(!judge_light_color(light_blobs, pm_light_blobs, light_blobs_real)){
//        return false;
//    }
    if(show_light_blobs){
        showContours("blobs", split, light_blobs);
//        showContours("pm blobs", pmsrc, pm_light_blobs);
//        showContours("blobs real", src, light_blobs_real);
        cv::waitKey(1);
    }
    if(!findArmorBoxes(light_blobs, armor_boxes)){
        return false;
    }
    armor_box = armor_boxes[0];
    if(show_armor_boxes){
        showArmorBoxVector("boxes", split, armor_boxes);
        cv::waitKey(1);
    }
    if(split.size() == cv::Size(320, 240)){
        armor_box.x *= 2;
        armor_box.y *= 2;
        armor_box.width *= 2;
        armor_box.height *= 2;
    }
    
    return sendBoxPosition();
}
