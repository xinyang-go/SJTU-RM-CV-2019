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
void Energy::run(cv::Mat &gimbal_src, cv::Mat &chassis_src) {
    if (chassis_src.empty())
        run(gimbal_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if (is_gimbal) {
        energy_part_param_ = gimbal_energy_part_param_;
        clearAll();
        initImage(gimbal_src);
//        findFans(gimbal_src);
//        showFans("fan",gimbal_src);

        if (findArmors(gimbal_src) < 1)return;
        if (show_energy)showArmors("armor", gimbal_src);
        if (!findFlowStripFan(gimbal_src))return;
        if (!findTargetInFlowStripFan()) return;
        if (!findCenterROI(gimbal_src))return;
        if (show_energy)showFlowStripFan("strip", gimbal_src);
        if (!findCenterR(gimbal_src))return;
        if (show_energy)showCenterR("R", gimbal_src);

        if (!getOrigin())return;
        startChassis();
        initEnergy();
        destroyAllWindows();
    } else if (is_chassis) {
        energy_part_param_ = chassis_energy_part_param_;
        clearAll();
        initImage(chassis_src);

        changeMark();
        if (is_mark)return;//操作手强制手动标定origin_yaw和origin_pitch

        if (findArmors(chassis_src) < 1)return;
        if (show_energy)showArmors("armor", chassis_src);
        if (!findFlowStripFan(chassis_src))return;
        showFlowStripFan("flow strip fan", chassis_src);
        if (!findTargetInFlowStripFan()) return;
        if (!findCenterROI(chassis_src))return;
        if (show_energy)showFlowStripFan("strip", chassis_src);
        if (!findCenterR(chassis_src))return;
        if (show_energy)showCenterR("R", chassis_src);
        getTargetPolarAngle();
        changeTarget();
        JudgeMode();
        if (energy_mode_init)return;
        if (is_big && energy_rotation_init) {
            initRotation();
            return;
        }
        if (is_predicting) {
            getPredictPoint(target_point);
            gimbalRotation();
            judgeShoot();
            sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
        } else if (is_guessing && stayGuessing()) {
            findFans(chassis_src);
            if (show_energy)showFans("fans", chassis_src);
            if (save_mark)writeDownMark();
            if (!guessTarget()) return;
            if (show_energy)showGuessTarget("guess", chassis_src);
            getPredictPoint(guess_point);
            gimbalRotation();
            sendTarget(serial, yaw_rotation, pitch_rotation, false);
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::run(cv::Mat &gimbal_src) {
    energy_part_param_ = gimbal_energy_part_param_;
    clearAll();
    initImage(gimbal_src);

    changeMark();
    if (is_mark)return;//操作手强制手动标定origin_yaw和origin_pitch

    if (show_process)imshow("bin", gimbal_src);
    if (findArmors(gimbal_src) < 1)return;
    if (show_energy)showArmors("armor", gimbal_src);
    if (!findFlowStripFan(gimbal_src))return;
    if (!findTargetInFlowStripFan()) return;
    if (!findCenterROI(gimbal_src))return;
    if (show_energy)showFlowStripFan("strip", gimbal_src);
    if (!findCenterR(gimbal_src))return;
    if (show_energy)showCenterR("R", gimbal_src);
    changeTarget();
    getTargetPolarAngle();
    JudgeMode();
    if (energy_mode_init)return;
    if (!getOrigin())return;
    if (is_big && energy_rotation_init) {
        initRotation();
        return;
    }
    if (is_predicting) {
        getPredictPoint(target_point);
        gimbalRotation();
        judgeShoot();
        sendTarget(serial, yaw_rotation, pitch_rotation, shoot);
    } else if (is_guessing && stayGuessing()) {
        findFans(gimbal_src);
        if (show_energy)showFans("fans", gimbal_src);
        if (save_mark)writeDownMark();
        guessTarget();
        if (show_energy)showGuessTarget("guess", gimbal_src);
        getPredictPoint(guess_point);
        gimbalRotation();
        sendTarget(serial, yaw_rotation, pitch_rotation, false);
    }
}
