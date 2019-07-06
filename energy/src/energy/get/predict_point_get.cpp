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
void Energy::getPredictPoint(){
    if(energy_rotation_direction==1) rotate();
    if(energy_rotation_direction==-1) rotate();
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于操作手手动标定
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::changeTarget(){
    if(pointDistance(target_point,last_target_point) < energy_part_param_.TARGET_CHANGE_DISTANCE_MAX){
        last_target_point = target_point;
        return false;
    }
    else{
        last_target_point= target_point;
        return true;
    }
}