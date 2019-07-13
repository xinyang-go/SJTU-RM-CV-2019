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
    isMark = false;
    isPredicting = true;
    isGuessing = false;
    manual_mark = false;
    auto_mark = false;
    energy_mode_init = true;
    circle_center_point = Point(0, 0);
    target_point = Point(0, 0);
    last_target_point = Point(0, 0);
    guess_point = Point(0, 0);
    predict_point = Point(0, 0);
    target_polar_angle = -1000;
    guess_polar_angle = -1000;
    last_target_polar_angle = -1000;
    radius = 0;
    energy_rotation_direction = ANTICLOCKWISE;
    attack_distance = ATTACK_DISTANCE;
    last_mode = -1;//既不是大符也不是小符
    last_fans_cnt = 0;
    send_cnt = 0;
    yaw_rotation = 0;
    pitch_rotation = 0;
    last_mark = 0;

    shoot = false;
    guess_devide = 0;
    startguessing = false;
    predict_rad = 20;

    fans.clear();
    armors.clear();

    all_target_armor_centers.clear();
    while(!recent_target_armor_centers.empty())recent_target_armor_centers.pop();

    clockwise_rotation_init_cnt = 0;
    anticlockwise_rotation_init_cnt = 0;

    destroyAllWindows();
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数对能量机关参数进行初始化
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initEnergyPartParam() {
    gimble_energy_part_param_.GRAY_THRESH = 160;
    gimble_energy_part_param_.SPLIT_GRAY_THRESH = 180;
    gimble_energy_part_param_.FAN_GRAY_THRESH = 75;
    gimble_energy_part_param_.ARMOR_GRAY_THRESH = 80;

    gimble_energy_part_param_.FAN_CONTOUR_AREA_MAX = 6600;
    gimble_energy_part_param_.FAN_CONTOUR_AREA_MIN = 0;
    gimble_energy_part_param_.FAN_CONTOUR_LENGTH_MIN = 56;
    gimble_energy_part_param_.FAN_CONTOUR_LENGTH_MAX = 88;
    gimble_energy_part_param_.FAN_CONTOUR_WIDTH_MIN = 21;
    gimble_energy_part_param_.FAN_CONTOUR_WIDTH_MAX = 40;
    gimble_energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX = 4;
    gimble_energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN = 1;
    gimble_energy_part_param_.FAN_NON_ZERO_RATE_MAX = 0.8;
    gimble_energy_part_param_.FAN_NON_ZERO_RATE_MIN = 0.48;

    gimble_energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
    gimble_energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
    gimble_energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 18;
    gimble_energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 32;
    gimble_energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 10;
    gimble_energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 30;
    gimble_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX = 3;
    gimble_energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN = 1;

    gimble_energy_part_param_.CENTER_R_CONTOUR_AREA_MAX = 100000;
    gimble_energy_part_param_.CENTER_R_CONTOUR_AREA_MIN = 0;
    gimble_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MIN = 7;
    gimble_energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX = 19;
    gimble_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MIN = 7;
    gimble_energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX = 19;
    gimble_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX = 3;
    gimble_energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN = 1;
    gimble_energy_part_param_.CENTER_R_CONTOUR_AREA_RATIO_MIN = 0.7;
    gimble_energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN = 10;

    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MAX = 17000;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MIN = 0;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MIN = 56;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MAX = 88;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MIN = 21;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MAX = 40;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MAX = 3;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MIN = 1;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MAX = 0.55;
    gimble_energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MIN = 0.25;
    gimble_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX = 0.48;
    gimble_energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN = 0.25;

    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX = 100000;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN = 0;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN = 31;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX = 57;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN = 2;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX = 13;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX = 12;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 4;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_RATIO_MIN = 0.5;
    gimble_energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN = 117;

    gimble_energy_part_param_.TWIN_ANGEL_MAX = 10;
    gimble_energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN = 24;



    chassis_energy_part_param_.GRAY_THRESH = 225;
    chassis_energy_part_param_.SPLIT_GRAY_THRESH = 60;
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

    chassis_energy_part_param_.ARMOR_CONTOUR_AREA_MAX = 100000;
    chassis_energy_part_param_.ARMOR_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN = 30;
    chassis_energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX = 50;
    chassis_energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN = 15;
    chassis_energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX = 45;
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

    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX = 100000;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN = 0;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN = 50;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX = 90;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN = 3;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX = 20;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX = 12;
    chassis_energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN = 4;
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
