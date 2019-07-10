//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于切换猜测模式（发弹——新目标出现）和击打模式（新目标出现——发弹）
// ---------------------------------------------------------------------------------------------------------------------
void Energy::changeMode() {
    if (changeTarget()) {
        isGuessing = false;
        isPredicting = true;
        target_cnt++;//若云台移动过程中发现有新装甲板亮起，需改变target_cnt值，以及时告知主控板中断进程，防止重复打击
    }
    if (big_energy_shoot || small_energy_shoot){
        isGuessing = true;
        isPredicting = false;
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断云台对心是否完成
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isGimbleCentered() {
    if (centerRs.size() == 1) {
        circle_center_point = centerRs.at(0).rect.center;
        isGimble = false;
        isChassis = true;
        return true;
    }
    return false;
}