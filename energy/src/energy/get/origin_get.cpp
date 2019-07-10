//
// Created by sun on 19-7-10.
//
#include "energy/energy.h"

using namespace std;
using namespace cv;




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于获得云台对心得到的初始yaw和pitch（即以该yaw和pitch发射子弹，可以击中风车中心）
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getOrigin(){
    double dx = circle_center_point.x - 320;
    double dy = circle_center_point.y - 240;
    origin_yaw   = atan(dx / FOCUS_PIXAL) * 180 / PI;
    origin_pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
}