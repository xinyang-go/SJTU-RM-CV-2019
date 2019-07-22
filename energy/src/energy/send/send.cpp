//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include <iostream>
#include "log.h"

using namespace std;

//----------------------------------------------------------------------------------------------------------------------
// 此函数用于发送数据给主控板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::sendTarget(Serial& serial, float x, float y, float z){
    short x_tmp, y_tmp, z_tmp;
    uint8_t buff[10];

#ifdef WITH_COUNT_FPS
    static auto last_time = time(nullptr);
    static int fps = 0;
    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
        fps = 0;
    }
    fps += 1;
#endif

    x_tmp = static_cast<short>(x * (32768 - 1) / 100);
    y_tmp = static_cast<short>(y * (32768 - 1) / 100);
    z_tmp = static_cast<short>(z * (32768 - 1) / 100);
    buff[0] = 's';
    buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
    buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
    buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
    buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
    buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
    buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
    buff[9] = 'e';
    serial.WriteData(buff, sizeof(buff));
    send_cnt+=1;
//    LOGM(STR_CTR(WORD_LIGHT_PURPLE, "send"));
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于发送数据给主控板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::sendTarget(Serial& serial, float x, float y, float z, uint16_t u){
    short x_tmp, y_tmp, z_tmp;
    uint8_t buff[10];

#ifdef WITH_COUNT_FPS
    static auto last_time = time(nullptr);
    static int fps = 0;
    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
        fps = 0;
    }
    fps += 1;
#endif

    x_tmp = static_cast<short>(x * (32768 - 1) / 100);
    y_tmp = static_cast<short>(y * (32768 - 1) / 100);
    z_tmp = static_cast<short>(z * (32768 - 1) / 100);
    buff[0] = 's';
    buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
    buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
    buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
    buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
    buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
    buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
    buff[7] = static_cast<char>((u >> 8) & 0xFF);
    buff[8] = static_cast<char>((u >> 0) & 0xFF);;
    buff[9] = 'e';
    serial.WriteData(buff, sizeof(buff));
    send_cnt+=1;
//    LOGM(STR_CTR(WORD_LIGHT_PURPLE, "send"));
}
