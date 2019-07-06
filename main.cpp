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

#define ENERGY_STATE 'e'
#define ARMOR_STATE  'a'

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

int main(int argc, char *argv[]) {
    process_options(argc, argv);
    Serial serial(115200);
	uint8_t last_state = mcuData.state;
    thread receive(uartReceive, &serial);

    int from_camera = 1;
    if (!run_with_camera) {
        cout << "Input 1 for camera, 0 for video files" << endl;
        cin >> from_camera;
    }

    while (true) {
        VideoWriter armor_video_writer, energy_video_writer;
        if (save_video) {
            initVideoWriter(armor_video_writer, PROJECT_DIR"/armor_video/");
            initVideoWriter(energy_video_writer, PROJECT_DIR"/energy_video/");
        }

        WrapperHead *video_armor=nullptr;
        WrapperHead *video_energy=nullptr;
        if (from_camera) {
            video_armor = new CameraWrapper(0/*, "armor"*/);
            video_energy = new CameraWrapper(1, "energy");
        } else {
            video_armor = new VideoWrapper("/home/sjturm/Desktop/valid_video/armor/65.avi");
            video_energy = new VideoWrapper("/home/sjturm/Desktop/valid_video/energy/121.avi");
        }
        if (video_armor->init()) {
            LOGM("video_armor source initialization successfully.");
        } else {
            LOGW("video_armor source unavailable!");
            delete video_armor;
            video_armor = nullptr;
        }
        if (video_energy->init()) {
            LOGM("video_energy source initialization successfully.");
        } else {
            LOGW("video_energy source unavailable!");
            delete video_energy;
            video_energy = nullptr;
        }

        Mat energy_src, armor_src;
        for (int i = 0; i < 10; i++) {
            if (video_armor) {
                video_armor->read(armor_src);
            }
            if (video_energy) {
                video_energy->read(energy_src);
            }
        }

        ArmorFinder armorFinder(mcuData.enemy_color, serial, PROJECT_DIR"/tools/para/", mcuData.use_classifier);

        Energy energy(serial, mcuData.enemy_color);
//        energy.setAllyColor(ally_color);
        energy.setRotation(CLOCKWISE);

        bool ok = true;
        cout<<"start running"<<endl;
        do {
            CNT_TIME("Total", {
                if (mcuData.state == ENERGY_STATE) {
					if (last_state == ARMOR_STATE) {
						energy.setEnergyRotationInit();
						cout << "set" << endl;
					}
					last_state = mcuData.state;
                    if (video_energy) {
                        ok = video_energy->read(energy_src);
                        if (!ok) {
                            delete video_energy;
                            video_energy = nullptr;
                        }
                        if(save_video){
                            Mat energy_save = energy_src.clone();
                            cvtColor(energy_save,energy_save,COLOR_GRAY2BGR);
                            energy_video_writer.write(energy_save);
//                            cout<<energy_src.type()<<endl;
//                            LOGM(STR_CTR(WORD_GREEN,"Save ENERGY!"));
                        }
                        if (show_origin) {
                            imshow("energy src", energy_src);
                        }
//                        if (from_camera == 0) {
//							cv::resize(energy_src, energy_src, cv::Size(640, 480), 2);
//							imshow("resize", energy_src);
//                            energy.extract(energy_src);
//                        }
                        energy.run(energy_src);
//                        waitKey(1);
                    } else {
                        video_energy = new CameraWrapper(1, "energy");
                        if(!video_energy->init()){
                            delete video_energy;
                            video_energy = nullptr;
                        }
                    }

                } else if (mcuData.state == ARMOR_STATE) {
					last_state = mcuData.state;
                    if (video_armor) {
                        ok = video_armor->read(armor_src);
                        if (!ok) {
                            delete video_armor;
                            video_armor = nullptr;
                        }
                        if(save_video){
                            armor_video_writer.write(armor_src);
//                            cout<<armor_src.type()<<endl;
//                            LOGM(STR_CTR(WORD_GREEN,"Save ARMOR!"));
                        }
//                        flip(armor_src, armor_src, 0);
                        if (show_origin) {
                            imshow("armor src", armor_src);
                        }
                        CNT_TIME("Armor Time", {
                            armorFinder.run(armor_src);
                        });
                    } else {
                        video_armor = new CameraWrapper(0, "armor");
                        if(!video_armor->init()){
                            delete video_armor;
                            video_armor = nullptr;
                        }
                    }
                }
//                cout<<last_state<<endl;
                waitKey(1);
            });
        } while (ok);

        delete video_armor;
        delete video_energy;
        cout << "Program fails. Restarting" << endl;
    }
    return 0;
}

