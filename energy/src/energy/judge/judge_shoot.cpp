//
// Created by sun on 19-7-11.
//

#include "energy/energy.h"
#include "log.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断世界坐标系下是否可以发弹
// ---------------------------------------------------------------------------------------------------------------------
void Energy::judgeShootInWorld(){
    if (abs(yaw_rotation - mcuData.curr_yaw) < 0.8 && fabs(pitch_rotation - mcuData.curr_pitch) < 0.8) {
        shoot = 4;
        is_predicting = false;
        is_guessing = true;
        start_guess = true;
        gettimeofday(&time_start_guess, NULL);
        LOGM(STR_CTR(WORD_LIGHT_RED, "Start Guessing!"));
    } else
        shoot = 2;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断云台坐标系下是否可以发弹
// ---------------------------------------------------------------------------------------------------------------------
void Energy::judgeShootInGimbal(){
    if (abs(yaw_rotation) < 0.5 && fabs(pitch_rotation) < 0.5) {
        shoot = 4;
        is_predicting = false;
        is_guessing = true;
        start_guess = true;
        gettimeofday(&time_start_guess, NULL);
//        LOGM(STR_CTR(WORD_LIGHT_RED, "Start Guessing!"));
    } else
        shoot = 2;

    sum_yaw += yaw_rotation;
    sum_pitch += pitch_rotation;
    yaw_rotation = AIM_KP * yaw_rotation +  AIM_KI * sum_yaw;
    pitch_rotation = AIM_KP * pitch_rotation + AIM_KI * sum_pitch;
}
