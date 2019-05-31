//
// Created by sjturm on 19-5-17.
//

#include <cstring>
#include <fstream>
#include <additions/additions.h>
#include <log.h>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>

#define RECEIVE_LOG_LEVEL LOG_MSG

using namespace std;

void uartReceive(Serial* pSerial) {
    char buffer[20];
    int cnt = 0;
    LOGM(STR_CTR(WORD_LIGHT_WHITE,"data receive start!"));
    while (true) {
        char byte = 0;
        memset(buffer, 0, sizeof(buffer));
        while (pSerial->ReadData((uint8_t*)&byte, 1) && byte!='\n') {
            buffer[cnt++] = byte;
            if (cnt >= sizeof(buffer)) {
//                LOGE("data receive over flow!");
                cnt = 0;
            }
        }
        if (cnt==0 && byte=='\n'){
            LOGM("%d", cnt);
        }
        if (cnt == sizeof(mcuData)) {
            memcpy(&mcuData, buffer, sizeof(mcuData));
            LOGM("Get, state:%c, mark:%d!", mcuData.state, (int)mcuData.mark);
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
    std::string file_name = filename_prefix + std::to_string(cnt) + ".avi";
    cnt++;
    std::ofstream out(filename_prefix + "cnt.txt");
    if (out.is_open()) {
        out << cnt << std::endl;
        out.close();
    }
    video.open(file_name, CV_FOURCC('P', 'I', 'M', '1'), 90, cv::Size(640, 480), true);
}

void lastVideo(std::string &video_name, const std::string &filename_prefix){
    std::ifstream in(filename_prefix + "cnt.txt");
    int cnt = 0;
    if (in.is_open())
    {
        in >> cnt;
        in.close();
    }
    if(cnt > 1) std::string video_name = filename_prefix + std::to_string(cnt) + ".avi";
}

