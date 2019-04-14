//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

void Energy::sendTargetByUart(float x, float y, float z) {
//    if(!changeTarget()){
//        return;
//    }
    uart.sendTarget(x, y, z);
    send_cnt+=1;
}



