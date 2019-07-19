//
// Created by xinyang on 19-7-11.
//

#include <armor_finder/armor_finder.h>

static bool sendTarget(Serial &serial, double x, double y, double z) {
    static short x_tmp, y_tmp, z_tmp;
    static time_t last_time = time(nullptr);
    static int fps;
    uint8_t buff[8];

    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
        fps = 0;
    }
    fps += 1;

    x_tmp = static_cast<short>(x * (32768 - 1) / 100);
    y_tmp = static_cast<short>(y * (32768 - 1) / 100);
    z_tmp = static_cast<short>(z * (32768 - 1) / 1000);

    buff[0] = 's';
    buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
    buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
    buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
    buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
    buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
    buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
    buff[7] = 'e';

    return serial.WriteData(buff, sizeof(buff));
}

bool ArmorFinder::sendBoxPosition() {
    if(armor_box.rect == cv::Rect2d()) return false;
    auto rect = armor_box.rect;
    double dx = rect.x + rect.width / 2 - 320;
    double dy = rect.y + rect.height / 2 - 240 - 20;
    double yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
    double pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
    double dist = DISTANCE_HEIGHT / rect.height;
//    cout << yaw << endl;
    return sendTarget(serial, yaw, -pitch, dist);
}
