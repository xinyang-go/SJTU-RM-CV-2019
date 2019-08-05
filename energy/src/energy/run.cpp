//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"
#include "log.h"
#include "config/setconfig.h"
#include "options.h"

using namespace std;
using namespace cv;

//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::runBig(cv::Mat &gimbal_src, cv::Mat &chassis_src) {
    if (chassis_src.empty())
        runBig(gimbal_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if (is_gimbal) {
        energy_part_param_ = gimbal_energy_part_param_;
        clearAll();
        initImage(gimbal_src);
        camera_cnt = 2;

        if (findArmors(gimbal_src) < 1)return;
        if (show_energy)showArmors("armor", gimbal_src);
        if (!findFlowStripFan(gimbal_src))return;
        if (!findTargetInFlowStripFan()) return;
        if (!findFlowStrip(gimbal_src))return;
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
        if (!findTargetInFlowStripFan()) return;
        if (!findFlowStrip(gimbal_src))return;
        if (!findCenterROI(chassis_src))return;
        if (show_energy)showFlowStripFan("strip", chassis_src);
        if (!findCenterR(chassis_src))return;
        if (show_energy)showCenterR("R", chassis_src);
        getTargetPolarAngle();
        changeTarget();
        if (is_big && energy_rotation_init) {
            initRotation();
            return;
        }
        if (save_mark)writeDownMark(chassis_src);
        getPredictPoint(target_point);
        gimbalRotation();
        judgeShootInWorld();
        sendEnergy();
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::runBig(cv::Mat &gimbal_src) {
    energy_part_param_ = gimbal_energy_part_param_;
    clearAll();
    initImage(gimbal_src);

    if (show_process)imshow("bin", gimbal_src);
    if (findArmors(gimbal_src) < 1)return;
    if (show_energy)showArmors("armor", gimbal_src);
    if (!findFlowStripFan(gimbal_src)) {
        if (!findFlowStripWeak(gimbal_src))return;
    } else {
        if (show_energy)showFlowStripFan("strip fan", gimbal_src);
        if (!findTargetInFlowStripFan()) return;
        if (!findFlowStrip(gimbal_src))return;
    }
    if (!findCenterROI(gimbal_src))return;
    if (show_energy)showFlowStrip("strip", gimbal_src);
    if (!findCenterR(gimbal_src))return;
    if (show_energy)showCenterR("R", gimbal_src);
    fans_cnt = findFans(gimbal_src);
    if (show_energy)showFans("fans", gimbal_src);

//    getCenter();
//    sendEnergy();
//    return;

    changeTarget();
    getTargetPolarAngle();

    if (energy_rotation_init) {
        initRotation();
        return;
    }
    if (save_mark)writeDownSlightChange(gimbal_src);
    getPredictPoint(target_point);
    getAimPoint(predict_point);
    judgeShootInGimbal();
    cout << "yaw: " << yaw_rotation << '\t' << "pitch: " << pitch_rotation << '\t' << "shoot: " << shoot << endl;
    waitKey(0);
    sendEnergy();
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关模式主控制流函数，击打小符只需要拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
void Energy::runSmall(cv::Mat &gimbal_src) {
    energy_part_param_ = gimbal_energy_part_param_;
    clearAll();
    initImage(gimbal_src);

    if (show_process)imshow("bin", gimbal_src);
    if (findArmors(gimbal_src) < 1)return;
    if (show_energy)showArmors("armor", gimbal_src);
    if (!findFlowStripFan(gimbal_src)) {
        if (!findFlowStripWeak(gimbal_src))return;
    } else {
        if (show_energy)showFlowStripFan("strip fan", gimbal_src);
        if (!findTargetInFlowStripFan()) return;
        if (!findFlowStrip(gimbal_src))return;
    }
    if (show_energy)showTarget("target", gimbal_src);
    fans_cnt = findFans(gimbal_src);
    if (show_energy)showFans("fans", gimbal_src);

//    getCenter();
//    sendEnergy();
//    return;

    changeTarget();
    if (save_mark)writeDownSlightChange(gimbal_src);
    getPredictPoint(target_point);
    getAimPoint(predict_point);
    judgeShootInGimbal();
    sendEnergy();
}


