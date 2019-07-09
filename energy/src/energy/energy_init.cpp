//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数对能量机关成员变量进行初始化
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initEnergy() {
	isMark = false;
	centered=false;
	fans_cnt = 0;
	armors_cnt = 0;
	centerRs_cnt = 0;
    flow_strips_cnt = 0;
    flow_strip_fans_cnt = 0;
	gimble_cnt = 0;
    circle_center_point = Point(0, 0);
	target_point = Point(0, 0);
    last_target_point = Point(0, 0);
    predict_point = Point(0, 0);
	former_point = Point(0,0);
    target_polar_angle = -1000;
    last_target_polar_angle = -1000;
	radius = 0;
    energy_rotation_direction = ANTICLOCKWISE;
	attack_distance = ATTACK_DISTANCE;
	last_fans_cnt = 0;
	last_armors_cnt = 0;
    last_flow_strips_cnt = 0;
    last_flow_strip_fans_cnt = 0;
	send_cnt = 0;
	yaw_rotation = 0;
	pitch_rotation = 0;
	last_mark = 0;

    red_origin_yaw = -0.35;
    red_origin_pitch = 15.11719;
    blue_origin_yaw = -0.439453;
    blue_origin_pitch = 15.688477;

	target_cnt = 0;
    small_energy_shoot = false;
	energy_rotation_init = false;
	predict_rad = 20;

	fans.clear();
	armors.clear();
    centerRs.clear();
    flow_strips.clear();
    flow_strip_fans.clear();
    center_ROI.clear();
    target_armor.clear();

	fan_polar_angle.clear();
	armor_polar_angle.clear();

	all_armor_centers.clear();

	clockwise_rotation_init_cnt = 0;
	anticlockwise_rotation_init_cnt = 0;
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数对能量机关参数进行初始化
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initEnergyPartParam() {
	energy_part_param_.GRAY_THRESH = 225;
	energy_part_param_.SPLIT_GRAY_THRESH = 60;
	energy_part_param_.FAN_GRAY_THRESH = 75;
	energy_part_param_.ARMOR_GRAY_THRESH = 80;

	/*energy_part_param_.FAN_CONTOUR_AREA_MAX = 17000;
	energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
	energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 70;
    energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 100;
	energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 30;
    energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 60;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;

	energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
	energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 13;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 5;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 30;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 20;
	energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
	energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;*/

    energy_part_param_.FAN_CONTOUR_AREA_MAX = 17000;
    energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
    energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 90;
    energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 35;
    energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 140;
    energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 60;
    energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
    energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;
    energy_part_param_.FAN_CONTOUR_AREA_RATIO_MIN = 0.6;

    energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
    energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
    energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 30;
    energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 15;
    energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 50;
    energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 45;
    energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
    energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;
    energy_part_param_.ARMOR_CONTOUR_AREA_RATIO_MIN = 0.7;

    energy_part_param_.CENTER_R_CONTOUR_AREA_MAX = 100000;
    energy_part_param_.CENTER_R_CONTOUR_AREA_MIN = 0;
    energy_part_param_.CENTER_R_CONTOUR_LENGTH_MIN = 10;
    energy_part_param_.CENTER_R_CONTOUR_WIDTH_MIN = 10;
    energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX = 30;
    energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX = 30;
    energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX = 3;
    energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN = 1;
    energy_part_param_.CENTER_R_CONTOUR_AREA_RATIO_MIN = 0.7;
    energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN = 10;

    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MAX = 17000;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MIN = 0;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MIN = 90;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MIN = 35;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MAX = 140;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MAX = 60;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MAX = 3;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MIN = 1;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MAX = 0.55;
    energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MIN = 0.25;

    energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX = 100000;
    energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN = 0;
    energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN = 50;
    energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN = 3;
    energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX = 90;
    energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX = 20;
    energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX = 12;
    energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 4;
    energy_part_param_.FLOW_STRIP_CONTOUR_AREA_RATIO_MIN = 0.5;
    energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN = 300;

	energy_part_param_.TWIN_ANGEL_MAX = 10;
	energy_part_param_.INTERSETION_CONTOUR_AREA_MIN = 60;

	energy_part_param_.TARGET_CHANGE_DISTANCE_MAX = 20;
    energy_part_param_.TWIN_POINT_MAX = 20;
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数对能量机关旋转方向进行初始化
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initRotation() {
	if (target_polar_angle >= -180 && last_target_polar_angle >= -180
	    && fabs(target_polar_angle - last_target_polar_angle) < 30) {
	    //target_polar_angle和last_target_polar_angle的初值均为1000，大于-180表示刚开始几帧不要
	    //若两者比较接近，则说明没有切换目标，因此可以用于顺逆时针的判断
		if (target_polar_angle < last_target_polar_angle) clockwise_rotation_init_cnt++;
		else if (target_polar_angle > last_target_polar_angle) anticlockwise_rotation_init_cnt++;
	}
    //由于刚开始圆心判断不准，角度变化可能计算有误，因此需要在角度正向或逆向变化足够大时才可确定是否为顺逆时针
	if (clockwise_rotation_init_cnt == 30) {
        energy_rotation_direction = CLOCKWISE;//顺时针变化30次，确定为顺时针
		cout << "rotation: " << energy_rotation_direction << endl;
		energy_rotation_init = false;
	}
	else if (anticlockwise_rotation_init_cnt == 30) {
        energy_rotation_direction = ANTICLOCKWISE;//逆时针变化30次，确定为顺时针
		cout << "rotation: " << energy_rotation_direction << endl;
		energy_rotation_init = false;
	}
    last_target_polar_angle = target_polar_angle;
}
