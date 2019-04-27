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
    int hit_position = 1000;

    if(energy_part_rotation==1){    //顺时针
        if(target_armor>=0&&target_armor<60){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -60;
        }
        if(target_armor>=60&&target_armor<120){
            hit_point.x = cycle_center.x + static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 0;
        }
        if(target_armor>=120&&target_armor<=180){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = 60;
        }
        if(target_armor>=-180&&target_armor<-120){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = 120;
        }
        if(target_armor>=-120&&target_armor<-60){
            hit_point.x = cycle_center.x - static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 180;
        }
        if(target_armor>=-60&&target_armor<0){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -120;
        }
    }

    if(energy_part_rotation==-1){    //逆时针
        if(target_armor>=0&&target_armor<60){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = 120;
        }
        if(target_armor>=60&&target_armor<120){
            hit_point.x = cycle_center.x - static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 180;
        }
        if(target_armor>=120&&target_armor<=180){
            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -120;
        }
        if(target_armor>=-180&&target_armor<-120){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
            hit_position = -60;
        }
        if(target_armor>=-120&&target_armor<-60){
            hit_point.x = cycle_center.x + static_cast<int>(radius);
            hit_point.y = cycle_center.y;
            hit_position = 0;
        }
        if(target_armor>=-60&&target_armor<0){
            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
            hit_position = 60;
        }
    }

    cout<<"hit position: "<<hit_position<<endl;

//    double rad = static_cast<double>(energy_part_rotation * energy_part_param_.RPM
//                * energy_part_param_.HIT_TIME * 360 / 60);
//    rotate(rad, radius, cycle_center, target_center, hit_point);
}

bool Energy::changeTarget(){
    return !(pointDistance(target_center, last_target_center) < 25 || fabs(target_position - last_target_position) < 30
             ||fabs(target_position - last_target_position) > 330);
}