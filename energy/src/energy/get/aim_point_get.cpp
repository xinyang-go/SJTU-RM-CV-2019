//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"

using namespace std;
using namespace cv;

//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(cv::Point target_point) {
//五号车
    double dx = -(target_point.x - 320 - 3);
    double dy = -(target_point.y - 240 - 74);
//四号车
//    double dx = -(target_point.x - 320 + 16);
//    double dy = -(target_point.y - 240 - 82);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
}
