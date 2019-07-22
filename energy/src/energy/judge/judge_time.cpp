//
// Created by sun on 19-7-11.
//


#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断guess模式是否超时
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isGuessingTimeout() {
    timeval cur_time;
    gettimeofday(&cur_time, NULL);
    return (cur_time.tv_sec - time_start_guess.tv_sec) * 1000.0 +
           (cur_time.tv_usec - time_start_guess.tv_usec) / 1000.0 > 1000;
};