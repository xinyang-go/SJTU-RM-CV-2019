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
#include "camera/camera_api.h"

class CameraWrapper: public WrapperHead {
private:
    unsigned char* rgb_buffer0;
    unsigned char* rgb_buffer1;
    int camera_cnts;
    int camera_status0, camera_status1;
    tSdkCameraDevInfo camera_enum_list[2];
    int h_camera0;
    int h_camera1;
    char camera_name0[32];
    char camera_name1[32];

    tSdkCameraCapbility tCapability0;
    tSdkCameraCapbility tCapability1;
    tSdkFrameHead frame_info0;
    tSdkFrameHead frame_info1;
    BYTE *pby_buffer0;
    BYTE *pby_buffer1;
    IplImage* iplImage0;
    IplImage* iplImage1;
    int channel0;
    int channel1;




    void swapCameraHandle();

public:
    CameraWrapper();
    ~CameraWrapper() final;

    bool init() final;
    bool read(cv::Mat& src0, cv::Mat& src1) final;
    bool readRaw(cv::Mat& src0, cv::Mat& src1);
    bool readProcessed(cv::Mat& src0, cv::Mat& src1);


};


#endif //VIDEO_TEST1_CAMERA_WRAPPER_H
