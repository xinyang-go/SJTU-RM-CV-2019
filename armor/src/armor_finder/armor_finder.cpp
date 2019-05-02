//
// Created by xinyang on 19-3-27.
//
#define LOG_LEVEL LOG_NONE
#include <log.h>
#include <options/options.h>
#include <show_images/show_images.h>
#include <opencv2/highgui.hpp>
#include <armor_finder/armor_finder.h>

ArmorFinder::ArmorFinder(EnemyColor color, Uart &u, string paras_folder) :
            uart(u),
            enemy_color(color),
            state(STANDBY_STATE),
            classifier(std::move(paras_folder)),
            contour_area(0)
            {
}

void ArmorFinder::run(cv::Mat &src) {
    cv::Mat src_use;
    src_use = src.clone();
    cv::cvtColor(src_use, src_gray, CV_RGB2GRAY);

    if(show_armor_box){
        showArmorBox("box", src, armor_box);
        cv::waitKey(1);
    }
//    stateSearchingTarget(src_use);
//    return;
    switch (state){
        case SEARCHING_STATE:
            if(stateSearchingTarget(src_use)){
                if((armor_box & cv::Rect2d(0, 0, 640, 480)) == armor_box) {
                    if(!classifier){
                        cv::Mat roi = src_use.clone()(armor_box), roi_gray;
                        cv::cvtColor(roi, roi_gray, CV_RGB2GRAY);
                        cv::threshold(roi_gray, roi_gray, 180, 255, cv::THRESH_BINARY);
                        contour_area = cv::countNonZero(roi_gray);
                    }
                    tracker = TrackerToUse::create();
                    tracker->init(src_use, armor_box);
                    state = TRACKING_STATE;
                    LOGM(STR_CTR(WORD_LIGHT_CYAN, "into track"));
                }
            }
            break;
        case TRACKING_STATE:
            if(!stateTrackingTarget(src_use)){
                state = SEARCHING_STATE;
                LOGM(STR_CTR(WORD_LIGHT_YELLOW ,"into search!"));
            }
            break;
        case STANDBY_STATE:
        default:
            stateStandBy();
    }
}

#define FOCUS_PIXAL      (0.36/0.48*640)

bool ArmorFinder::sendBoxPosition() {
    static int dx_add = 0;
    auto rect = armor_box;
    double dx = rect.x + rect.width/2 - 320 - 8;
    dx_add += dx;
    dx = dx + dx_add * 0;
    double dy = rect.y + rect.height/2 - 240 - 30;
    double yaw   = atan(dx / FOCUS_PIXAL) * 180 / 3.14159265459;
    double pitch = atan(dy / FOCUS_PIXAL) * 180 / 3.14159265459;
    uart.sendTarget(yaw, -pitch, 0);
    return true;
}