//
// Created by xixiliadorabarry on 1/24/19.
//
#include <iostream>
#include <opencv2/core/core.hpp>

#include <energy/energy.h>
#include <serial/serial.h>
#include <energy/param_struct_define.h>
#include <energy/constant.h>
#include <camera/camera_wrapper.h>
#include <camera/video_wrapper.h>
#include <camera/wrapper_head.h>
#include <armor_finder/armor_finder.h>
#include <options/options.h>
#include <thread>

#define DO_NOT_CNT_TIME
#include <log.h>

#define ENERGY_STATE 1
#define ARMOR_STATE  0

using namespace cv;
using namespace std;


int state = ENERGY_STATE;
float curr_yaw = 0, curr_pitch = 0;
float mark_yaw = 0, mark_pitch = 0;
int mark = 0;
EnemyColor enemy_color = ENEMY_BLUE;
int ally_color = ALLY_RED;
bool use_classifier = true;

void uartReceive(Serial *uart);

int main(int argc, char *argv[]) {
    process_options(argc, argv);
	Serial uart(3, 115200);
    thread receive(uartReceive, &uart);
    bool flag = true;

    while (flag) {
        
        int energy_part_rotation = CLOCKWISE;

        int from_camera = 1;
        if (!run_with_camera) {
            cout << "Input 1 for camera, 0 for video files" << endl;
            cin >> from_camera;
        }

        WrapperHead *video_armor;
        WrapperHead *video_energy;
        if (from_camera) {
            video_armor = new CameraWrapper(0, "armor");
            video_energy = new CameraWrapper(1, "energy");
        } else {
            video_armor = new VideoWrapper("/home/xinyang/Desktop/DataSets/video/blue_4.mp4");
            video_energy = new VideoWrapper("/home/xinyang/Desktop/DataSets/video/blue_4.mp4");
        }
        if (video_armor->init() && video_energy->init()) {
            cout << "Video source initialization successfully." << endl;
        } else {
            delete video_armor;
            delete video_energy;
            cout << "Program fails. Restarting" << endl;
            continue;
        }

        Mat energy_src, armor_src;
        for(int i=0; i<10; i++){
            video_armor->read(armor_src);
            video_energy->read(armor_src);
        }

        ArmorFinder armorFinder(enemy_color, uart, PROJECT_DIR"/tools/para/", use_classifier);

        Energy energy(uart, ally_color);
//        energy.setAllyColor(ally_color);
        energy.setRotation(energy_part_rotation);

		bool ok = video_armor->read(armor_src) && video_energy->read(armor_src);

        while (ok) {
            CNT_TIME("Total", {
                if (state == ENERGY_STATE) {
                    ok = video_energy->read(energy_src);
                    if (show_origin) {
                        imshow("energy src", energy_src);
                    }
                    if (from_camera == 0) {
                        energy.extract(energy_src);
                    }
                    energy.run(energy_src);
                } else {
                    ok = video_armor->read(armor_src);
					flip(armor_src, armor_src, 0);
                    if (show_origin) {
                        imshow("armor src", armor_src);
                    }
                    CNT_TIME("Armor Time", {
                        armorFinder.run(armor_src);
                    });
                }
                if (waitKey(1) == 'q') {
                    flag = false;
                    break;
                }
            });
        }
        delete video_armor;
        delete video_energy;
        cout << "Program fails. Restarting" << endl;
    }

    return 0;
}

#define RECEIVE_LOG_LEVEL LOG_NOTHING

char uartReadByte(Serial &uart) {
	while (uart.GetBytesInCOM() == 0);
	char byte;
	if (uart.ReadData((uint8_t*)& byte, 1) == false) {
		LOGE("serial error!");
	}
	return byte;
}

void uartReceive(Serial* uart) {
    char buffer[100];
    int cnt = 0;
    LOGM("data receive start!");
    while (true) {
        char data;
        while ((data = uartReadByte(*uart)) != '\n') {
            buffer[cnt++] = data;
            if (cnt >= 100) {
                LOG(RECEIVE_LOG_LEVEL, "data receive over flow!");
                cnt = 0;
            }
        }
        LOGM("%d", cnt);
        if (cnt == 12) {
            if (buffer[8] == 'e') {
                state = ENERGY_STATE;
                LOG(RECEIVE_LOG_LEVEL, "Energy state");
            } else if (buffer[8] == 'a') {
                state = ARMOR_STATE;
                LOG(RECEIVE_LOG_LEVEL, "Armor state");
            }
            if (buffer[10] == 0){
                use_classifier = false;
                LOG(RECEIVE_LOG_LEVEL, "Classifier off!");
            } else if(buffer[10] == 1){
                use_classifier = true;
                LOG(RECEIVE_LOG_LEVEL, "Classifier on!");
            }
			if (buffer[11] == ENEMY_BLUE) {
				LOG(RECEIVE_LOG_LEVEL, "ENEMY_BLUE!");
				ally_color = ALLY_RED;
				enemy_color = ENEMY_BLUE;
			} else if (buffer[11] == ENEMY_RED) {
				LOG(RECEIVE_LOG_LEVEL, "ENEMY_RED!");
				ally_color = ALLY_BLUE;
				enemy_color = ENEMY_RED;
			}
            memcpy(&curr_yaw, buffer, 4);
            memcpy(&curr_pitch, buffer + 4, 4);
            LOG(RECEIVE_LOG_LEVEL, "Get yaw:%f pitch:%f", curr_yaw, curr_pitch);
            if (buffer[9] == 1) {
                if (mark == 0) {
                    mark = 1;
                    mark_yaw = curr_yaw;
                    mark_pitch = curr_pitch;
                }
                LOG(RECEIVE_LOG_LEVEL, "Marked");
            }
        }
        cnt = 0;
    }
}
