//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"

using namespace std;
using namespace cv;

#define FOCUS_PIXAL_5MM  (917)
#define FOCUS_PIXAL      FOCUS_PIXAL_5MM


//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(){
    double dx = target_point.x - 320;
    double dy = target_point.y - 240;
    yaw_rotation   = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
    if(fabs(yaw_rotation) < 0.5 && fabs(pitch_rotation) < 0.5){
        small_energy_shoot = true;
        cout<<"send"<<endl;
    }
    else
        small_energy_shoot = false;
}
