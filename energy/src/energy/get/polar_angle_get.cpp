//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using namespace std;



//----------------------------------------------------------------------------------------------------------------------
// 此函数获取目标装甲板极坐标角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getTargetPolarAngle() {
    target_polar_angle = static_cast<float>(180 / PI * atan2(-1 * (target_point.y - circle_center_point.y),
                                                            (target_point.x - circle_center_point.x)));
}

