//
// Created by sjturm on 19-5-17.
//

#ifndef _ADDITIONS_H_
#define _ADDITIONS_H_

#include <stdint.h>
#include <systime.h>
#include <serial.h>
#include <opencv2/core.hpp>

struct McuData {
    float curr_yaw;
    float curr_pitch;
    uint8_t state;
    uint8_t mark;
    uint8_t use_classifier;
    uint8_t enemy_color;
    int delta_x;
    int delta_y;
};

extern McuData mcu_data;

void uartReceive(Serial *pSerial);

bool checkReconnect(bool is_camera_0_connect, bool is_camera_1_connect);

bool checkReconnect(bool is_camera_connect);

void saveVideos(const cv::Mat &gimbal_src, const cv::Mat &chassis_src);

void saveVideos(const cv::Mat &gimbal_src);

void showOrigin(const cv::Mat &gimbal_src, const cv::Mat &chassis_src);

void showOrigin(const cv::Mat &gimbal_src);

void extract(cv::Mat &gimbal_src, cv::Mat &chassis_src);

void extract(cv::Mat &gimbal_src);

float getTimeIntervalms(const systime &now, const systime &last);

double getPointLength(const cv::Point2f &p);

template<class type, int length>
class RoundQueue {
private:
    type data[length];
    int head;
    int tail;
public:
    RoundQueue<type, length>() : head(0), tail(0) {};

    constexpr int size() const {
        return length;
    };

    bool empty() const {
        return head == tail;
    };

    void push(const type &obj) {
        data[head] = obj;
        head = (head + 1) % length;
        if (head == tail) {
            tail = (tail + 1) % length;
        }
    };

    bool pop(type &obj) {
        if (empty()) return false;
        obj = data[tail];
        tail = (tail + 1) % length;
        return true;
    };

    type &operator[](int idx) {
        while (tail + idx < 0) idx += length;
        return data[(tail + idx) % length];
    };
};

#endif /* _ADDITIONS_H_ */
