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
Energy::Energy(Serial &u, uint8_t &color) : serial(u), ally_color(color),
                                            src_blue(SRC_HEIGHT, SRC_WIDTH, CV_8UC1),
                                            src_red(SRC_HEIGHT, SRC_WIDTH, CV_8UC1) {
    initEnergy();
    initEnergyPartParam();

    is_big = false;
    is_small = false;
    is_gimbal = true;
    is_chassis = false;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关析构函数，设置为默认
// ---------------------------------------------------------------------------------------------------------------------
Energy::~Energy() = default;


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关再初始化函数
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setEnergyInit() {
    initEnergy();
    initEnergyPartParam();

    is_big = false;
    is_small = false;
    is_gimbal = true;
    is_chassis = false;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关再初始化函数
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setBigEnergyInit() {
    initEnergy();
    initEnergyPartParam();

    getsystime(time_start_energy);

    is_big = true;
    is_small = false;
    is_gimbal = true;
    is_chassis = false;

    FILE *fp = fopen(PROJECT_DIR"/Mark/delta.txt", "r");
    if (fp) {
        fscanf(fp, "delta_x: %d, delta_y: %d", &manual_delta_x, &manual_delta_y);
        fclose(fp);
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关再初始化函数
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setSmallEnergyInit() {
    initEnergy();
    initEnergyPartParam();

    is_big = false;
    is_small = true;
    is_gimbal = true;
    is_chassis = false;

    FILE *fp = fopen(PROJECT_DIR"/Mark/delta.txt", "r");
    if (fp) {
        fscanf(fp, "%d %d", &manual_delta_x, &manual_delta_y);
        fclose(fp);
    }
}