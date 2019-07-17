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
    is_mark = false;
    is_guessing = false;
    is_predicting = true;
    energy_mode_init = true;
    energy_rotation_init = true;
    manual_mark = false;
    auto_mark = false;
    start_guess = false;
    change_target = false;

    last_mark = 0;

    radius = 0;

    send_cnt = 0;
    last_fans_cnt = 0;
    guess_devide = 0;
    energy_rotation_direction = ANTICLOCKWISE;
    clockwise_rotation_init_cnt = 0;
    anticlockwise_rotation_init_cnt = 0;
    last_mode = -1;//既不是大符也不是小符

    target_polar_angle = -1000;
    last_target_polar_angle = -1000;
    guess_polar_angle = -1000;
    last_base_angle = -1000;
    predict_rad = 25;
    attack_distance = ATTACK_DISTANCE;
    center_delta_yaw = 1000;
    center_delta_pitch = 1000;
    yaw_rotation = 0;
    pitch_rotation = 0;
    shoot = 0;

    circle_center_point = Point(0, 0);
    target_point = Point(0, 0);
    last_target_point = Point(0, 0);
    guess_point = Point(0, 0);
    predict_point = Point(0, 0);

    fans.clear();
    armors.clear();
    all_target_armor_centers.clear();
    while(!recent_target_armor_centers.empty())recent_target_armor_centers.pop();


}


//----------------------------------------------------------------------------------------------------------------------
// 此函数对能量机关参数进行初始化
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initEnergyPartParam() {
    gimbal_energy_part_param_.GRAY_THRESH = 140;//home
//    gimbal_energy_part_param_.GRAY_THRESH = 200;//official
//    gimbal_energy_part_param_.GRAY_THRESH = 225;
    gimbal_energy_part_param_.SPLIT_GRAY_THRESH = 230;
    gimbal_energy_part_param_.FAN_GRAY_THRESH = 75;
    gimbal_energy_part_param_.ARMOR_GRAY_THRESH = 80;

    gimbal_energy_part_param_.FAN_CONTOUR_AREA_MAX = 6600;
    gimbal_energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
    gimbal_energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 80;
    gimbal_energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 100;
    gimbal_energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 20;
    gimbal_energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 50;
    gimbal_energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
    gimbal_energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;
    gimbal_energy_part_param_.FAN_CONTOUR_AREA_RATIO_MIN = 0.65;
    gimbal_energy_part_param_.FAN_NON_ZERO_RATE_MAX = 0.8;
    gimbal_energy_part_param_.FAN_NON_ZERO_RATE_MIN = 0.48;
//    gimbal_energy_part_param_.FAN_NON_ZERO_RATE_MAX = 0.3;
//    gimbal_energy_part_param_.FAN_NON_ZERO_RATE_MIN = 0.16;

    gimbal_energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
    gimbal_energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
    gimbal_energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 16;
    gimbal_energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 32;
    gimbal_energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 5;
    gimbal_energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 20;
    gimbal_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
    gimbal_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;

    gimbal_energy_part_param_.CENTER_R_CONTOUR_AREA_MAX = 100000;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_AREA_MIN = 0;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MIN = 7;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX = 25;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MIN = 7;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX = 25;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX = 3;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN = 1;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_AREA_RATIO_MIN = 0.7;
    gimbal_energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN = 10;

    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MAX = 3000;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MIN = 1000;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MIN = 60;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MAX = 100;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MIN = 20;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MAX = 50;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MAX = 3;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MIN = 1;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MAX = 0.65;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MIN = 0.34;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX = 0.65;
    gimbal_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN = 0.34;
//    gimbal_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX = 0.2;
//    gimbal_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN = 0.08;

    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX = 100000;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN = 0;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN = 40;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX = 65;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN = 8;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX = 20;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX = 12;
//    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 4;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 2.7;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_RATIO_MIN = 0.5;
    gimbal_energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN = 117;

    gimbal_energy_part_param_.TWIN_ANGEL_MAX = 10;
    gimbal_energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN = 40;



    chassis_energy_part_param_.GRAY_THRESH = 120;//home
//    chassis_energy_part_param_.GRAY_THRESH = 200;//official
//    chassis_energy_part_param_.GRAY_THRESH = 225;
    chassis_energy_part_param_.SPLIT_GRAY_THRESH = 230;
    chassis_energy_part_param_.FAN_GRAY_THRESH = 75;
    chassis_energy_part_param_.ARMOR_GRAY_THRESH = 80;

    chassis_energy_part_param_.FAN_CONTOUR_AREA_MAX = 17000;
    chassis_energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 90;
    chassis_energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 140;
    chassis_energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 35;
    chassis_energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 65;
    chassis_energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
    chassis_energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;
    chassis_energy_part_param_.FAN_CONTOUR_AREA_RATIO_MIN = 0.6;
    chassis_energy_part_param_.FAN_NON_ZERO_RATE_MAX = 0.8;
    chassis_energy_part_param_.FAN_NON_ZERO_RATE_MIN = 0.48;
//    chassis_energy_part_param_.FAN_NON_ZERO_RATE_MAX = 0.3;
//    chassis_energy_part_param_.FAN_NON_ZERO_RATE_MIN = 0.16;

    chassis_energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
    chassis_energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 30;
    chassis_energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 50;
    chassis_energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 13;
    chassis_energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 33;
    chassis_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
    chassis_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;
    chassis_energy_part_param_.ARMOR_CONTOUR_AREA_RATIO_MIN = 0.7;

    chassis_energy_part_param_.CENTER_R_CONTOUR_AREA_MAX = 100000;
    chassis_energy_part_param_.CENTER_R_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MIN = 10;
    chassis_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX = 30;
    chassis_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MIN = 10;
    chassis_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX = 30;
    chassis_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX = 3;
    chassis_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN = 1;
    chassis_energy_part_param_.CENTER_R_CONTOUR_AREA_RATIO_MIN = 0.7;
    chassis_energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN = 10;

    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MAX = 17000;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MIN = 90;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MAX = 140;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MIN = 35;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MAX = 60;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MAX = 3;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MIN = 1;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MAX = 0.55;
    chassis_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MIN = 0.25;
    chassis_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX = 0.48;
    chassis_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN = 0.25;
//    chassis_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX = 0.2;
//    chassis_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN = 0.08;

    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX = 100000;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN = 55;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX = 95;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN = 8;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX = 25;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX = 12;
//    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 4;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 2.7;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_RATIO_MIN = 0.5;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN = 300;

    chassis_energy_part_param_.TWIN_ANGEL_MAX = 10;
    chassis_energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN = 60;

    chassis_energy_part_param_.TARGET_CHANGE_DISTANCE_MAX = 20;
    chassis_energy_part_param_.TWIN_POINT_MAX = 20;
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
    } else if (anticlockwise_rotation_init_cnt == 30) {
        energy_rotation_direction = ANTICLOCKWISE;//逆时针变化30次，确定为顺时针
        cout << "rotation: " << energy_rotation_direction << endl;
        energy_rotation_init = false;
    }
    last_target_polar_angle = target_polar_angle;
}
