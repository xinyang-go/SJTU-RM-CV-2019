//
// Created by zhikun on 18-11-7.
//

#ifndef _CAMERA_WRAPPER_H_
#define _CAMERA_WRAPPER_H_

#include <additions.h>
#include <opencv2/core/core.hpp>
#include <camera/wrapper_head.h>

#ifdef Windows
    #include "camera/CameraApi.h"
#elif defined(Linux) || defined(Darwin)
    #include <camera/camera_api.h>
#endif

class CameraWrapper: public WrapperHead {
    friend void cameraCallback(CameraHandle hCamera, BYTE *pFrameBuffer, tSdkFrameHead* pFrameHead,PVOID pContext);
private:
    const std::string name;
    int mode;

    bool init_done;

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

    RoundQueue<cv::Mat, 2> src_queue;
public:
    int gain;
    int exposure;

    CameraWrapper(int exposure, int gain, int camera_mode=1, const std::string &n="NULL");
    ~CameraWrapper() final;

    bool init() final;
    bool read(cv::Mat& src) final;
    bool readRaw(cv::Mat& src);
    bool readProcessed(cv::Mat& src);
    bool readCallback(cv::Mat& src);
};


#endif /* _CAMERA_WRAPPER_H_ */
