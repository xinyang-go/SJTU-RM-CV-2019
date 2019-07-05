//
// Created by xixiliadorabarry on 19-3-23.
//
#include "energy/energy.h"
#include <cmath>
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于操作手手动标定
// ---------------------------------------------------------------------------------------------------------------------
void Energy::changeMark() {
	if (mcuData.mark == 0 && last_mark == 1) {
		last_mark = mcuData.mark;
		origin_yaw = mcuData.curr_yaw;
		origin_pitch = mcuData.curr_pitch;
		isMark = false;
//        LOGM(STR_CTR(WORD_LIGHT_YELLOW, "IsMark"));
	}
	else if (mcuData.mark == 1) {
		last_mark = mcuData.mark;
		isMark = true;
//		LOGM(STR_CTR(WORD_BLUE,"Marking..."));

	}
	else {
		last_mark = mcuData.mark;
		isMark = false;
	}
	//cout<<"mark: "<<int(mcuData.mark)<<endl;
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于计算云台应当转到角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::gimbleRotation(){
	cv::Point2f real_predict_point;//计算在真实世界中的预测点位，进而计算云台的旋转角度
    stretch(predict_point, real_predict_point);
    yaw_rotation = static_cast<float>(180 / PI *
            atan2((attack_distance * tan(origin_yaw * PI / 180) - real_predict_point.x), attack_distance));
    pitch_rotation = static_cast<float>(180 / PI *
            atan2((attack_distance*tan(origin_pitch*PI/180)-real_predict_point.y), attack_distance));
}