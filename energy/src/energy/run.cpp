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
// 此函数为能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::run(cv::Mat &gimble_src, cv::Mat &chassis_src) {
    if (chassis_src.empty())
        run(gimble_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if (isGimble) {
        energy_part_param_ = chassis_energy_part_param_;
        clearAll();
        initImage(gimble_src);

        if (findArmors(gimble_src) < 1)return;
        if (!findFlowStripFan(gimble_src))return;
        if (!findTargetInFlowStripFan()) return;
        if (!findCenterROI(gimble_src))return;
        if (!findCenterR(gimble_src))return;

        if (show_energy)showFlowStripFan("strip", gimble_src);
        if (show_energy)showCenterR("R", gimble_src);

        if (!getOrigin())return;
        startChassis();
        initEnergy();

    } else if (isChassis) {
        energy_part_param_ = chassis_energy_part_param_;
        clearAll();
        initImage(chassis_src);

        changeMark();
        if (isMark)return;//操作手强制手动标定origin_yaw和origin_pitch

        if (findArmors(chassis_src) < 1)return;
        if (!findFlowStripFan(chassis_src))return;
        if (!findTargetInFlowStripFan()) return;
        if (!findCenterROI(chassis_src))return;
        if (!findCenterR(chassis_src))return;

        if (show_energy)showFlowStripFan("strip", chassis_src);
        if (show_energy)showCenterR("R", chassis_src);

        getTargetPolarAngle();
        JudgeMode();
        if (energy_mode_init)return;
        if (isBig && energy_rotation_init) {
            initRotation();
            return;
        }
        if (isPredicting) {
            getPredictPoint(target_point);
            gimbleRotation();
            judgeShoot();
            sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
        } else if (isGuessing && stayGuessing()) {
            findFans(chassis_src);
            if (save_mark)writeDownMark();
            if (!guessTarget()) return;
            if (show_energy)showGuessTarget("guess", chassis_src);
            getPredictPoint(guess_point);
            gimbleRotation();
            sendTarget(serial, yaw_rotation, pitch_rotation, false);
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::run(cv::Mat &gimble_src) {
    energy_part_param_ = gimble_energy_part_param_;
    clearAll();
    initImage(gimble_src);

    changeMark();
    if (isMark)return;//操作手强制手动标定origin_yaw和origin_pitch

    if (show_process)imshow("bin", gimble_src);
    if (findArmors(gimble_src) < 1)return;
    if (!findFlowStripFan(gimble_src))return;
    if (!findTargetInFlowStripFan()) return;
    if (!findCenterROI(gimble_src))return;
    if (show_energy)showFlowStripFan("strip", gimble_src);
    if (!findCenterR(gimble_src))return;
    if (show_energy)showCenterR("R", gimble_src);
    getTargetPolarAngle();
    JudgeMode();
    if (energy_mode_init)return;
    if (!getOrigin())return;
    if (isBig & energy_rotation_init) {
        initRotation();
        return;
    }
    if (isPredicting) {
        getPredictPoint(target_point);
        gimbleRotation();
        judgeShoot();
        sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
    } else if (isGuessing && stayGuessing()) {
        findFans(gimble_src);
        if (save_mark)writeDownMark();
        guessTarget();
        if (show_energy)showGuessTarget("guess", gimble_src);
        getPredictPoint(guess_point);
        gimbleRotation();
        sendTarget(serial, yaw_rotation, pitch_rotation, false);
    }
}
