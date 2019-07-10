//
// Created by zhikun on 18-11-7.
// used for testing double cameras
// camera0 is left camera, camera1 is right camera.
//

#ifndef VIDEO_TEST1_CAMERA_WRAPPER_H
#define VIDEO_TEST1_CAMERA_WRAPPER_H

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include "camera/wrapper_head.h"
#ifdef Windows
    #include "camera/CameraApi.h"
#elif defined(Linux) || defined(Darwin)
    #include "camera/camera_api.h"
#endif

class CameraWrapper: public WrapperHead {
private:
    const std::string name;
    int mode;

    unsigned char* rgb_buffer;
    int camera_cnts;
    int camera_status;
    tSdkCameraDevInfo camera_enum_list[2];
    int h_camera;
    char camera_name[32];

    tSdkCameraCapbility tCapability;
    tSdkFrameHead frame_info;
    BYTE *pby_buffer;
    IplImage* iplImage;
    int channel;


public:
    CameraWrapper(int camera_mode=1, const std::string &n="NULL");
    ~CameraWrapper() final;

    bool init() final;
    bool read(cv::Mat& src) final;
    bool readRaw(cv::Mat& src);
    bool readProcessed(cv::Mat& src);
    bool changeBrightness(int brightness);
};


#endif //VIDEO_TEST1_CAMERA_WRAPPER_H
