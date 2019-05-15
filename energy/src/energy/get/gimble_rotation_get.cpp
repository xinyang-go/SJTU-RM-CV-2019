//
// Created by xixiliadorabarry on 19-3-23.
//
#include "energy/energy.h"
#include <cmath>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

extern float curr_yaw, curr_pitch, mark_yaw, mark_pitch;


void Energy::gimbleRotation(){
	cv::Point2f real_hit_point;
    stretch(hit_point, real_hit_point);

	float origin_yaw = -0.13; 
	float origin_pitch = 13.18;

	/*origin_yaw = mark_yaw;
	origin_pitch = mark_pitch;*/
   
    if(position_mode == 1){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
    else if(position_mode == 2){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
    else if(position_mode == 3){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
    else if(position_mode == 4){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
    else if(position_mode == 5){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
    else if(position_mode == 6){
		yaw_rotation = static_cast<float>(180 / PI * atan2((attack_distance * tan(origin_yaw * PI / 180) - real_hit_point.x), attack_distance));
        pitch_rotation = static_cast<float>(180 / PI * atan2((attack_distance*tan(origin_pitch*PI/180)-real_hit_point.y), attack_distance));
    }
//    else{
//        pitch_rotation = 5.5+static_cast<float>(180 / PI * atan2((attack_distance*tan(mark_pitch*PI/180)-real_hit_point.y), attack_distance));
//    }

}