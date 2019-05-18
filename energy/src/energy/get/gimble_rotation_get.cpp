//
// Created by xixiliadorabarry on 19-3-23.
//
#include "energy/energy.h"
#include <cmath>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::changeMark() {
	if (mcuData.mark == 0 && last_mark == 1) {
		last_mark = mcuData.mark;
		origin_yaw = mcuData.curr_yaw;
		origin_pitch = mcuData.curr_pitch;
		isMark = true;
	}
	else if (mcuData.state == 1) {
		last_mark = mcuData.mark;
		isMark = true;
	}
	else {
		last_mark = mcuData.mark;
		isMark = false;
	}
}


void Energy::gimbleRotation(){
	cv::Point2f real_hit_point;
    stretch(hit_point, real_hit_point);

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