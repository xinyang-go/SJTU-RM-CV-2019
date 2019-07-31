//
// Created by sun on 19-7-6.
//

#include "energy/energy.h"
#include "energy/constant.h"
#include "config/setconfig.h"

using namespace std;
using namespace cv;

extern mcu_data mcuData;

//----------------------------------------------------------------------------------------------------------------------
// 此函数通过自瞄逻辑击打目标点，用于大符的自动对心和小符直接打击
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAimPoint(cv::Point target_point_) {
    float target_polar_angle_ = static_cast<float>(180 / PI * atan2(-1 * (target_point_.y - circle_center_point.y),
                                                                    (target_point_.x - circle_center_point.x)));

    if (target_polar_angle_ > 0 && target_polar_angle_ <= 90) {
        extra_delta_x = EXTRA_DELTA_X * (90 - target_polar_angle_) / 90;
        extra_delta_y = - EXTRA_DELTA_Y * target_polar_angle_  / 90;
    } else if (target_polar_angle_ > 90 && target_polar_angle_ < 180) {
        extra_delta_x = - EXTRA_DELTA_X * (target_polar_angle_ - 90) / 90;
        extra_delta_y = - EXTRA_DELTA_Y * (180 - target_polar_angle_) / 90;
    } else {
        extra_delta_x = 0;
        extra_delta_y = 0;
    }

    double dx = -(target_point_.x - 320 - COMPENSATE_YAW - mcuData.delta_x - manual_delta_x - extra_delta_x);
    double dy = -(target_point_.y - 240 - COMPENSATE_PITCH - mcuData.delta_y - manual_delta_y - extra_delta_y);
    yaw_rotation = atan(dx / FOCUS_PIXAL) * 180 / PI;
    pitch_rotation = atan(dy / FOCUS_PIXAL) * 180 / PI;
//    cout << "yaw: " << yaw_rotation << '\t' << "pitch: " << pitch_rotation << endl;
//    cout << "mcuData.delta_x: " << mcuData.delta_x << '\t' << "mcuData.delta_y: " << mcuData.delta_y << endl;
//    cout << "manual delta: " << manual_delta_x << '\t' << manual_delta_y << endl;

}
