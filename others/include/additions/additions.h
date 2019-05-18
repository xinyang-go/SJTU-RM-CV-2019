//
// Created by sjturm on 19-5-17.
//

#ifndef _ADDITIONS_H_
#define _ADDITIONS_H_

#include <stdint.h>
#include <serial/serial.h>
#include <opencv2/videoio.hpp>
#include <camera/wrapper_head.h>

#define ENEMY_BLUE 0
#define ENEMY_RED  1

struct mcu_data{
    float curr_yaw;
    float curr_pitch;
    uint8_t state;
    uint8_t mark;
    uint8_t use_classifier;
    uint8_t enemy_color;
};

extern mcu_data mcuData;

void uartReceive(Serial *pSerial);
void initVideoWriter(cv::VideoWriter& video, const std::string &armor_filename_prefix);

#endif /* _ADDITIONS_H_ */
