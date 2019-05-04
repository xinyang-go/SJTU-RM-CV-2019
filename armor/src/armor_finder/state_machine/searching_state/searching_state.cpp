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
    static cv::Mat src_gray, src_bin;
    if(src.type() == CV_8UC3){
        cvtColor(src, src_gray, CV_BGR2GRAY);
    }else if(src.type() == CV_8UC1){
        src_gray = src.clone();
    }

    std::vector<std::vector<cv::Point> > light_contours;
    cv::findContours(src_gray, light_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
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

double centerDistance(const cv::Rect2d &box){
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
            min_x = fmin(rect_left.x, rect_right.x);
            max_x = fmax(rect_left.x + rect_left.width, rect_right.x + rect_right.width);
            min_y = fmin(rect_left.y, rect_right.y) - 3;
            max_y = fmax(rect_left.y + rect_left.height, rect_right.y + rect_right.height) + 3;
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
    cv::Mat split, src_bin;
    LightBlobs light_blobs, light_blobs_, light_blobs_real;
    std::vector<cv::Rect2d> armor_boxes, boxes_number[10];
    armor_box = cv::Rect2d(0,0,0,0);

    cv::cvtColor(src, src_gray, CV_BGR2GRAY);
//    pipelineLightBlobPreprocess(src_gray);
    cv::threshold(src_gray, src_bin, 120, 255, CV_THRESH_BINARY);
    if(!findLightBlobs(src_bin, light_blobs)){
        return false;
    }
    if(show_light_blobs){
        showContours("blobs", src_bin, light_blobs);
        cv::waitKey(1);
    }

    imageColorSplit(src, split, enemy_color);
    imagePreProcess(split);
    cv::threshold(split, src_bin, 120, 255, CV_THRESH_BINARY);
    if(!findLightBlobs(src_bin, light_blobs_)){
        return false;
    }
    if(show_light_blobs){
        showContours("blobs_", src_bin, light_blobs_);
        cv::waitKey(1);
    }

    if(!judge_light_color(light_blobs, light_blobs_, light_blobs_real)){
        return false;
    }
    if(show_light_blobs){
        showContours("blobs_real", src, light_blobs_real);
        cv::waitKey(1);
    }

    if(!findArmorBoxes(light_blobs_real, armor_boxes)){
        return false;
    }
    if(show_armor_boxes){
        showArmorBoxVector("boxes", split, armor_boxes);
        cv::waitKey(1);
    }
    if(classifier){
        for(auto box : armor_boxes){
            cv::Mat roi = src(box).clone();
            cv::resize(roi, roi, cv::Size(48, 36));
            int c = classifier(roi);
            if(c){
                boxes_number[c-1].emplace_back(box);
            }
        }
        for(auto box : boxes_number){
            if(!box.empty()){
                armor_box = box[0];
            }
        }

        if(armor_box == cv::Rect2d(0,0,0,0)){
            return false;
        }
        if(show_armor_boxes){
            showArmorBoxClass("class", src, boxes_number);
        }
    }else{
        armor_box = armor_boxes[0];
    }
    if(split.size() == cv::Size(320, 240)){
        armor_box.x *= 2;
        armor_box.y *= 2;
        armor_box.width *= 2;
        armor_box.height *= 2;
    }
    return sendBoxPosition();
}
