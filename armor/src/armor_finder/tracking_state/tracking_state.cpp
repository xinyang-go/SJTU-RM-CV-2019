//
// Created by xinyang on 19-3-27.
//
#include <log.h>
#include <options.h>
#include <armor_finder/armor_finder.h>
#include <show_images/show_images.h>

bool ArmorFinder::stateTrackingTarget(cv::Mat &src) {
    auto pos = target_box.rect;
    if(!tracker->update(src, pos)){
        target_box = ArmorBox();
        return false;
    }
    if((pos & cv::Rect2d(0, 0, 640, 480)) != pos){
        target_box = ArmorBox();
        return false;
    }

    cv::Rect2d bigger_rect;

    bigger_rect.x = pos.x - pos.width / 2.0;
    bigger_rect.y = pos.y - pos.height / 2.0;
    bigger_rect.height = pos.height * 2;
    bigger_rect.width  = pos.width * 2;
    bigger_rect &= cv::Rect2d(0, 0, 640, 480);

    if(show_armor_box)
        showTrackSearchingPos("track", src, bigger_rect);

    cv::Mat roi = src(bigger_rect).clone();

    ArmorBox box;
    if(findArmorBox(roi, box)) {
        target_box = box;
        target_box.rect.x += bigger_rect.x;
        target_box.rect.y += bigger_rect.y;
        for(auto &blob : target_box.light_blobs){
            blob.rect.center.x += bigger_rect.x;
            blob.rect.center.y += bigger_rect.y;
        }
        tracker = TrackerToUse::create();
        tracker->init(src, target_box.rect);
    }else{
//        roi = src(pos).clone();
//        if(classifier){
//            cv::resize(roi, roi, cv::Size(48, 36));
//            if(classifier(roi) == 0){
//                target_box = ArmorBox();
//                return false;
//            }
//        }else{
//            cv::Mat roi_gray;
//            cv::cvtColor(roi, roi_gray, CV_RGB2GRAY);
//            cv::threshold(roi_gray, roi_gray, 180, 255, cv::THRESH_BINARY);
//            contour_area = cv::countNonZero(roi_gray);
//            if(abs(cv::countNonZero(roi_gray) - contour_area) > contour_area * 0.3){
//                target_box = ArmorBox();
//                return false;
//            }
//        }
//        target_box.rect = pos;
//        target_box.light_blobs.clear();
        target_box = ArmorBox();
        return false;
    }
    return true;
}
