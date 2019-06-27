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
    return rect.size.height>rect.size.width ?
    rect.size.height / rect.size.width :
    rect.size.width / rect.size.height ;
}

bool rectangleContainPoint(cv::RotatedRect rectangle, cv::Point2f point)
{
    //转化为轮廓
    cv::Point2f corners[4];
    rectangle.points(corners);
    cv::Point2f *lastItemPointer = (corners+sizeof corners/sizeof corners[0]);
    vector<cv::Point2f> contour(corners,lastItemPointer);
    //判断
    double indicator = pointPolygonTest(contour,point,true);
    return indicator >= 0;
}
/// Todo: 下面的函数可以有性能优化，暂时未做。
static double nonZeroRateOfRotateRect(const cv::Mat &bin, const cv::RotatedRect &rorect){
    auto rect = rorect.boundingRect();
    if(rect.x < 0 || rect.y < 0 || rect.x+rect.width > bin.cols || rect.y+rect.height > bin.rows){
//        cout << "break" << endl;
        return 0;
    }
    auto roi=bin(rect);
    int cnt=0;
    for(int r=0; r<roi.rows; r++){
        for(int c=0; c<roi.cols; c++){
            if(rectangleContainPoint(rorect, cv::Point(c+rect.x, r+rect.y))){
                if(roi.at<uint8_t>(r, c)){
                    cnt++;
                }
            }
        }
    }
    return double(cnt) / rorect.size.area();
}

static bool isValidLightBlob(const cv::Mat &bin, const cv::RotatedRect &rect){
    return (lw_rate(rect) > 1.5) &&
//           (rect.size.width*rect.size.height < 3000) &&
           (rect.size.width*rect.size.height > 1) &&
           (nonZeroRateOfRotateRect(bin, rect) > 0.8);
}

static void pipelineLightBlobPreprocess(cv::Mat &src) {
    src -= 150;
    src *= 3.5;
    src -= 150;
    src *= 3.5;
}

static bool findLightBlobs(const cv::Mat &src, LightBlobs &light_blobs) {
    static cv::Mat src_gray;
    if(src.type() == CV_8UC3){
        cvtColor(src, src_gray, CV_BGR2GRAY);
    }else if(src.type() == CV_8UC1){
        src_gray = src.clone();
    }

    std::vector<std::vector<cv::Point> > light_contours;
    cv::findContours(src_gray, light_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    for (auto &light_contour : light_contours) {
        cv::RotatedRect rect = cv::minAreaRect(light_contour);
        if(isValidLightBlob(src_gray, rect)){
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

bool isCoupleLight(const LightBlob &light_blob_i, const LightBlob &light_blob_j, uint8_t enemy_color) {
    if(light_blob_i.BlobColor != enemy_color || light_blob_j.BlobColor != enemy_color){
        return false;
    }
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

static bool findArmorBoxes(LightBlobs &light_blobs, std::vector<cv::Rect2d> &armor_boxes, uint8_t enemy_color) {
    for (int i = 0; i < light_blobs.size() - 1; ++i) {
        for (int j = i + 1; j < light_blobs.size(); ++j) {
            if (!isCoupleLight(light_blobs.at(i), light_blobs.at(j), enemy_color)) {
                continue;
            }
            cv::Rect2d rect_left = light_blobs.at(static_cast<unsigned long>(i)).rect.boundingRect();
            cv::Rect2d rect_right = light_blobs.at(static_cast<unsigned long>(j)).rect.boundingRect();
            double min_x, min_y, max_x, max_y;
            min_x = fmin(rect_left.x, rect_right.x) - 4;
            max_x = fmax(rect_left.x + rect_left.width, rect_right.x + rect_right.width) + 4;
            min_y = fmin(rect_left.y, rect_right.y) - 4;
            max_y = fmax(rect_left.y + rect_left.height, rect_right.y + rect_right.height) + 4;
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

void get_blob_color(const cv::Mat &src, std::vector<LightBlob> &blobs) {
    for(auto &blob : blobs){
        auto region = blob.rect.boundingRect();
        region.x -= fmax(2, region.width * 0.1);
        region.y -= fmax(2, region.height * 0.05);
        region.width += 2 * fmax(2, region.width * 0.1);
        region.height += 2 * fmax(2, region.height * 0.05);
        region &= cv::Rect(0, 0, 640, 480);
        cv::Mat roi = src(region);
        long long int red_cnt = 0, blue_cnt = 0;
        for(int row=0; row<roi.rows; row++){
            for(int col=0; col<roi.cols; col++){
                red_cnt += roi.at<cv::Vec3b>(row, col)[2];
                blue_cnt += roi.at<cv::Vec3b>(row, col)[0];
            }
        }
        if(red_cnt > blue_cnt){
            blob.BlobColor = BLOB_RED;
        }else{
            blob.BlobColor = BLOB_BLUE;
        }
    }
}

int prior_red[] = {0, 2, 3, 4, 1, 5, 7, 8, 9, 6};
int prior_blue[]= {5, 7, 8, 9, 6, 0, 2, 3, 4, 1};

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    cv::Mat split, src_bin;
    LightBlobs light_blobs, light_blobs_, light_blobs_real;
    std::vector<cv::Rect2d> armor_boxes, boxes_number[10];
    armor_box = cv::Rect2d(0,0,0,0);

    cv::cvtColor(src, src_gray, CV_BGR2GRAY);
//    pipelineLightBlobPreprocess(src_gray);
    cv::threshold(src_gray, src_bin, 170, 255, CV_THRESH_BINARY);
//    imshow("gray bin", src_bin);
    if(!findLightBlobs(src_bin, light_blobs)){
        return false;
    }
    if(show_light_blobs){
        showContours("blobs_gray", src_bin, light_blobs);
        cv::waitKey(1);
    }

//    imageColorSplit(src, split, enemy_color);
////    imshow("split123",split);
//    imagePreProcess(split);
////    imshow("split",split);
//    cv::threshold(split, src_bin, 170, 255, CV_THRESH_BINARY);
//    if(!findLightBlobs(src_bin, light_blobs_)){
//        return false;
//    }
//    if(show_light_blobs){
//        showContours("blobs_split", src_bin, light_blobs_);
//        cv::waitKey(1);
//    }
//
//    if(!judge_light_color(light_blobs, light_blobs_, light_blobs_real)){
//        return false;
//    }
    light_blobs_real = light_blobs;
    get_blob_color(src, light_blobs_real);
    if(show_light_blobs){
        showContours("blobs_real", src, light_blobs_real);
        cv::waitKey(1);
    }

    if(!findArmorBoxes(light_blobs_real, armor_boxes, enemy_color)){
        return false;
    }
    if(show_armor_boxes){
        showArmorBoxVector("boxes", src, armor_boxes);
        cv::waitKey(1);
    }
    if(classifier && use_classifier){
        for(auto box : armor_boxes){
            cv::Mat roi = src(box).clone();
            cv::resize(roi, roi, cv::Size(48, 36));
            int c = classifier(roi);
            if(c){
                boxes_number[c-1].emplace_back(box);
            }
        }
        if(enemy_color == ENEMY_BLUE) {
            for(auto id : prior_blue){
                if(!boxes_number[id].empty()){
                    armor_box = boxes_number[id][0];
                    break;
                }
            }
        }else if(enemy_color == ENEMY_RED) {
            for(auto id : prior_red){
                if(!boxes_number[id].empty()){
                    armor_box = boxes_number[id][0];
                    break;
                }
            }
        }else{
            LOGE("enemy_color ERROR!");
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
