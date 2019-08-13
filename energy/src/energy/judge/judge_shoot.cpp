//
// Created by sun on 19-7-11.
//

#include "energy/energy.h"
#include "log.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断云台坐标系下是否可以发弹
// ---------------------------------------------------------------------------------------------------------------------
void Energy::judgeShoot() {
    if (abs(yaw_rotation) < 0.7 && abs(pitch_rotation) < 0.7) {
        shoot = 2;
//        is_predicting = false;
//        is_guessing = true;
//        start_guess = true;
//        getsystime(time_start_guess);
//        LOGM(STR_CTR(WORD_LIGHT_RED, "Start Guessing!"));
    } else
        shoot = 1;
}
