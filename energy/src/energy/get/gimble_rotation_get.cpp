//
// Created by xixiliadorabarry on 19-3-23.
//
#include "energy/energy.h"
#include <cmath>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

extern float curr_yaw, curr_pitch, mark_yaw, mark_pitch;


void Energy::gimbleRotation(){
//该方法用于标定激光零点的情况，对操作手友好，但建立在云台稳定情况下
//    yaw_rotation = static_cast<float>(180 / PI * atan2(-1*STRETCH*(hit_point.x-ZERO_POINT_X), ATTACK_DISTANCE));
//    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(PITCH_ORIGIN_RAD)-STRETCH*(hit_point.y-ZERO_POINT_Y)), ATTACK_DISTANCE));

//该方法用于操作手自己完成对心工作的情况，对操作手要求高
//    cv::Point2f real_hit_point;
//    stretch(hit_point, real_hit_point);
//    yaw_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(YAW_ORIGIN_RAD)-real_hit_point.x), ATTACK_DISTANCE));
//    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(PITCH_ORIGIN_RAD)-real_hit_point.y), ATTACK_DISTANCE));

//    yaw_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(curr_yaw)-real_hit_point.x), ATTACK_DISTANCE));
//    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(curr_pitch)-real_hit_point.y), ATTACK_DISTANCE));

    yaw_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(3.5*PI/180)-STRETCH*(hit_point.x-cycle_center.x)), ATTACK_DISTANCE));
    pitch_rotation = static_cast<float>(180 / PI * atan2((ATTACK_DISTANCE*tan(9.1*PI/180)-STRETCH*(hit_point.y-cycle_center.y)), ATTACK_DISTANCE));
    cout<<"cur: "<<curr_yaw<<endl;
    cout<<"hit point: "<<hit_point<<'\t'<<"cycle center: "<<cycle_center<<endl;
}