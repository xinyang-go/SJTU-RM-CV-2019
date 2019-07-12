//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于从云台摄像头对心状态切换到底盘摄像头击打状态
// ---------------------------------------------------------------------------------------------------------------------
void Energy::startChassis(){
    isChassis = true;
    isGimble = false;
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断是否应当继续保持猜测模式
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::stayGuessing(){
    if (changeTarget() || isGuessingTimeout()) {
        isPredicting = true;
        isGuessing = false;
        LOGM(STR_CTR(WORD_LIGHT_YELLOW, "Start Predicting!"));
        return false;
    }
    return true;
}