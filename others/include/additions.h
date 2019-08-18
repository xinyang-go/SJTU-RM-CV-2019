//
// Created by sjturm on 19-5-17.
//

#ifndef _ADDITIONS_H_
#define _ADDITIONS_H_

#include <stdint.h>
#include <systime.h>
#include <serial.h>
#include <opencv2/core.hpp>
// 单片机端回传数据结构体
struct McuData {
    float curr_yaw;      // 当前云台yaw角度
    float curr_pitch;    // 当前云台pitch角
    uint8_t state;       // 当前状态，自瞄-大符-小符
    uint8_t mark;        // 云台角度标记位
    uint8_t anti_top;    // 是否为反陀螺模式
    uint8_t enemy_color; // 敌方颜色
    int delta_x;         // 能量机关x轴补偿量
    int delta_y;         // 能量机关y轴补偿量
};

extern McuData mcu_data;
// 串口接收函数
void uartReceive(Serial *pSerial);
// 相机断线重连函数
bool checkReconnect(bool is_camera_connect);
// 视频保存函数
void saveVideos(const cv::Mat &src);
//　原始图像显示函数
void showOrigin(const cv::Mat &src);
// 图像裁剪函数
void extract(cv::Mat &src);

double getPointLength(const cv::Point2f &p);

// 循环队列
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
