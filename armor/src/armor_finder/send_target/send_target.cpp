//
// Created by xinyang on 19-7-11.
//

#include <armor_finder/armor_finder.h>
#include <config/setconfig.h>
#include <log.h>

static bool sendTarget(Serial &serial, double x, double y, double z, uint16_t shoot_delay) {
    static short x_tmp, y_tmp, z_tmp;
    uint8_t buff[10];

#ifdef WITH_COUNT_FPS
    static time_t last_time = time(nullptr);
    static int fps;
    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "Armor: fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
        fps = 0;
    }
    fps += 1;
#endif

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
    buff[7] = static_cast<char>((shoot_delay >> 8) & 0xFF);
    buff[8] = static_cast<char>((shoot_delay >> 0) & 0xFF);
    buff[9] = 'e';
//    if(buff[7]<<8 | buff[8])
//        cout << (buff[7]<<8 | buff[8]) << endl;
    return serial.WriteData(buff, sizeof(buff));
}

bool ArmorFinder::sendBoxPosition(uint16_t shoot_delay) {
    if (target_box.rect == cv::Rect2d()) return false;
    if (shoot_delay) {
        LOGM(STR_CTR(WORD_BLUE, "next box %dms"), shoot_delay);
    }
    auto rect = target_box.rect;
    double dx = rect.x + rect.width / 2 - IMAGE_CENTER_X;
    double dy = rect.y + rect.height / 2 - IMAGE_CENTER_Y;
    double yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
    double pitch = atan(dy / FOCUS_PIXAL) * 180 / PI;
    double dist = DISTANCE_HEIGHT / rect.height;
    return sendTarget(serial, yaw, -pitch, dist, shoot_delay);
}
