//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断云台对心是否完成
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isGimbleCentered(){
    if(centerRs.size()==1){
        circle_center_point = centerRs.at(0).rect.center;
        isGimble = false;
        isChassis = true;
        return true;
    }
    return false;
}