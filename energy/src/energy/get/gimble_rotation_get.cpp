//
// Created by xixiliadorabarry on 19-3-23.
//
#include "energy/energy.h"
#include <cmath>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;


void Energy::gimbleRotation(){
//该方法用于标定激光零点的情况，对操作手友好，但建立在云台稳定情况下
//    yaw_rotation = static_cast<float>(180 / PI * atan2(-1*STRETCH*(hit_point.x-ZERO_POINT_X), ATTACK_DISTANCE));
//    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(PITCH_ORIGIN_RAD)-STRETCH*(hit_point.y-ZERO_POINT_Y)), ATTACK_DISTANCE));

//该方法用于操作手自己完成对心工作的情况，对操作手要求高
    cv::Point2f real_hit_point;
    stretch(hit_point, real_hit_point);
//    yaw_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(YAW_ORIGIN_RAD)-real_hit_point.x), ATTACK_DISTANCE));
//    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(PITCH_ORIGIN_RAD)-real_hit_point.y), ATTACK_DISTANCE));

    yaw_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(aim.yaw)-real_hit_point.x), ATTACK_DISTANCE));
    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(aim.pitch)-real_hit_point.y), ATTACK_DISTANCE));
}