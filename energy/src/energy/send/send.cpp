//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include <iostream>
#include "log.h"
#include "config/setconfig.h"

using namespace std;

#define MINMAX(value, min, max) value = ((value) < (min)) ? (min) : ((value) > (max) ? (max) : (value))

//----------------------------------------------------------------------------------------------------------------------
// 此函数用于发送能量机关数据
// ---------------------------------------------------------------------------------------------------------------------
void Energy::sendEnergy() {
    if (is_big) {
        if (camera_cnt == 1) {
            sum_yaw += yaw_rotation;
            sum_pitch += pitch_rotation;
            if (ROBOT_ID == 3 || ROBOT_ID == 4 || ROBOT_ID == 8) {
                MINMAX(sum_yaw, -100, 100);
                MINMAX(sum_yaw, -100, 100);
            } else if (ROBOT_ID == 7) {
                float yaw_I_component = BIG_YAW_AIM_KI * sum_yaw;
                float pitch_I_component = BIG_PITCH_AIM_KI * sum_pitch;
//                MINMAX(yaw_I_component, -3, 3);
//                MINMAX(pitch_I_component, -3, 3);
                MINMAX(yaw_I_component, -2, 2);
                MINMAX(pitch_I_component, -2, 2);
            }

            double tmp_yaw = yaw_rotation;
            double tmp_pitch = pitch_rotation;
            if (mcu_data.mark == 1) {
                yaw_rotation = TRY_BIG_YAW_AIM_KP * yaw_rotation + TRY_BIG_YAW_AIM_KI * sum_yaw +
                               TRY_BIG_YAW_AIM_KD * (yaw_rotation - last_yaw);
                pitch_rotation = TRY_BIG_PITCH_AIM_KP * pitch_rotation + TRY_BIG_PITCH_AIM_KI * sum_pitch +
                                 TRY_BIG_PITCH_AIM_KD * (pitch_rotation - last_pitch);
            } else {
                yaw_rotation = BIG_YAW_AIM_KP * yaw_rotation + BIG_YAW_AIM_KI * sum_yaw +
                               BIG_YAW_AIM_KD * (yaw_rotation - last_yaw);
                pitch_rotation = BIG_PITCH_AIM_KP * pitch_rotation + BIG_PITCH_AIM_KI * sum_pitch +
                                 BIG_PITCH_AIM_KD * (pitch_rotation - last_pitch);
            }

//            cout << "yaw: "<<BIG_YAW_AIM_KP * yaw_rotation << '\t' << BIG_YAW_AIM_KI * sum_yaw << '\t'
//                 << BIG_YAW_AIM_KD * (yaw_rotation - last_yaw) << endl;
//            cout << "pitch: "<<BIG_PITCH_AIM_KP * pitch_rotation << '\t' << BIG_PITCH_AIM_KI * sum_pitch << '\t'
//                 << BIG_PITCH_AIM_KD * (pitch_rotation - last_pitch) << endl;
            last_yaw = tmp_yaw;
            last_pitch = tmp_pitch;
            if (ROBOT_ID == 7) {
                MINMAX(yaw_rotation, -6, 6);
                MINMAX(pitch_rotation, -6, 6);
            }
        } else if (is_chassis) {
//            sum_yaw += yaw_rotation - mcu_data.curr_yaw;
//            sum_pitch += pitch_rotation - mcu_data.curr_pitch;
//            double tmp_yaw = yaw_rotation;
//            double tmp_pitch = pitch_rotation;
//            yaw_rotation = BIG_YAW_AIM_KP * (yaw_rotation - mcu_data.curr_yaw) + BIG_YAW_AIM_KI * sum_yaw;
//            pitch_rotation = BIG_PITCH_AIM_KP * (pitch_rotation - mcu_data.curr_pitch) + BIG_PITCH_AIM_KI * sum_pitch;
//            last_yaw = tmp_yaw;
//            last_pitch = tmp_pitch;
        }
    } else if (is_small) {
        double tmp_yaw = yaw_rotation;
        double tmp_pitch = pitch_rotation;
        if (mcu_data.mark == 1) {
            yaw_rotation = TRY_SMALL_YAW_AIM_KP * yaw_rotation + TRY_SMALL_YAW_AIM_KD * (yaw_rotation - last_yaw);
            pitch_rotation =
                    TRY_SMALL_PITCH_AIM_KP * pitch_rotation + TRY_SMALL_PITCH_AIM_KD * (pitch_rotation - last_pitch);
        } else {
            yaw_rotation = SMALL_YAW_AIM_KP * yaw_rotation + SMALL_YAW_AIM_KD * (yaw_rotation - last_yaw);
            pitch_rotation = SMALL_PITCH_AIM_KP * pitch_rotation + SMALL_PITCH_AIM_KD * (pitch_rotation - last_pitch);
        }
        if (ROBOT_ID == 7) {
            MINMAX(yaw_rotation, -6, 6);
            MINMAX(pitch_rotation, -6, 6);
        }
        last_yaw = tmp_yaw;
        last_pitch = tmp_pitch;
    }


    if (change_target) {
        sendTarget(serial, yaw_rotation, pitch_rotation, 5, 0);
    } else if (is_guessing) {
        sendTarget(serial, yaw_rotation, pitch_rotation, 6, 0);
    } /*else if (fans_cnt >= 4) {
        sendTarget(serial, yaw_rotation, pitch_rotation, 7, 0);
    }*/ else {
        sendTarget(serial, yaw_rotation, pitch_rotation, shoot, 0);
    }

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于发送数据给主控板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::sendTarget(Serial &serial, float x, float y, float z) {
    short x_tmp, y_tmp, z_tmp;
    uint8_t buff[8];

#ifdef WITH_COUNT_FPS
    static auto last_time = time(nullptr);
    static int fps = 0;
    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "Energy: fps:" << fps << ", (" << x << "," << y << "," << z << ")" << endl;
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
    buff[7] = 'e';
    serial.WriteData(buff, sizeof(buff));
    send_cnt += 1;
//    LOGM(STR_CTR(WORD_LIGHT_PURPLE, "send"));
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于发送数据给主控板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::sendTarget(Serial &serial, float x, float y, float z, uint16_t u) {
    short x_tmp, y_tmp, z_tmp;
    uint8_t buff[10];

#ifdef WITH_COUNT_FPS
    static auto last_time = time(nullptr);
    static int fps = 0;
    time_t t = time(nullptr);
    if (last_time != t) {
        last_time = t;
        cout << "Energy: fps:" << fps << ", (" << x << "," << y << "," << z << "," << u << ")" << endl;
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
    buff[8] = static_cast<char>((u >> 0) & 0xFF);
    buff[9] = 'e';
    serial.WriteData(buff, sizeof(buff));
    send_cnt += 1;
//    LOGM(STR_CTR(WORD_LIGHT_PURPLE, "send"));
}
