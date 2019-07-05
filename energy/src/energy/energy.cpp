//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

extern uint8_t last_state;

Energy::Energy(Serial &u, uint8_t &color):serial(u),ally_color(color),
        src_blue(SRC_HEIGHT, SRC_WIDTH, CV_8UC1),
        src_red(SRC_HEIGHT, SRC_WIDTH, CV_8UC1)
{
	initEnergy();
	initEnergyPartParam();

    save_new_mark = true;

    if(ally_color == ALLY_RED){
        origin_yaw = red_origin_yaw;
        origin_pitch = red_origin_pitch;
    }
    else if(ally_color == ALLY_BLUE){
        origin_yaw = blue_origin_yaw;
        origin_pitch = blue_origin_pitch;
    }
    else {
        LOGE_INFO("ally color_run");
    }
}

Energy::~Energy() = default;

void Energy::setEnergyRotationInit() {
	initEnergy();
	initEnergyPartParam();
	energy_rotation_init = true;

	if(!save_new_mark){
        FILE *fp = fopen(PROJECT_DIR"/Mark/mark.txt", "r");
        if(fp){
            fscanf(fp,"%f %f",&origin_yaw,&origin_pitch);
            fclose(fp);
        }
	}
}
