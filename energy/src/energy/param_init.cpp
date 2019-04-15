//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::initEnergyPartParam() {

    energy_part_param_.RPM = 10;
    energy_part_param_.HIT_TIME = 1.5;

	energy_part_param_.GRAY_THRESH = 240;
	energy_part_param_.SPLIT_GRAY_THRESH = 80;
	energy_part_param_.FAN_GRAY_THRESH = 75;
	energy_part_param_.ARMOR_GRAY_THRESH = 80;

	energy_part_param_.FAN_CONTOUR_AREA_MAX = 17000;
	energy_part_param_.FAN_CONTOUR_AREA_MIN = 7000;
	energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 150;
	energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 50;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
	energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;

	energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
	energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 50;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 25;
	energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 80;
	energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 50;
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


