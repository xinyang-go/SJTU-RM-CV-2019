//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断是否应当继续保持猜测模式
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::stayGuessing(){
    if (change_target || isGuessingTimeout()) {
        is_predicting = true;
        is_guessing = false;
        LOGM(STR_CTR(WORD_LIGHT_YELLOW, "Start Predicting!"));
        return false;
    }
    return true;
}