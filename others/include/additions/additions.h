//
// Created by sjturm on 19-5-17.
//

#ifndef _ADDITIONS_H_
#define _ADDITIONS_H_

#include <stdint.h>
#include <serial/serial.h>

struct mcu_data{
    float curr_yaw;
    float curr_pitch;
    uint8_t state;
    uint8_t mark;
    uint8_t use_classifier;
    uint8_t enemy_color;
    int delta_x;
    int delta_y;
};

extern mcu_data mcuData;

void uartReceive(Serial *pSerial);
bool checkReconnect(bool is_camera_0_connect, bool is_camera_1_connect);
bool checkReconnect(bool is_camera_connect);
void saveVideos(const cv::Mat &gimbal_src, const cv::Mat &chassis_src);
void saveVideos(const cv::Mat &gimbal_src);
void showOrigin(const cv::Mat &gimbal_src, const cv::Mat &chassis_src);
void showOrigin(const cv::Mat &gimbal_src);
void extract(cv::Mat &gimbal_src, cv::Mat &chassis_src);
void extract(cv::Mat &gimbal_src);

#endif /* _ADDITIONS_H_ */
