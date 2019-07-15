//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"

using namespace std;
using namespace cv;




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断目标是否切换
// ---------------------------------------------------------------------------------------------------------------------
void Energy::changeTarget(){
    if (pointDistance(target_point, last_target_point) < energy_part_param_.TARGET_CHANGE_DISTANCE_MAX) {
        change_target = false;
    } else {
        change_target = true;
    }
    last_target_point = target_point;
}