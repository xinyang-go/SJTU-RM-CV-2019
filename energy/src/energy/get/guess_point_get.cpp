//
// Created by sun on 19-7-11.
//
#include "energy/energy.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数获得猜测的击打点
// ---------------------------------------------------------------------------------------------------------------------
void Energy::guessTarget() {
    vector<int> all_fan_angles;
    float angle;
    for (const auto &fan : fans) {
        angle = static_cast<float>(180 / PI * atan2(-1 * (fan.center.y - circle_center_point.y),
                                                    (fan.center.x - circle_center_point.x)));
        if (angle < 0)angle += 360;
        all_fan_angles.emplace_back(angle);
    }
    angle = target_polar_angle;
    if (angle < 0)angle += 360;
    all_fan_angles.emplace_back(angle);

    sort(all_fan_angles.begin(), all_fan_angles.end());
    float min_angle = all_fan_angles.at(0);
    float max_angle = all_fan_angles.at(all_fan_angles.size() - 1);
    float base_angle = min_angle;
    while (base_angle > 72)base_angle -= 72;
    if (startguessing) {
        int i = 0;
        for (i = 1; i < all_fan_angles.size(); ++i) {
            if (abs(min_angle + 72 * i - all_fan_angles.at(i)) > energy_part_param_.TWIN_ANGEL_MAX) {
                guess_polar_angle = min_angle + 72 * i;
                break;
            }
        }
        if (i == all_fan_angles.size()) guess_polar_angle = max_angle + 72;
        startguessing = false;
        guess_devide = devide(guess_polar_angle);
    } else if (abs(base_angle - last_base_angle) > 20) {
        if (energy_rotation_direction == CLOCKWISE)guess_devide = (guess_devide + 4) % 5;
        else guess_devide = (guess_devide + 1) % 5;
        guess_polar_angle = base_angle + guess_devide * 72;
    } else {
        guess_polar_angle = base_angle + guess_devide * 72;
    }
    if (guess_polar_angle > 180)guess_polar_angle -= 360;
    radius = pointDistance(target_point, circle_center_point);
    guess_point.x = circle_center_point.x + radius * cos(PI / 180.0 * guess_polar_angle);
    guess_point.y = circle_center_point.y - radius * sin(PI / 180.0 * guess_polar_angle);
    last_base_angle = base_angle;
}
