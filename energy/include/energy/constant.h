//
// Created by xixiliadorabarry on 1/24/19.
//
#ifndef CONSTANT_H
#define CONSTANT_H

#define d2r (CV_PI / 180.0)

const int ALLY_BLUE = 123;
const int ALLY_RED = 456;
const int SRC_WIDTH_CAMERA = 640;
const int SRC_HEIGHT_CAMERA = 480;
const int SRC_WIDTH = 320;
const int SRC_HEIGHT = 240;
const double PI = 3.1415926;
const int CLOCKWISE = 1;
const int ANTICLOCKWISE = -1;
const float ATTACK_DISTANCE = 770;//cm
const double WHOLE_FAN = 80;//cm
const double ARMOR_CENTER_TO_CYCLE_CENTER = 75;//cm
//const double ARMOR_CENTER_TO_CYCLE_CENTER = 71;//cm
const int EXTRACT_POINT_X = 200;
const int EXTRACT_POINT_Y = 20;
const int EXTRACT_WIDTH = 240;
const int EXTRACT_HEIGHT = 180;

//以摄像头正方向位y轴
const int GM_L = 14;//云台摄像头z方向
const int GM_X = 15;//云台摄像头x方向
const int GM_H = 16;//云台摄像头y方向

//const double STRETCH = 231.0/640.0;//实际距离与图像伸缩比
const double STRETCH = 0.34;

const int ZERO_POINT_X = 281;
const int ZERO_POINT_Y = 188;
const double YAW_ORIGIN_RAD = PI/180*2.25;
const double PITCH_ORIGIN_RAD = PI/180*14.85;

const double LIFT_HEIGHT = 20;//云台抬升高度

#endif //CONSTANT_H

