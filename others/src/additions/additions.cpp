//
// Created by sjturm on 19-5-17.
//

#include <cstring>
#include <fstream>
#include <additions/additions.h>
#include <log.h>
#include <opencv2/videoio/videoio_c.h>

#define RECEIVE_LOG_LEVEL LOG_NOTHING

void uartReceive(Serial* pSerial) {
    char buffer[100];
    int cnt = 0;
    LOGM("data receive start!");
    while (true) {
        char byte;
        while (pSerial->ReadData((uint8_t*)&byte, 1) && byte!='\n') {
            buffer[cnt++] = byte;
            if (cnt >= 100) {
                LOG(RECEIVE_LOG_LEVEL, "data receive over flow!");
                cnt = 0;
            }
        }
        if (cnt == sizeof(mcuData)) {
            memcpy(&mcuData, buffer, sizeof(mcuData));
        }
        cnt = 0;
    }
}

void initVideoWriter(cv::VideoWriter& video, const std::string &filename_prefix){
    std::ifstream in(filename_prefix + "cnt.txt");
    int cnt = 0;
    if (in.is_open())
    {
        in >> cnt;
        in.close();
    }
    std::string armor_file_name = filename_prefix + std::to_string(cnt) + ".avi";
    cnt++;
    std::ofstream out(filename_prefix + "cnt.txt");
    if (out.is_open()) {
        out << cnt << std::endl;
        out.close();
    }
    video.open(armor_file_name, CV_FOURCC('P', 'I', 'M', '1'), 90, cv::Size(640, 480), true);
}

