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
#include <additions.h>
#include <camera/camera_wrapper.h>
#include <energy/energy.h>
#include <armor_finder/armor_finder.h>
#include <log.h>

#define RECEIVE_LOG_LEVEL LOG_MSG

using namespace std;
using namespace cv;

extern WrapperHead *video;

extern Serial serial;
extern uint8_t last_state;

extern ArmorFinder armor_finder;
extern Energy energy;

void uartReceive(Serial *pSerial) {
    char buffer[40];
    LOGM(STR_CTR(WORD_LIGHT_WHITE, "data receive start!"));
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        pSerial->ReadData((uint8_t *) buffer, sizeof(mcu_data)+1);
        if (buffer[sizeof(mcu_data)] == '\n') {
            memcpy(&mcu_data, buffer, sizeof(mcu_data));
//            LOGM("Get, state:%c, mark:%d!", mcu_data.state, (int) mcu_data.mark);
//            LOGM("Get yaw: %f, pitch: %f!", mcu_data.curr_yaw, mcu_data.curr_pitch);
//            LOGM("Get delta x: %d, delta y: %d!", mcu_data.delta_x, mcu_data.delta_y);
//            static int t = time(nullptr);
//            static int cnt = 0;
//            if(time(nullptr) > t){
//                t = time(nullptr);
//                LOGM("fps:%d", cnt);
//                cnt = 0;
//            }else{
//                cnt++;
//            }
        }else{
//            LOGW("corrupt data!");
        }
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

bool checkReconnect(bool is_camera_connect) {
    if (!is_camera_connect) {
        int curr_gain = ((CameraWrapper* )video)->gain;
        int curr_exposure = ((CameraWrapper* )video)->exposure;
        delete video;
        video = new CameraWrapper(curr_exposure, curr_gain, 0/*, "armor"*/);
        is_camera_connect = video->init();
    }
    return is_camera_connect;
}

auto video_writer = initVideoWriter(PROJECT_DIR"/video/");

void saveVideos(const cv::Mat &gimbal_src) {
    if (!gimbal_src.empty()) {
        video_writer.write(gimbal_src);
    } else return;
}

void showOrigin(const cv::Mat &src) {
    if (!src.empty()) {
        imshow("origin", src);
        cv::waitKey(1);
    } else return;
}

void extract(cv::Mat &src) {//图像预处理，将视频切成640×480的大小
    if (src.empty()) return;
    float length = static_cast<float>(src.cols);
    float width = static_cast<float>(src.rows);
    if (length / width > 640.0 / 480.0) {
        length *= 480.0 / width;
        resize(src, src, cv::Size(length, 480));
        src = src(Rect((length - 640) / 2, 0, 640, 480));
    } else {
        width *= 640.0 / length;
        resize(src, src, cv::Size(640, width));
        src = src(Rect(0, (width - 480) / 2, 640, 480));
    }
}

double getPointLength(const cv::Point2f &p) {
    return sqrt(p.x * p.x + p.y * p.y);
}
