//
// Created by xixiliadorabarry on 1/24/19.
//

#include "energy/energy.h"
#include "energy/constant.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::getHitPoint(){
//    if(!changeTarget()){
//        //last_target_center = target_center;
//        //last_target_position = target_position;
//        return;
//    }
//    else {
        double rad = static_cast<double>(energy_part_rotation * energy_part_param_.RPM
                * energy_part_param_.HIT_TIME * 360 / 60);
        rotate(rad, radius, cycle_center, target_center, hit_point);
        //last_target_center = target_center;
        //last_target_position = target_position;
//    }
}

bool Energy::changeTarget(){
    return !(pointDistance(target_center, last_target_center) < 25 || fabs(target_position - last_target_position) < 30
             ||fabs(target_position - last_target_position) > 330);
}