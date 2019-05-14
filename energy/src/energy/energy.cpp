//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

Energy::Energy(Serial &u, int &ally_color):serial(u),ally_color_(ally_color),
        src_blue(SRC_HEIGHT, SRC_WIDTH, CV_8UC1),
        src_red(SRC_HEIGHT, SRC_WIDTH, CV_8UC1)
{
    isSendTarget = false;

	fans_cnt = 0;
	armors_cnt = 0;
	cycle_center = Point(0, 0);
	target_center = Point(0, 0);
	last_target_center = Point(0, 0);
	hit_point = Point(0,0);
	target_position = -1;
	last_target_position = -1;
    last_hit_position = 20000;
	target_armor = -1;
	radius = 0;

    ally_color_ = ALLY_RED;
    energy_part_rotation = CLOCKWISE;
    attack_distance = ATTACK_DISTANCE;
	count = 1;
	last_fans_cnt = 0;
	last_armors_cnt = 0;
	send_cnt = 0;

    rectified_focal_length = 1000;
	theta = 0;
	phi = 0;
	yaw_rotation = 0;
	pitch_rotation = 0;

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

	initEnergyPartParam();
}

Energy::~Energy() = default;


void Energy::setAllyColor(int color)
{
    ally_color_ = color;
}

void Energy::setRotation(int rotation){
	energy_part_rotation = rotation;
}

