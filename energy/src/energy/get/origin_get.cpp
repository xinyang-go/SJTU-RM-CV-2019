//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于获得云台对心得到的初始yaw和pitch（即以该yaw和pitch发射子弹，可以击中风车中心）
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::getOrigin() {
    if (!auto_mark && !manual_mark) {
        double dx = -(circle_center_point.x - 320);
        double dy = -(circle_center_point.y - 240);
        center_delta_yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
        center_delta_pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
        if (abs(center_delta_pitch) > 0.3 || abs(center_delta_pitch) > 0.3) {
            sendTarget(serial, center_delta_yaw, center_delta_pitch, false);
            return false;
        } else {
            origin_yaw = mcuData.curr_yaw;
            origin_pitch = mcuData.curr_pitch;
            auto_mark = true;
            sendTarget(serial, center_delta_yaw, center_delta_pitch, true);
            LOGM(STR_CTR(WORD_BLUE_CODE, "auto mark success!"));
            return true;
        }
    }
    return true;
}