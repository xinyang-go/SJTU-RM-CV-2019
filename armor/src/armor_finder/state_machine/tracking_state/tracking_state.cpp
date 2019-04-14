//
// Created by xinyang on 19-3-27.
//
#include <log.h>
#include <armor_finder/armor_finder.h>

bool ArmorFinder::stateTrackingTarget(cv::Mat &src) {
    auto last = armor_box;
    tracker->update(src, armor_box);

    if((armor_box & cv::Rect2d(0, 0, 640, 480)) != armor_box){
        return false;
    }
    cv::Mat roi = src(armor_box);
    threshold(roi, roi, 200, 255, cv::THRESH_BINARY);

    if(abs(cv::countNonZero(roi) - contour_area) > contour_area * 0.3){
        return false;
    }
    return sendBoxPosition();
}
