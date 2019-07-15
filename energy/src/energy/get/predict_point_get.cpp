//
// Created by xixiliadorabarry on 1/24/19.
//

#include "energy/energy.h"
#include "energy/constant.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;


//----------------------------------------------------------------------------------------------------------------------
// 此函数获取预测点坐标
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getPredictPoint(cv::Point target_point) {
    if (is_big) {
        if (energy_rotation_direction == 1) rotate(target_point);
        if (energy_rotation_direction == -1) rotate(target_point);
    } else if (is_small) predict_point = target_point;
}

