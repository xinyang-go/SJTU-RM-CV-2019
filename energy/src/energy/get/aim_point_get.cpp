//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;

extern mcu_data mcuData;

//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(cv::Point target_point) {
    double dx = -(target_point.x - 320 - COMPENSATE_YAW - mcuData.delta_x);
    double dy = -(target_point.y - 240 - COMPENSATE_PITCH - mcuData.delta_y);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
//    cout << "yaw: " << yaw_rotation << '\t' << "pitch: " << pitch_rotation << endl;
    cout << "mcuData.delta_x: " << mcuData.delta_x << '\t' << "mcuData.delta_y: " << mcuData.delta_y << endl;

}
