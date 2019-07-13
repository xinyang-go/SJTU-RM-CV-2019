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

    energy_rotation_init = false;
    isBig = false;
    isSmall = false;
    isgimbal = true;
    isChassis = false;
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

    energy_rotation_init = true;
    isBig = false;
    isSmall = false;
    isgimbal = true;
    isChassis = false;
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关再初始化函数
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setBigEnergyInit() {
    initEnergy();
    initEnergyPartParam();

    energy_rotation_init = true;
    isBig = true;
    isSmall = false;
    isgimbal = true;
    isChassis = false;
}

//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关再初始化函数
// ---------------------------------------------------------------------------------------------------------------------
void Energy::setSmallEnergyInit() {
    initEnergy();
    initEnergyPartParam();

    isBig = false;
    isSmall = true;
    isgimbal = true;
    isChassis = false;
}
