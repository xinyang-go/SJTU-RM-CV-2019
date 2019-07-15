//
// Created by sun on 19-7-11.
//

#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断是否可以发弹
// ---------------------------------------------------------------------------------------------------------------------
void Energy::judgeShoot(){
    if (abs(yaw_rotation - mcuData.curr_yaw) < 0.3 && fabs(pitch_rotation - mcuData.curr_pitch) < 0.3) {
        shoot = true;
        is_predicting = false;
        is_guessing = true;
        start_guess = true;
        gettimeofday(&time_start_guess, NULL);
        LOGM(STR_CTR(WORD_LIGHT_RED, "Start Guessing!"));
    } else
        shoot = false;
}
