//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"
#include "log.h"
#include "config/setconfig.h"


using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于对心
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getCenter(){
    int compensate_yaw = 0, compensate_pitch = 0;
    if (mcu_data.enemy_color == ENEMY_BLUE) {
        compensate_yaw = RED_COMPENSATE_YAW;
        compensate_pitch = RED_COMPENSATE_PITCH;
    } else if (mcu_data.enemy_color == ENEMY_RED) {
        compensate_yaw = BLUE_COMPENSATE_YAW;
        compensate_pitch = BLUE_COMPENSATE_PITCH;
    }
    double dx = -(circle_center_point.x - 320 - compensate_yaw);
    double dy = -(circle_center_point.y - 240 - compensate_pitch);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
    if (abs(yaw_rotation) < 0.7 && abs(pitch_rotation) < 0.7) {
        shoot = 2;
    } else
        shoot = 1;
}
