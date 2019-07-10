/**********************************************************************/
/*   ____      _ _____ _   _       ____  __  __        ______     __  */
/*  / ___|    | |_   _| | | |     |  _ \|  \/  |      / ___\ \   / /  */
/*  \___ \ _  | | | | | | | |_____| |_) | |\/| |_____| |    \ \ / /   */
/*   ___) | |_| | | | | |_| |_____|  _ <| |  | |_____| |___  \ V /    */
/*  |____/ \___/  |_|  \___/      |_| \_\_|  |_|      \____|  \_/     */
/*                                                                    */
/**********************************************************************/

#include <iostream>
#include <thread>
#include <opencv2/core/core.hpp>
#include <serial/serial.h>
#include <camera/camera_wrapper.h>
#include <camera/video_wrapper.h>
#include <camera/wrapper_head.h>
#include <energy/energy.h>
#include <armor_finder/armor_finder.h>
#include <options/options.h>
#include <additions/additions.h>
#define DO_NOT_CNT_TIME
#include <log.h>

using namespace cv;
using namespace std;

mcu_data mcuData = {    // 单片机端回传结构体
        0,              // 当前云台yaw角
        0,              // 当前云台pitch角
        ARMOR_STATE,    // 当前状态，自瞄-大符-小符
        0,              // 云台角度标记位
        1,              // 是否启用数字识别
        ENEMY_RED,      // 敌方颜色
};

WrapperHead *video_gimble = nullptr;    // 云台摄像头视频源
WrapperHead *video_chassis = nullptr;   // 底盘摄像头视频源

Serial serial(115200);                  // 串口对象
uint8_t last_state = mcuData.state;     // 上次状态，用于初始化
// 自瞄主程序对象
ArmorFinder armorFinder(mcuData.enemy_color, serial, PROJECT_DIR"/tools/para/", mcuData.use_classifier);
// 能量机关主程序对象
Energy energy(serial, mcuData.enemy_color);

int box_distance = 0;

int main(int argc, char *argv[]) {
    process_options(argc, argv);            // 处理命令行参数
    thread receive(uartReceive, &serial);   // 开启串口接收线程

    int from_camera = 1;                    // 根据条件选择视频源
    if (!run_with_camera) {
        cout << "Input 1 for camera, 0 for video files" << endl;
        cin >> from_camera;
    }

    while (true) {
        // 打开视频源
        if (from_camera) {
            video_gimble = new CameraWrapper(0/*, "armor"*/);
            video_chassis = new CameraWrapper(1/*, "energy"*/);
        } else {
            video_gimble = new VideoWrapper("/home/sun/项目/energy_video/energy_test.avi");
            video_chassis = new VideoWrapper("/home/sun/项目/energy_video/energy_test.avi");
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

        // 跳过前10帧噪声图像。
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
        cout << "start running" << endl;
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
                } else if (mcuData.state != BIG_ENERGY_STATE) {//自瞄或小符模式
                    last_state = mcuData.state;
                    ok = checkReconnect(video_gimble->read(gimble_src));
                    if (save_video) saveVideos(gimble_src);
                    if (show_origin) showOrigin(gimble_src);
                    if (mcuData.state == ARMOR_STATE) {
                        CNT_TIME("Armor Time", {
                            armorFinder.run(gimble_src);
                        });
                    } else if (mcuData.state == SMALL_ENERGY_STATE) {
//                        energy.runSmall(gimble_src);
                        energy.runBig(gimble_src);
                    }
                }
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

