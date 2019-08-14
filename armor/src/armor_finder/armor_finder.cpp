//
// Created by xinyang on 19-3-27.
//

/*===========================================================================*/
/*                               使用本代码的兵种                               */
/*===========================================================================*/
/*   _______________   _______________   _______________   _______________   */
/*  |     _____     | |     _  _      | |     ____      | |     _____     |  */
/*  ||   |___ /    || ||   | || |    || ||   | ___|    || ||   |___  |   ||  */
/*  ||     |_ \    || ||   | || |_   || ||   |___ \    || ||      / /    ||  */
/*  ||    ___) |   || ||   |__   _|  || ||    ___) |   || ||     / /     ||  */
/*  ||   |____/    || ||      |_|    || ||   |____/    || ||    /_/      ||  */
/*  |_______________| |_______________| |_______________| |_______________|  */
/*                                                                           */
/*===========================================================================*/

#define LOG_LEVEL LOG_NONE
#include <log.h>
#include <options.h>
#include <show_images/show_images.h>
#include <opencv2/highgui.hpp>
#include <armor_finder/armor_finder.h>

std::map<int, string> id2name = {                               //装甲板id到名称的map
        {-1, "OO"},{ 0, "NO"},
        { 1, "B1"},{ 2, "B2"},{ 3, "B3"},{ 4, "B4"},{ 5, "B5"},{ 6, "B7"},{ 7, "B8"},
        { 8, "R1"},{ 9, "R2"},{10, "R3"},{11, "R4"},{12, "R5"},{13, "R7"},{14, "R8"},
};

std::map<string, int> name2id = {                               //装甲板名称到id的map
        {"OO", -1},{"NO",  0},
        {"B1",  1},{"B2",  2},{"B3",  3},{"B4",  4},{"B5",  5},{"B7",  6},{"B8",  7},
        {"R1",  8},{"R2",  9},{"R3", 10},{"R4", 11},{"R5", 12},{"R7", 13},{"R8", 14},
};

std::map<string, int> prior_blue = {
        {"B8", 0}, {"B1", 1}, {"B3", 2}, {"B4", 2}, {"B5", 2}, {"B7", 3}, {"B2", 4},
        {"R8", 5}, {"R1", 6}, {"R3", 7}, {"R4", 7}, {"R5", 7}, {"R7", 8}, {"R2", 9},
        {"NO", 10},
};

std::map<string, int> prior_red = {
        {"R8", 0}, {"R1", 1}, {"R3", 2}, {"R4", 2}, {"R5", 2}, {"R7", 3}, {"R2", 4},
        {"B8", 5}, {"B1", 6}, {"B3", 7}, {"B4", 7}, {"B5", 7}, {"B7", 8}, {"B2", 9},
        {"NO", 10},
};

ArmorFinder::ArmorFinder(uint8_t &color, Serial &u, const string &paras_folder, const uint8_t &anti_top) :
        serial(u),
        enemy_color(color),
        is_anti_top(anti_top),
        state(STANDBY_STATE),
        anti_switch_cnt(0),
        classifier(paras_folder),
        contour_area(0),
        tracking_cnt(0) {
}

void ArmorFinder::run(cv::Mat &src) {
    getsystime(frame_time); //　获取当前帧时间(不是足够精确)
//    stateSearchingTarget(src);                    // for debug
//    goto end;
    switch (state) {
        case SEARCHING_STATE:
            if (stateSearchingTarget(src)) {
                if ((target_box.rect & cv::Rect2d(0, 0, 640, 480)) == target_box.rect) { // 判断装甲板区域是否脱离图像区域
                    if (!classifier) {                                          /* 如果分类器不可用 */
                        cv::Mat roi = src(target_box.rect).clone(), roi_gray;  /* 就使用装甲区域亮点数判断是否跟丢 */
                        cv::cvtColor(roi, roi_gray, CV_RGB2GRAY);
                        cv::threshold(roi_gray, roi_gray, 180, 255, cv::THRESH_BINARY);
                        contour_area = cv::countNonZero(roi_gray);
                    }
                    tracker = TrackerToUse::create();                       // 成功搜寻到装甲板，创建tracker对象
                    tracker->init(src, target_box.rect);
                    state = TRACKING_STATE;
                    tracking_cnt = 0;
                    LOGM(STR_CTR(WORD_LIGHT_CYAN, "into track"));
                }
            }
            break;
        case TRACKING_STATE:
            if (!stateTrackingTarget(src) || ++tracking_cnt > 100) {    // 最多追踪100帧图像
                state = SEARCHING_STATE;
                LOGM(STR_CTR(WORD_LIGHT_YELLOW, "into search!"));
            }
            break;
        case STANDBY_STATE:
        default:
            stateStandBy(); // currently meaningless
    }
end:
    if(is_anti_top) { // 判断当前是否为反陀螺模式
        antiTop();
    }else if(target_box.rect != cv::Rect2d()) {
        anti_top_cnt = 0;
        time_seq.clear();
        angle_seq.clear();
        sendBoxPosition(0);
    }

    if(target_box.rect != cv::Rect2d()){
        last_box = target_box;
    }

    if (show_armor_box) {                 // 根据条件显示当前目标装甲板
        showArmorBox("box", src, target_box);
        cv::waitKey(1);
    }
}

