//
// Created by zhikun on 18-11-7.
//

#include <camera/camera_wrapper.h>

using std::cout;
using std::endl;
using namespace cv;

CameraWrapper::CameraWrapper()
{
    camera_cnts = 2;
    camera_status0 = -1;
    camera_status1 = -1;
    iplImage0 = nullptr;
    iplImage1 = nullptr;
    channel0 = 3;
    channel1 = 3;
}


bool CameraWrapper::init() {
    CameraSdkInit(1);

    //枚举设备，并建立设备列表
    int camera_enumerate_device_status =  CameraEnumerateDevice(camera_enum_list, &camera_cnts);
    //cout<<"camera enumerate device status: "<<camera_enumerate_device_status<<endl;
    //cout<<"camera number: "<<camera_cnts<<endl;

    //没有连接设备
    if (camera_cnts == 0) {
        cout<<"No device detected!"<<endl;
        return false;
    }
    else if(camera_cnts == 1)
    {
        cout<<"Only one camera device detected"<<endl;
        return false;
    }
    else if(camera_cnts == 2)
    {
        cout<<"Two camera devices detected."<<endl;
    }
    else
    {
        cout<<"More than 2 cameras detected or some other error occurs."<<endl;
        return false;
    }

    //相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
    camera_status0 = CameraInit(&camera_enum_list[0], -1, -1, &h_camera0);
    //初始化失败
    if (camera_status0 != CAMERA_STATUS_SUCCESS) {
        cout<<"Camera 0 initialization failed with code "<<camera_status0<<". See camera_status.h to find the code meaning."<<endl;
        return false;
    }

    camera_status1 = CameraInit(&camera_enum_list[1], -1, -1, &h_camera1);
    if (camera_status1 != CAMERA_STATUS_SUCCESS) {
        cout<<"Camera 1 initialization failed with code "<<camera_status1<<". See camera_status.h to find the code meaning."<<endl;
        return false;
    }

        CameraGetFriendlyName(h_camera0, camera_name0);
        CameraGetFriendlyName(h_camera1, camera_name1);
        cout<<"camera names: "<<camera_name0<<" "<<camera_name1<<endl;
//        cout<<camera_name0<<endl;
//        cout<<camera_name1<<endl;
    //如果读取的相机列表不是0在左，1在右，则交换相机句柄
//    if(strcmp(camera_name0, "camera0") != 0)
//    {
//        swapCameraHandle();
//    }

    //获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数
    CameraGetCapability(h_camera0, &tCapability0);
    CameraGetCapability(h_camera1, &tCapability1);

    // set resolution to 320*240
    // CameraSetImageResolution(hCamera, &(tCapability.pImageSizeDesc[2]));

    rgb_buffer0 = (unsigned char *)malloc(tCapability0.sResolutionRange.iHeightMax *
            tCapability0.sResolutionRange.iWidthMax * 3);
    rgb_buffer1 = (unsigned char *)malloc(tCapability1.sResolutionRange.iHeightMax *
            tCapability1.sResolutionRange.iWidthMax * 3);

    CameraSetAeState(h_camera0, true);  //设置是否自动曝光
    CameraSetAeState(h_camera1, true);

    /*让SDK进入工作模式，开始接收来自相机发送的图像
    数据。如果当前相机是触发模式，则需要接收到
    触发帧以后才会更新图像。    */
    CameraPlay(h_camera0);
    CameraPlay(h_camera1);

    /*其他的相机参数设置
    例如 CameraSetExposureTime   CameraGetExposureTime  设置/读取曝光时间
         CameraSetImageResolution  CameraGetImageResolution 设置/读取分辨率
         CameraSetGamma、CameraSetConrast、CameraSetGain等设置图像伽马、对比度、RGB数字增益等等。
         CameraGetFriendlyName    CameraSetFriendlyName 获取/设置相机名称（该名称可写入相机硬件）
    */
//    double exposure_time0, exposure_time1;
//    CameraGetExposureTime(h_camera0, &exposure_time0);
//    CameraGetExposureTime(h_camera1, &exposure_time1);
//    cout<<"exposure time "<<exposure_time0<<" "<<exposure_time1<<endl;

    // 抗频闪
    CameraSetAntiFlick(h_camera0, true);
    CameraSetAntiFlick(h_camera1, true);


    if (tCapability0.sIspCapacity.bMonoSensor) {
        channel0 = 1;
        CameraSetIspOutFormat(h_camera0, CAMERA_MEDIA_TYPE_MONO8);
        cout<<"camera0 mono "<<endl;
    } else {
        channel0 = 3;
        CameraSetIspOutFormat(h_camera0, CAMERA_MEDIA_TYPE_BGR8);
        cout<<"camera0 color mode"<<endl;
    }

    if (tCapability1.sIspCapacity.bMonoSensor) {
        channel1 = 1;
        CameraSetIspOutFormat(h_camera1, CAMERA_MEDIA_TYPE_MONO8);
        cout<<"camera1 mono "<<endl;
    } else {
        channel1 = 3;
        CameraSetIspOutFormat(h_camera1, CAMERA_MEDIA_TYPE_BGR8);
        cout<<"camera1 color mode"<<endl;
    }

    return true;
}


bool CameraWrapper::read(cv::Mat& src0, cv::Mat& src1) {
    return readRaw(src0, src1);             //suit for using bayer hacking in armor_finder to replace process, fast and it can filter red and blue.
    //return readProcessed(src0, src1);   // processed color image, but this runs slowly, about half fps of previous one.


}

bool CameraWrapper::readRaw(cv::Mat &src0, cv::Mat &src1) {



    if (CameraGetImageBuffer(h_camera0, &frame_info0, &pby_buffer0, 1000) == CAMERA_STATUS_SUCCESS &&
        CameraGetImageBuffer(h_camera1, &frame_info1, &pby_buffer1, 1000) == CAMERA_STATUS_SUCCESS)
    {
        if (iplImage0) {
            cvReleaseImageHeader(&iplImage0);
        }
        if (iplImage1){
            cvReleaseImageHeader(&iplImage1);
        }

        iplImage0 = cvCreateImageHeader(cvSize(frame_info0.iWidth, frame_info0.iHeight), IPL_DEPTH_8U, 1);
        iplImage1 = cvCreateImageHeader(cvSize(frame_info1.iWidth, frame_info1.iHeight), IPL_DEPTH_8U, 1);

        cvSetData(iplImage0, pby_buffer0, frame_info0.iWidth);  //此处只是设置指针，无图像块数据拷贝，不需担心转换效率
        cvSetData(iplImage1, pby_buffer1, frame_info1.iWidth);

        src0 = cv::cvarrToMat(iplImage0);
        src1 = cv::cvarrToMat(iplImage1);

        //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
        //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        CameraReleaseImageBuffer(h_camera0, pby_buffer0);
        CameraReleaseImageBuffer(h_camera1, pby_buffer1);

        return true;
    } else {
        return false;
    }
}

bool CameraWrapper::readProcessed(cv::Mat &src0, cv::Mat &src1) {
    if (CameraGetImageBuffer(h_camera0, &frame_info0, &pby_buffer0, 1000) == CAMERA_STATUS_SUCCESS &&
        CameraGetImageBuffer(h_camera1, &frame_info1, &pby_buffer1, 1000) == CAMERA_STATUS_SUCCESS)
    {

        CameraImageProcess(h_camera0, pby_buffer0, rgb_buffer0, &frame_info0);  // this function is super slow, better not to use it.
        CameraImageProcess(h_camera1, pby_buffer1, rgb_buffer1, &frame_info1);
        if (iplImage0) {
            cvReleaseImageHeader(&iplImage0);
        }
        if (iplImage1){
            cvReleaseImageHeader(&iplImage1);
        }

        iplImage0 = cvCreateImageHeader(cvSize(frame_info0.iWidth, frame_info0.iHeight), IPL_DEPTH_8U, channel0);
        iplImage1 = cvCreateImageHeader(cvSize(frame_info1.iWidth, frame_info1.iHeight), IPL_DEPTH_8U, channel1);

        cvSetData(iplImage0, rgb_buffer0, frame_info0.iWidth * channel0);  //此处只是设置指针，无图像块数据拷贝，不需担心转换效率
        cvSetData(iplImage1, rgb_buffer1, frame_info1.iWidth * channel1);

        src0 = cv::cvarrToMat(iplImage0);
        src1 = cv::cvarrToMat(iplImage1);

        //在成功调用CameraGetImageBuffer后，必须调用CameraReleaseImageBuffer来释放获得的buffer。
        //否则再次调用CameraGetImageBuffer时，程序将被挂起一直阻塞，直到其他线程中调用CameraReleaseImageBuffer来释放了buffer
        CameraReleaseImageBuffer(h_camera0, pby_buffer0);
        CameraReleaseImageBuffer(h_camera1, pby_buffer1);
        return true;
    } else {
        return false;
    }
}


CameraWrapper::~CameraWrapper()
{
    CameraUnInit(h_camera0);
    CameraUnInit(h_camera1);
    //注意，先反初始化后再free
    free(rgb_buffer0);
    free(rgb_buffer1);
}

void CameraWrapper::swapCameraHandle() {
    int tmp_h_camera = h_camera0;
    h_camera0 = h_camera1;
    h_camera1 = tmp_h_camera;
}





