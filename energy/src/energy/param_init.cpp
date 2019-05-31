//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::initEnergy() {
	isSendTarget = false;
	isMark = false;

	fans_cnt = 0;
	armors_cnt = 0;
	cycle_center = Point(0, 0);
	target_center = Point(0, 0);
	last_target_center = Point(0, 0);
	hit_point = Point(0, 0);
	target_position = -1000;
	last_target_position = -1000;
	last_hit_position = 20000;
	target_armor = -1000;
    last_target_armor = -1000;
	radius = 0;

	//    ally_color = ALLY_RED;
	energy_part_rotation = CLOCKWISE;
	attack_distance = ATTACK_DISTANCE;
	count = 1;
	last_fans_cnt = 0;
	last_armors_cnt = 0;
	send_cnt = 0;

	//rectified_focal_length = 1000;
	//theta = 0;
	//phi = 0;
	yaw_rotation = 0;
	pitch_rotation = 0;
	last_mark = 0;

    red_origin_yaw = -0.35;
    red_origin_pitch = 15.11719;
    blue_origin_yaw = -0.439453;
    blue_origin_pitch = 15.688477;

	target_cnt = 0;
    target_cnt_flag = true;

	isLeftVertexFound = -1;
	isTopVertexFound = -1;
	isRightVertexFound = -1;
	isBottomVertexFound = -1;

	left = Point(640, 480);
	right = Point(0, 0);
	top = Point(640, 480);
	bottom = Point(0, 0);

	position_mode = 0;
	last_position_mode = 0;

	energy_rotation_init = false;

	fans.clear();
	armors.clear();
	fanPosition.clear();
	armorPosition.clear();
	Armor_center.clear();
	first_armor_centers.clear();
	all_armor_centers.clear();

	clockwise_rotation_init_cnt = 0;
	anticlockwise_rotation_init_cnt = 0;
}

void Energy::initEnergyPartParam() {

    energy_part_param_.RPM = 10;
    energy_part_param_.HIT_TIME = 1.14;

	energy_part_param_.GRAY_THRESH = 240;
	energy_part_param_.SPLIT_GRAY_THRESH = 60;
	energy_part_param_.FAN_GRAY_THRESH = 75;
	energy_part_param_.ARMOR_GRAY_THRESH = 80;

	energy_part_param_.FAN_CONTOUR_AREA_MAX = 17000;
	energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
	energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 90;
    energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 140;
	energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 35;
    energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 60;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;

	energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
	energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 30;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 15;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 50;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 45;
	energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
	energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;

	energy_part_param_.TWIN_ANGEL_MAX = 10;

	lift_height_.LIFT_0 = 0;
    lift_height_.LIFT_30 = 0;
    lift_height_.LIFT_60 = 0;
    lift_height_.LIFT_90 = 10;
    lift_height_.LIFT_minus_30 = 0;
    lift_height_.LIFT_minus_60 = 0;
    lift_height_.LIFT_minus_90 = 0;

}


void Energy::initRotation() {
	target_position = target_armor;
//	cout << "target position: " << target_position << '\t' << "last target position: " << last_target_position << endl;
	if (target_position >= -180 && last_target_position >= -180 && fabs(target_position - last_target_position) < 30) {
		if (target_position < last_target_position) clockwise_rotation_init_cnt++;
		else if (target_position > last_target_position) anticlockwise_rotation_init_cnt++;
	}

	if (clockwise_rotation_init_cnt == 30) {
		energy_part_rotation = CLOCKWISE;
		cout << "rotation: " << energy_part_rotation << endl;
		energy_rotation_init = false;
	}
	else if (anticlockwise_rotation_init_cnt == 30) {
		energy_part_rotation = ANTICLOCKWISE;
		cout << "rotation: " << energy_part_rotation << endl;
		energy_rotation_init = false;
	}
//	else cout << clockwise_rotation_init_cnt <<'\t'<<anticlockwise_rotation_init_cnt<< endl;

	last_target_position = target_position;
}
