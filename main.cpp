//
// Created by xixiliadorabarry on 1/24/19.
//
#include <iostream>
#include <opencv2/core/core.hpp>
#include <fstream>
#include <energy/energy.h>
#include <serial/serial.h>
#include <energy/param_struct_define.h>
#include <energy/constant.h>
#include <camera/camera_wrapper.h>
#include <camera/video_wrapper.h>
#include <camera/wrapper_head.h>
#include <armor_finder/armor_finder.h>
#include <options/options.h>
#include <additions/additions.h>
#include <thread>

#define DO_NOT_CNT_TIME

#include <log.h>

using namespace cv;
using namespace std;

mcu_data mcuData = {
        0,
        0,
        ARMOR_STATE,
        0,
        1,
        ENEMY_BLUE,
};

WrapperHead *video_gimble = nullptr;
WrapperHead *video_chassis = nullptr;

Serial serial(115200);
uint8_t last_state = mcuData.state;

ArmorFinder armorFinder(mcuData.enemy_color, serial, PROJECT_DIR"/tools/para/", mcuData.use_classifier);
Energy energy(serial, mcuData.enemy_color);

int main(int argc, char *argv[]) {
    process_options(argc, argv);
    thread receive(uartReceive, &serial);

    int from_camera = 1;
    if (!run_with_camera) {
        cout << "Input 1 for camera, 0 for video files" << endl;
        cin >> from_camera;
    }

    while (true) {
        if (from_camera) {
            video_gimble = new CameraWrapper(0/*, "armor"*/);
            video_chassis = new CameraWrapper(1/*, "energy"*/);
        } else {
            video_gimble = new VideoWrapper("/Users/leo/Desktop/videos/179.avi");
            video_chassis = new VideoWrapper("/Users/leo/Desktop/videos/179.avi");
        }
        if (video_gimble->init()) {
            LOGM("video_gimble source initialization successfully.");
        } else {
            LOGW("video_gimble source unavailable!");
            delete video_gimble;
            video_gimble = nullptr;
        }
        if (video_chassis->init()) {
            LOGM("video_chassis source initialization successfully.");
        } else {
            LOGW("video_chassis source unavailable!");
            delete video_chassis;
            video_chassis = nullptr;
        }

        Mat gimble_src, chassis_src;
        for (int i = 0; i < 10; i++) {
            if (video_gimble) {
                video_gimble->read(gimble_src);
            }
            if (video_chassis) {
                video_chassis->read(chassis_src);
            }
        }
        bool ok = true;
        cout<<"start running"<<endl;
        do {
            CNT_TIME("Total", {
                if (mcuData.state == BIG_ENERGY_STATE) {//大符模式
                    ok = checkReconnect(video_gimble->read(gimble_src), video_chassis->read(chassis_src));//检查有几个摄像头
                    if (save_video) saveVideos(gimble_src, chassis_src);//保存视频
                    if (show_origin) showOrigin(gimble_src, chassis_src);//显示原始图像
//                    if (from_camera == 0) {
//                        cv::resize(chassis_src, chassis_src, cv::Size(640, 480), 2);
//                        imshow("resize", chassis_src);
//                        energy.extract(chassis_src);
//                    }
                    if (last_state != BIG_ENERGY_STATE) {//若上一帧不是大符模式，即刚往完成切换，则需要初始化
                        energy.setEnergyRotationInit();
                        cout << "set" << endl;
                    }
                    energy.runBig(gimble_src, chassis_src);//击打大符
                    last_state = mcuData.state;//更新上一帧状态
                }
                else if (mcuData.state != BIG_ENERGY_STATE) {//自瞄或小符模式
                    last_state = mcuData.state;
                    ok = checkReconnect(video_gimble->read(gimble_src));
                    if (save_video) saveVideos(gimble_src);
                    if (show_origin) showOrigin(gimble_src);
                    if (mcuData.state == ARMOR_STATE){
                        CNT_TIME("Armor Time", {
                            armorFinder.run(gimble_src);
                        });
                    }
                    else if(mcuData.state == SMALL_ENERGY_STATE){
                        energy.runSmall(gimble_src);
                    }
                }
                cv::waitKey(1);
            });
        } while (ok);

        delete video_gimble;
        video_gimble = nullptr;
        delete video_chassis;
        video_chassis = nullptr;
        cout << "Program fails. Restarting" << endl;
    }
    return 0;
}

