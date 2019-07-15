//
// Created by sjturm on 19-5-17.
//

#include <cstring>
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <additions/additions.h>
#include <camera/camera_wrapper.h>
#include <energy/energy.h>
#include <armor_finder/armor_finder.h>
#include <log.h>

#define RECEIVE_LOG_LEVEL LOG_MSG

using namespace std;
using namespace cv;

extern WrapperHead *video_gimbal;
extern WrapperHead *video_chassis;

extern Serial serial;
extern uint8_t last_state;

extern ArmorFinder armorFinder;
extern Energy energy;

void uartReceive(Serial *pSerial) {
    char buffer[20];
    int cnt = 0;
    LOGM(STR_CTR(WORD_LIGHT_WHITE, "data receive start!"));
    while (true) {
        char byte = 0;
        memset(buffer, 0, sizeof(buffer));
        while (pSerial->ReadData((uint8_t *) &byte, 1) && byte != '\n') {
            buffer[cnt++] = byte;
            if (cnt >= sizeof(buffer)) {
//                LOGE("data receive over flow!");
                cnt = 0;
            }
        }
        if (cnt == 0 && byte == '\n') {
//            LOGM("%d", cnt);
        }
        if (cnt == sizeof(mcuData)) {
            memcpy(&mcuData, buffer, sizeof(mcuData));
//            LOGM("Get, state:%c, mark:%d!", mcuData.state, (int) mcuData.mark);
        }
        cnt = 0;
    }
}

cv::VideoWriter initVideoWriter(const std::string &filename_prefix) {
    cv::VideoWriter video;
    std::ifstream in(filename_prefix + "cnt.txt");
    int cnt = 0;
    if (in.is_open()) {
        in >> cnt;
        in.close();
    }
    std::string file_name = filename_prefix + std::to_string(cnt) + ".avi";
    cnt++;
    std::ofstream out(filename_prefix + "cnt.txt");
    if (out.is_open()) {
        out << cnt << std::endl;
        out.close();
    }
    video.open(file_name, CV_FOURCC('P', 'I', 'M', '1'), 90, cv::Size(640, 480), true);
    return video;
}

bool checkReconnect(bool is_camera_0_connect, bool is_camera_1_connect) {
    if (!is_camera_0_connect) {
        delete video_gimbal;
        video_gimbal = new CameraWrapper(0, "armor");
        is_camera_0_connect = video_gimbal->init();
    }
    if (!is_camera_1_connect) {
        delete video_chassis;
        video_chassis = new CameraWrapper(1, "energy");
        is_camera_1_connect = video_chassis->init();
    }
    return is_camera_0_connect && is_camera_1_connect;
}

bool checkReconnect(bool is_camera_connect) {
    if (!is_camera_connect) {
        delete video_gimbal;
        video_gimbal = new CameraWrapper(0, "armor");
        is_camera_connect = video_gimbal->init();
    }
    return is_camera_connect;
}

auto gimbal_video_writer = initVideoWriter(PROJECT_DIR"/gimbal_video/");
auto chassis_video_writer = initVideoWriter(PROJECT_DIR"/chassis_video/");

void saveVideos(const cv::Mat &gimbal_src, const cv::Mat &chassis_src) {
    if (!gimbal_src.empty() && !chassis_src.empty()) {
        gimbal_video_writer.write(gimbal_src);
        Mat chassis_save = chassis_src.clone();
        cvtColor(chassis_save, chassis_save, COLOR_GRAY2BGR);
        chassis_video_writer.write(chassis_save);
    } else if (!gimbal_src.empty() && chassis_src.empty()) {
        gimbal_video_writer.write(gimbal_src);
    } else if (gimbal_src.empty() && !chassis_src.empty()) {
        if (show_origin)imshow("src", gimbal_src);
        Mat chassis_save = chassis_src.clone();
        cvtColor(chassis_save, chassis_save, COLOR_GRAY2BGR);
        chassis_video_writer.write(chassis_save);
    } else return;
}

void saveVideos(const cv::Mat &gimbal_src) {
    if (!gimbal_src.empty()) {
        gimbal_video_writer.write(gimbal_src);
    } else return;
}

void showOrigin(const cv::Mat &gimbal_src, const cv::Mat &chassis_src) {
    if (!gimbal_src.empty() && !chassis_src.empty()) {
        imshow("gimbal", gimbal_src);
        imshow("chassis", chassis_src);
    } else if (!gimbal_src.empty() && chassis_src.empty()) {
        imshow("gimbal", gimbal_src);
    } else if (gimbal_src.empty() && !chassis_src.empty()) {
        imshow("chassis", chassis_src);
    } else return;
    cv::waitKey(1);
}

void showOrigin(const cv::Mat &gimbal_src) {
    if (!gimbal_src.empty()) {
        imshow("gimbal", gimbal_src);
    } else return;
    cv::waitKey(1);
}

void extract(cv::Mat &gimbal_src, cv::Mat &chassis_src) {
    if (!gimbal_src.empty() && !chassis_src.empty()) {
        extract(gimbal_src);
        extract(chassis_src);
    } else if (!gimbal_src.empty() && chassis_src.empty()) {
        extract(gimbal_src);
    } else if (gimbal_src.empty() && !chassis_src.empty()) {
        extract(chassis_src);
    } else return;
}

void extract(cv::Mat &gimbal_src) {//图像预处理，将视频切成640×480的大小
    if (gimbal_src.empty()) return;
    float length = static_cast<float>(gimbal_src.cols);
    float width = static_cast<float>(gimbal_src.rows);
    if (length / width > 640.0 / 480.0) {
        length *= 480.0 / width;
        resize(gimbal_src, gimbal_src, cv::Size(length, 480));
        gimbal_src = gimbal_src(Rect((length - 640) / 2, 0, 640, 480));
    } else {
        width *= 640.0 / length;
        resize(gimbal_src, gimbal_src, cv::Size(640, width));
        gimbal_src = gimbal_src(Rect(0, (width - 480) / 2, 640, 480));
    }
}