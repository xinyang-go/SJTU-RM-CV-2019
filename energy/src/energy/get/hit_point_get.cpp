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
    int rad = 60;
    if(energy_part_rotation==1) rotate(rad, radius, cycle_center, target_center, hit_point);
    if(energy_part_rotation==-1) rotate(-rad, radius, cycle_center, target_center, hit_point);
//    int hit_position = 1000;
//    int limit_angle = 6;
//    int angle_interval = 60;
//
//    if(energy_part_rotation==1){
//        if(target_armor>=0 && target_armor<=limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = -1*angle_interval;
//            position_mode = 1;
//        }
//        else if(target_armor>=angle_interval && target_armor<angle_interval+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 0;
//            position_mode = 2;
//        }
//        else if(target_armor>=angle_interval*2 && target_armor<=angle_interval*2+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = angle_interval;
//            position_mode = 3;
//        }
//        else if(target_armor>=-180 && target_armor<-180+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = 2*angle_interval;
//            position_mode = 4;
//        }
//        else if(target_armor>=-2*angle_interval&&target_armor<-2*angle_interval+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 180;
//            position_mode = 5;
//        }
//        else if(target_armor>=-1*angle_interval&&target_armor<-1*angle_interval+limit_angle) {
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = -2 * angle_interval;
//            position_mode = 6;
//        }
//        else{
//            position_mode = 0;
//            return;
//        }
//    }
//
//    if(energy_part_rotation==-1){
//        if(target_armor>=0 && target_armor<=limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = 2*angle_interval;
//            position_mode = 1;
//        }
//        else if(target_armor>=angle_interval && target_armor<angle_interval+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 180;
//            position_mode = 2;
//        }
//        else if(target_armor>=angle_interval*2 && target_armor<=angle_interval*2+limit_angle){
//            hit_point.x = cycle_center.x - static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = -2*angle_interval;
//            position_mode = 3;
//        }
//        else if(target_armor>=-180 && target_armor<-180+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y + static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = -1*angle_interval;
//            position_mode = 4;
//        }
//        else if(target_armor>=-2*angle_interval&&target_armor<-2*angle_interval+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius);
//            hit_point.y = cycle_center.y;
//            hit_position = 0;
//            position_mode = 5;
//        }
//        else if(target_armor>=-1*angle_interval&&target_armor<-1*angle_interval+limit_angle){
//            hit_point.x = cycle_center.x + static_cast<int>(radius / 2);
//            hit_point.y = cycle_center.y - static_cast<int>(radius * sqrt(3) / 2);
//            hit_position = angle_interval;
//            position_mode = 6;
//        }
//        else{
//            position_mode = 0;
//            return;
//        }
//    }
//
//    if(position_mode!=0 && position_mode!=last_position_mode){
//        last_position_mode = position_mode;
//        isSendTarget = true;
//        //cout<<"hit position: "<<hit_position<<endl;
//        return;
//    }
//    else if(position_mode == 0){
//        isSendTarget = false;
//        return;
//    }
//    else{
//        last_position_mode = position_mode;
//        isSendTarget = false;
//        return;
//    }
}

bool Energy::changeTarget(){
    if(fabs(target_armor - last_target_armor) < 30||fabs(target_armor - last_target_armor) > 330){
        last_target_armor = target_armor;
        return false;
    }
    else{
        last_target_armor = target_armor;
        return true;
    }
}