//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using namespace std;


//----------------------------------------------------------------------------------------------------------------------
// 此函数获取目标装甲板极坐标角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getTargetPolarAngle() {
    target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                             (target_point.x - circle_center_point.x)));
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于存储图像中所有装甲板的中心坐标，以便后续最小二乘法计算圆心和半径
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAllTargetArmorCenters() {
    all_target_armor_centers.emplace_back(target_point);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于存储近30帧图像中所有装甲板的中心坐标，用于判断小符和大符
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getRecentTargetArmorCenters() {
    if (change_target) {
        while (!recent_target_armor_centers.empty())recent_target_armor_centers.pop();//目标切换时清空
        return;
    }
    if (recent_target_armor_centers.size() < 30)recent_target_armor_centers.push(target_polar_angle);
    else {
        recent_target_armor_centers.pop();
        recent_target_armor_centers.push(target_polar_angle);
    }
}