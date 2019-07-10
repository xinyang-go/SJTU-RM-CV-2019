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
// 此函数为能量机关构造函数，只要程序不重启就不会重新构造
// ---------------------------------------------------------------------------------------------------------------------
Energy::Energy(Serial &u, uint8_t &color):serial(u),ally_color(color),
        src_blue(SRC_HEIGHT, SRC_WIDTH, CV_8UC1),
        src_red(SRC_HEIGHT, SRC_WIDTH, CV_8UC1)
{
	initEnergy();
	initEnergyPartParam();

    energy_rotation_init = false;
    isGimble = true;
    isChassis = false;
    save_new_mark = false;

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



//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关析构函数，设置为默认
// ---------------------------------------------------------------------------------------------------------------------
Energy::~Energy() = default;



//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关再初始化函数，如果未重启程序但重新进入能量机关，则会进行初始化，但不会将save_new_mark置为false
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setEnergyRotationInit() {
	initEnergy();
	initEnergyPartParam();

	energy_rotation_init = true;
    isGimble = true;
    isChassis = false;

	if(save_new_mark){
        FILE *fp = fopen(PROJECT_DIR"/Mark/mark.txt", "r");
        if(fp){
            fscanf(fp,"%f %f",&origin_yaw,&origin_pitch);
            fclose(fp);
        }
	}
}
