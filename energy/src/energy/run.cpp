//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"
#include "log.h"
#include "options/options.h"
#include <sys/time.h>

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src, cv::Mat &chassis_src) {
    if (chassis_src.empty())
        runBig(gimble_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if (isGimble) {
        energy_part_param_ = chassis_energy_part_param_;
        clearAll();
        initImage(gimble_src);

        if (findArmors(gimble_src) < 1)return 0;
        if (!findFlowStripFan(gimble_src))return 0;
        if (!findTargetInFlowStripFan()) return 0;
        if (!findCenterROI(gimble_src))return 0;
        if (show_energy)showFlowStripFanContours("strip", gimble_src);
        if (!findCenterR(gimble_src))return 0;
        if (show_energy)showCenterRContours("R", gimble_src);
        startChassis();
        getOrigin();
        initEnergy();
        destroyAllWindows();
    } else if (isChassis) {
        energy_part_param_ = chassis_energy_part_param_;
        clearAll();
        initImage(chassis_src);
        changeMark();
        if (isMark)return 0;//操作手强制手动标定origin_yaw和origin_pitch

        if (show_process)imshow("bin", chassis_src);
        if (findArmors(chassis_src) < 1)return 0;
        if (!findFlowStripFan(chassis_src))return 0;
        if (!findTargetInFlowStripFan()) return 0;
        if (!findCenterROI(chassis_src))return 0;
        if (show_energy)showFlowStripFanContours("strip", chassis_src);
        if (!findCenterR(chassis_src))return 0;
        if (show_energy)showCenterRContours("R", chassis_src);

        findFans(chassis_src);showFanContours("fan",chassis_src);

        getTargetPolarAngle();
        if (save_mark)writeDownMark();
        if (energy_rotation_init) {
            initRotation();
            return 0;
        }
        if (isPredicting) {
            getPredictPoint();
            gimbleRotation();
            judgeBigShoot();
            sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
        } else if (isGuessing) {
            if (changeTarget() || is_guessing_timeout()) {
                isPredicting = true;
                isGuessing = false;
                LOGM(STR_CTR(WORD_LIGHT_YELLOW, "Start Predicting!"));
            } else {
                findFans(chassis_src);
                guessTarget();
                if (show_energy)showGuessTarget("guess", chassis_src);
                target_point = guess_point;
                getPredictPoint();
                gimbleRotation();
                sendTarget(serial, yaw_rotation, pitch_rotation, false);
            }
        }
    }
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src) {
    energy_part_param_ = chassis_energy_part_param_;
    clearAll();
    initImage(gimble_src);

    changeMark();
    if (isMark)return 0;//操作手强制手动标定origin_yaw和origin_pitch

    threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
    if (show_process)imshow("bin", gimble_src);
    if (findArmors(gimble_src) < 1)return 0;
    if (!findFlowStripFan(gimble_src))return 0;
    if (!findTargetInFlowStripFan()) return 0;
    if (!findCenterROI(gimble_src))return 0;
    if (show_energy)showFlowStripFanContours("strip", gimble_src);
    if (!findCenterR(gimble_src))return 0;
    if (show_energy)showCenterRContours("R", gimble_src);
    getTargetPolarAngle();
    if (energy_rotation_init) {
        initRotation();
        getOrigin();//一旦确定风车旋向后，就开始移动云台，此时不再更新origin_yaw和origin_pitch
        return 0;
    }
    if (isPredicting) {
        getPredictPoint();
        gimbleRotation();
        judgeBigShoot();
        sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
    } else if (isGuessing) {
        if (changeTarget() || is_guessing_timeout()){
            isPredicting = true;
            isGuessing = false;
            LOGM(STR_CTR(WORD_LIGHT_YELLOW, "Start Predicting!"));
        } else {
            findFans(gimble_src);
            guessTarget();
            if (show_energy)showGuessTarget("guess", gimble_src);
            target_point = guess_point;
            getPredictPoint();
            gimbleRotation();
            sendTarget(serial, yaw_rotation, pitch_rotation, false);
        }
    }

    return 0;
}


/*//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关模式主控制流函数，击打小符只需要拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runSmall(cv::Mat &gimble_src) {
    if (gimble_src.type() == CV_8UC3)cvtColor(gimble_src, gimble_src, COLOR_BGR2GRAY);
    energy_part_param_ = gimble_energy_part_param_;
    fans.clear();
    armors.clear();
    centerRs.clear();
    flow_strip_fans.clear();
    flow_strips.clear();
    threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
    if (show_bin)imshow("bin", gimble_src);
    armors_cnt = findArmor(gimble_src, last_armors_cnt);
    flow_strip_fans_cnt = findFlowStripFan(gimble_src, last_flow_strip_fans_cnt);
    if (flow_strip_fans_cnt == 1 && findTargetInFlowStripFan()) {
        findCenterROI(gimble_src);
        if (show_strip)showFlowStripFanContours("strip", gimble_src);
    } else {
        fans_cnt = findFan(gimble_src, last_fans_cnt);
        findTargetByIntersection();
        if (show_single) {
            if (fans_cnt > 0)showFanContours("fan", gimble_src);
            if (armors_cnt > 0)showArmorContours("armor", gimble_src);
        }
        if (show_both && (fans_cnt > 0 || armors_cnt > 0))showBothContours("both", gimble_src);
    }
    centerRs_cnt = findCenterR(gimble_src);
    if (show_center && centerRs_cnt > 0)showCenterRContours("R", gimble_src);
    if (centerRs.size() != 1)return 0;
    circle_center_point = centerRs.at(0).center;
    target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                             (target_point.x - circle_center_point.x)));
    getAimPoint();
    changeMode();
    sendTarget(serial, yaw_rotation, pitch_rotation, target_cnt, small_energy_shoot);

    return 0;
}*/




