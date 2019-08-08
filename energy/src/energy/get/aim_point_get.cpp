//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;

extern McuData mcu_data;

//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(cv::Point target_point_) {
    float target_polar_angle_ = static_cast<float>(180 / PI * atan2(-1 * (target_point_.y - circle_center_point.y),
                                                                    (target_point_.x - circle_center_point.x)));

    if (target_polar_angle_ > 0 && target_polar_angle_ <= 90) {
        extra_delta_x = EXTRA_DELTA_X * (90 - target_polar_angle_) / 90;
        extra_delta_y = -EXTRA_DELTA_Y * target_polar_angle_ / 90;
    } else if (target_polar_angle_ > 90 && target_polar_angle_ < 180) {
        extra_delta_x = -EXTRA_DELTA_X * (target_polar_angle_ - 90) / 90;
        extra_delta_y = -EXTRA_DELTA_Y * (180 - target_polar_angle_) / 90;
    } else {
        extra_delta_x = 0;
        extra_delta_y = 0;
    }

    int compensate_yaw = 0, compensate_pitch = 0;
    if (mcu_data.enemy_color == ENEMY_BLUE) {
        compensate_yaw = RED_COMPENSATE_YAW;
        compensate_pitch = RED_COMPENSATE_PITCH;
    } else if (mcu_data.enemy_color == ENEMY_RED) {
        compensate_yaw = BLUE_COMPENSATE_YAW;
        compensate_pitch = BLUE_COMPENSATE_PITCH;
    }

    double dx = -(target_point_.x - 320 - compensate_yaw - mcu_data.delta_x - manual_delta_x - extra_delta_x);
    double dy = -(target_point_.y - 240 - compensate_pitch - mcu_data.delta_y - manual_delta_y - extra_delta_y);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
//    cout << "yaw: " << yaw_rotation << '\t' << "pitch: " << pitch_rotation << endl;
//    cout << "mcu_data.delta_x: " << mcu_data.delta_x << '\t' << "mcu_data.delta_y: " << mcu_data.delta_y << endl;
//    cout << "manual delta: " << manual_delta_x << '\t' << manual_delta_y << endl;

}
