//
// Created by zhikun on 18-11-7.
//

#include <camera/camera_wrapper.h>
#include <log.h>

using std::cout;
using std::endl;
using namespace cv;

CameraWrapper::CameraWrapper(int camera_mode, const std::string &n):
        name(n),
        mode(camera_mode),
        camera_cnts(2),
        camera_status(-1),
        iplImage(nullptr),
        rgb_buffer(nullptr),
        channel(3){
}


bool CameraWrapper::init() {
    CameraSdkInit(1);

    //枚举设备，并建立设备列表
    int camera_enumerate_device_status =  CameraEnumerateDevice(camera_enum_list, &camera_cnts);
    if(camera_enumerate_device_status != CAMERA_STATUS_SUCCESS){
        LOGE("CameraEnumerateDevice fail with %d!", camera_enumerate_device_status);
    }
    //没有连接设备
    if (camera_cnts == 0) {
        LOGE("No camera device detected!");
        return false;
    }else if(camera_cnts >= 1){
        LOGM("%d camera device detected!", camera_cnts);
    }
    //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    int i;
    for(i=0; i<camera_cnts; i++){
        camera_status = CameraInit(&camera_enum_list[i], -1, -1, &h_camera);
        if (camera_status != CAMERA_STATUS_SUCCESS) {
            LOGE("Camera 0 initialization failed with code %d. See camera_status.h to find the code meaning.", camera_status);
            goto stop;
        }
        CameraGetFriendlyName(h_camera, camera_name);
        if(name=="NULL" || strcmp(name.data(), camera_name)==0){
            break;
        }
stop:
        CameraUnInit(h_camera);
    }
    if(i >= camera_cnts){
        LOGE("No device name %s or device open error!!", name.data());
        return false;
    }

    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    CameraGetCapability(h_camera, &tCapability);

    // set resolution to 320*240
    // CameraSetImageResolution(hCamera, &(tCapability.pImageSizeDesc[2]));

    rgb_buffer = (unsigned char *)malloc(tCapability.sResolutionRange.iHeightMax *
            tCapability.sResolutionRange.iWidthMax * 3);
    if(mode == 0){
        // 不使用自动曝光
        CameraSetAeState(h_camera, false);
        // 曝光时间10ms
        CameraSetExposureTime(h_camera, 10000);
        double t;
        CameraGetExposureTime(h_camera, &t);
        LOGM("Exposure time: %lfms", t/1000.0);
        // 模拟增益4
        CameraSetAnalogGain(h_camera, 55);
        // 使用预设LUT表
        CameraSetLutMode(h_camera, LUTMODE_PRESET);
        // 抗频闪
//        CameraSetAntiFlick(h_camera, true);
    }
    else if(mode == 1){
        // 不使用自动曝光
        CameraSetAeState(h_camera, false);
        // 抗频闪
//        CameraSetAntiFlick(h_camera, true);
    }

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


bool CameraWrapper::read(cv::Mat& src) {
//    return readRaw(src);             //suit for using bayer hacking in armor_finder to replace process, fast and it can filter red and blue.
    if(mode==0)return readProcessed(src);   // processed color image, but this runs slowly, about half fps of previous one.
    if(mode==1)return readRaw(src);


}

bool CameraWrapper::readRaw(cv::Mat &src) {
    if (CameraGetImageBuffer(h_camera, &frame_info, &pby_buffer, 1000) == CAMERA_STATUS_SUCCESS){
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
        return false;
    }
}

bool CameraWrapper::readProcessed(cv::Mat &src) {
    if (CameraGetImageBuffer(h_camera, &frame_info, &pby_buffer, 1000) == CAMERA_STATUS_SUCCESS){
        CameraImageProcess(h_camera, pby_buffer, rgb_buffer, &frame_info);  // this function is super slow, better not to use it.
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
        return false;
    }
}

CameraWrapper::~CameraWrapper()
{
    CameraUnInit(h_camera);
    //注意，先反初始化后再free
    if(rgb_buffer != nullptr)
        free(rgb_buffer);
}

