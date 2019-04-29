//
// Created by xinyang on 19-3-27.
//
#include <log.h>
#include <armor_finder/armor_finder.h>

bool ArmorFinder::stateTrackingTarget(cv::Mat &src) {
    if(!tracker->update(src, armor_box)){
        return false;
    }
    if((armor_box & cv::Rect2d(0, 0, 640, 480)) != armor_box){
        return false;
    }

    cv::Mat roi = src.clone()(armor_box), roi_gray;
    cv::cvtColor(roi, roi_gray, CV_RGB2GRAY);
    cv::threshold(roi_gray, roi_gray, 180, 255, cv::THRESH_BINARY);
    contour_area = cv::countNonZero(roi_gray);
    if(abs(cv::countNonZero(roi_gray) - contour_area) > contour_area * 0.3){
        return false;
    }
    return sendBoxPosition();
}
