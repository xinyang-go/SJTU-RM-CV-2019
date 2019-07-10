//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src, cv::Mat &chassis_src) {
    if (chassis_src.empty())
        runBig(gimble_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if (isGimble) {
        imshow("src", gimble_src);
        fans.clear();
        armors.clear();
        centerRs.clear();
        flow_strip_fans.clear();
        flow_strips.clear();
        center_ROI.clear();
        target_armor.clear();

        threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
        imshow("bin", gimble_src);
        armors_cnt = findArmor(gimble_src, last_armors_cnt);
        flow_strip_fans_cnt = findFlowStripFan(gimble_src, last_flow_strip_fans_cnt);
        if (flow_strip_fans_cnt == 1 && findTargetInFlowStripFan()) {
            findCenterROI(gimble_src);
            showFlowStripFanContours("strip", gimble_src);
        } else {
            fans_cnt = findFan(gimble_src, last_fans_cnt);
            if (fans_cnt == -1 || armors_cnt == -1 || armors_cnt != fans_cnt + 1) return 0;
            findTargetByIntersection();
        }
        centerRs_cnt = findCenterR(gimble_src);
        if (centerRs_cnt > 0)showCenterRContours("R", gimble_src);
        if (isGimbleCentered()) {
            getOrigin();
            initEnergy();
            destroyAllWindows();
        }
    } else if (isChassis) {
        imshow("src", chassis_src);
        fans.clear();
        armors.clear();
        centerRs.clear();
        flow_strip_fans.clear();
        flow_strips.clear();
        center_ROI.clear();
        target_armor.clear();

//        imagePreprocess(chassis_src);
//        imshow("img_preprocess", chassis_src);

        changeMark();
        if (isMark)return 0;//操作手强制手动标定origin_yaw和origin_pitch

        threshold(chassis_src, chassis_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);

        armors_cnt = findArmor(chassis_src, last_armors_cnt);
        flow_strip_fans_cnt = findFlowStripFan(chassis_src, last_flow_strip_fans_cnt);
        if (flow_strip_fans_cnt == 1 && findTargetInFlowStripFan()) {
            findCenterROI(chassis_src);
            showFlowStripFanContours("strip", chassis_src);
        } else {
            fans_cnt = findFan(chassis_src, last_fans_cnt);
            if (fans_cnt == -1 || armors_cnt == -1 || armors_cnt != fans_cnt + 1) return 0;
            findTargetByIntersection();
        }

        centerRs_cnt = findCenterR(chassis_src);
        if (centerRs_cnt > 0)showCenterRContours("R", chassis_src);
        if (centerRs.size() != 1)return 0;
        circle_center_point = centerRs.at(0).rect.center;
        target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                                 (target_point.x - circle_center_point.x)));
        if (energy_rotation_init) {
            initRotation();
            return 0;
        }

        getOrigin();
        getPredictPoint();
        gimbleRotation();
        if (changeTarget())target_cnt++;
        sendBigTarget(serial, yaw_rotation, pitch_rotation, target_cnt);

        return 0;
    }
    return 0;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src) {
    imshow("src", gimble_src);
    fans.clear();
    armors.clear();
    centerRs.clear();
    flow_strip_fans.clear();
    flow_strips.clear();
    center_ROI.clear();
    target_armor.clear();
//    imagePreprocess(gimble_src);
//    imshow("img_preprocess", gimble_src);

    threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
//    imshow("bin",gimble_src);
    armors_cnt = findArmor(gimble_src, last_armors_cnt);
    flow_strip_fans_cnt = findFlowStripFan(gimble_src, last_flow_strip_fans_cnt);
    if (flow_strip_fans_cnt == 1 && findTargetInFlowStripFan()) {
        findCenterROI(gimble_src);
        showFlowStripFanContours("strip", gimble_src);
    } else {
        fans_cnt = findFan(gimble_src, last_fans_cnt);
        if (fans_cnt == -1 || armors_cnt == -1 || armors_cnt != fans_cnt + 1) return 0;
        findTargetByIntersection();
    }
    centerRs_cnt = findCenterR(gimble_src);
    if (centerRs_cnt > 0)showCenterRContours("R", gimble_src);
    if (centerRs.size() != 1)return 0;
    circle_center_point = centerRs.at(0).rect.center;
    target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                             (target_point.x - circle_center_point.x)));
    if (energy_rotation_init) {
        initRotation();
        getOrigin();//一旦确定风车旋向后，就开始移动云台，此时不再更新origin_yaw和origin_pitch
        return 0;
    }
    getPredictPoint();
    gimbleRotation();
    if (changeTarget())target_cnt++;
    sendBigTarget(serial, yaw_rotation, pitch_rotation, target_cnt);

    return 0;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关模式主控制流函数，击打小符只需要拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runSmall(cv::Mat &gimble_src) {
    imshow("gimble src", gimble_src);
    if (gimble_src.type() == CV_8UC3)cvtColor(gimble_src, gimble_src, COLOR_BGR2GRAY);
    fans.clear();
    armors.clear();
    centerRs.clear();
    flow_strip_fans.clear();
    flow_strips.clear();
    center_ROI.clear();
    target_armor.clear();
    threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
    imshow("bin", gimble_src);
    armors_cnt = findArmor(gimble_src, last_armors_cnt);
    flow_strip_fans_cnt = findFlowStripFan(gimble_src, last_flow_strip_fans_cnt);
    if (flow_strip_fans_cnt == 1 && findTargetInFlowStripFan()) {
        findCenterROI(gimble_src);
        showFlowStripFanContours("strip", gimble_src);
    } else {
        fans_cnt = findFan(gimble_src, last_fans_cnt);
        if (fans_cnt == -1 || armors_cnt == -1 || armors_cnt != fans_cnt + 1) return 0;
        findTargetByIntersection();
    }
    centerRs_cnt = findCenterR(gimble_src);
    if (centerRs_cnt > 0)showCenterRContours("R", gimble_src);
    if (centerRs.size() != 1)return 0;
    circle_center_point = centerRs.at(0).rect.center;
    target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                             (target_point.x - circle_center_point.x)));
    getAimPoint();
    if (changeTarget())target_cnt++;//若云台移动过程中发现有新装甲板亮起，需改变target_cnt值，以及时告知主控板中断进程，防止重复打击
    sendSmallTarget(serial, yaw_rotation, pitch_rotation, target_cnt, small_energy_shoot);

    return 0;
}




