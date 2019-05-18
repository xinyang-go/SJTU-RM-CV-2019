//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

extern uint8_t last_state;

Energy::Energy(Serial &u, uint8_t &enemy_color):serial(u),ally_color(enemy_color),
        src_blue(SRC_HEIGHT, SRC_WIDTH, CV_8UC1),
        src_red(SRC_HEIGHT, SRC_WIDTH, CV_8UC1)
{
	initEnergy();
	initEnergyPartParam();
}

Energy::~Energy() = default;

//
//void Energy::setAllyColor(int color)
//{
//    ally_color_ = color;
//}

void Energy::setRotation(int rotation){
	energy_part_rotation = rotation;
}

void Energy::setEnergyRotationInit() {
	initEnergy();
	initEnergyPartParam();
	energy_rotation_init = true;
}
