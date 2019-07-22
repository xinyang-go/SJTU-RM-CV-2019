//
// Created by zhikun on 18-11-7.
//

#include <camera/camera_wrapper.h>
#include <log.h>
#include <options/options.h>
#include <config/setconfig.h>

using namespace std;

using std::cout;
using std::endl;
using namespace cv;

CameraWrapper::CameraWrapper(int camera_mode, const std::string &n) :
        name(n),
        mode(camera_mode),
        camera_cnts(2),
        camera_status(-1),
        iplImage(nullptr),
        rgb_buffer(nullptr),
        channel(3) {
}


bool CameraWrapper::init() {
    CameraSdkInit(1);
    int camera_enumerate_device_status = CameraEnumerateDevice(camera_enum_list, &camera_cnts);
    if (camera_enumerate_device_status != CAMERA_STATUS_SUCCESS) {
        LOGE("CameraEnumerateDevice fail with %d!", camera_enumerate_device_status);
    }
    if (camera_cnts == 0) {
        LOGE("No camera device detected!");
        return false;
    } else if (camera_cnts >= 1) {
        LOGM("%d camera device detected!", camera_cnts);
    }
    int i;
    for (i = 0; i < camera_cnts; i++) {
        camera_status = CameraInit(&camera_enum_list[i], -1, -1, &h_camera);
        if (camera_status != CAMERA_STATUS_SUCCESS) {
            CameraUnInit(h_camera);
            continue;
        }
        CameraGetFriendlyName(h_camera, camera_name);
        if (name == "NULL" || strcmp(name.data(), camera_name) == 0) {
            break;
        }
        CameraUnInit(h_camera);
    }
    if (i >= camera_cnts) {
        LOGE("No device name %s or device open error!!", name.data());
        return false;
    }

    auto status = CameraGetCapability(h_camera, &tCapability);
    if (status != CAMERA_STATUS_SUCCESS) {
        cout << "CameraGetCapability return error code " << status << endl;
        return false;
    }

    rgb_buffer = (unsigned char *) malloc(tCapability.sResolutionRange.iHeightMax *
                                          tCapability.sResolutionRange.iWidthMax * 3);
#ifdef Windows
    char filepath[200];
    sprintf(filepath, PROJECT_DIR"/others/%s.Config", name.data());
    if (CameraReadParameterFromFile(h_camera, filepath) != CAMERA_STATUS_SUCCESS) {
        LOGE("Load parameter %s from file fail!", filepath);
        return false;
    }
    if (CameraLoadParameter(h_camera, PARAMETER_TEAM_A) != CAMERA_STATUS_SUCCESS) {
        LOGE("CameraLoadParameter %s fail!", filepath);
        return false;
    }
    LOGM("successfully loaded %s!", filepath);
#elif defined(Linux)
    CameraSetAeState(h_camera, false);
    CameraSetExposureTime(h_camera, CAMERA_EXPOSURE * 1000);
#ifndef WITH_TIME_BASED_CAMERA_GAIN
    CameraSetAnalogGain(h_camera, ARMOR_CAMERA_GAIN);
#else
    #include <sys/time.h>
    timeval tv;
    int gain;
    gettimeofday(&tv, nullptr);
    float hour = tv.tv_sec / 3600.0;
    if (6 <= hour && hour < 10) {
        gain = 20;
    } else if (10 <= hour && hour < 16) {
        gain = 10;
    } else if (16 <= hour && hour < 17) {
        gain = 20;
    } else if (17 <= hour && hour < 18) {
        gain = 40;
    } else {
        gain = 50;
    }
#endif
    if (mode == 0) {
        CameraSetGain(h_camera, CAMERA_BLUE_GAIN, CAMERA_GREEN_GAIN, CAMERA_RED_GAIN);
        CameraSetLutMode(h_camera, LUTMODE_PRESET);
    }
#endif
    double t;
    CameraGetExposureTime(h_camera, &t);
    LOGM("Exposure time: %lfms", t / 1000.0);
    /*让SDK进入工作模式，开始接收来自相机发送的图像
    数据。如果当前相机是触发模式，则需要接收到
    触发帧以后才会更新图像。    */
    CameraPlay(h_camera);

    /*其他的相机参数设置
    例如 CameraSetExposureTime   CameraGetExposureTime  设置/读取曝光时间
         CameraSetImageResolution  CameraGetImageResolution 设置/读取分辨率
         CameraSetGamma、CameraSetContrast、CameraSetGain等设置图像伽马、对比度、RGB数字增益等等。
         CameraGetFriendlyName    CameraSetFriendlyName 获取/设置相机名称（该名称可写入相机硬件）
    */
    cout << tCapability.sIspCapacity.bMonoSensor << endl;
    if (tCapability.sIspCapacity.bMonoSensor) {
        channel = 1;
        CameraSetIspOutFormat(h_camera, CAMERA_MEDIA_TYPE_MONO8);
        LOGM("camera %s mono ", camera_name);
    } else {
        channel = 3;
        CameraSetIspOutFormat(h_camera, CAMERA_MEDIA_TYPE_BGR8);
        LOGM("camera %s color ", camera_name);
    }
    return true;
}

bool CameraWrapper::changeBrightness(int brightness) {
    CameraSetAnalogGain(h_camera, brightness);
}

bool CameraWrapper::read(cv::Mat &src) {
    if (mode == 0)return readProcessed(src);
    if (mode == 1)return readRaw(src);
}

bool CameraWrapper::readRaw(cv::Mat &src) {
    if (CameraGetImageBuffer(h_camera, &frame_info, &pby_buffer, 1000) == CAMERA_STATUS_SUCCESS) {
        if (iplImage) {
            cvReleaseImageHeader(&iplImage);
        }

        iplImage = cvCreateImageHeader(cvSize(frame_info.iWidth, frame_info.iHeight), IPL_DEPTH_8U, 1);

        cvSetData(iplImage, pby_buffer, frame_info.iWidth);  //此处只是设置指针，无图像块数据拷贝，不需担心转换效率

        src = cv::cvarrToMat(iplImage).clone();

        //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
        //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        CameraReleaseImageBuffer(h_camera, pby_buffer);

        return true;
    } else {
        src = cv::Mat();
        return false;
    }
}

bool CameraWrapper::readProcessed(cv::Mat &src) {
//	cerr << "Get-1" << endl;
    if (CameraGetImageBuffer(h_camera, &frame_info, &pby_buffer, 1000) == CAMERA_STATUS_SUCCESS) {
        CameraImageProcess(h_camera, pby_buffer, rgb_buffer,
                           &frame_info);  // this function is super slow, better not to use it.
        if (iplImage) {
            cvReleaseImageHeader(&iplImage);
        }
        iplImage = cvCreateImageHeader(cvSize(frame_info.iWidth, frame_info.iHeight), IPL_DEPTH_8U, channel);
        cvSetData(iplImage, rgb_buffer, frame_info.iWidth * channel);  //此处只是设置指针，无图像块数据拷贝，不需担心转换效率
        src = cv::cvarrToMat(iplImage).clone();
        //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
        //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        CameraReleaseImageBuffer(h_camera, pby_buffer);
        return true;
    } else {
        src = cv::Mat();
        return false;
    }
}

CameraWrapper::~CameraWrapper() {
    CameraUnInit(h_camera);
    //注意，先反初始化后再free
    if (rgb_buffer != nullptr)
        free(rgb_buffer);
}

