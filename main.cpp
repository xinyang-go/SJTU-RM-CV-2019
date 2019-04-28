//
// Created by xixiliadorabarry on 1/24/19.
//
#include <iostream>
#include <opencv2/core/core.hpp>

#include <energy/energy.h>
#include <uart/uart.h>
#include <energy/param_struct_define.h>
#include <energy/constant.h>
#include <camera/camera_wrapper.h>
#include <camera/video_wrapper.h>
#include <camera/wrapper_head.h>
#include <armor_finder/armor_finder.h>
#include <options/options.h>
#include <log.h>

#include <thread>

using namespace cv;
using namespace std;

#define ENERGY_STATE 1
#define ARMOR_STATE 0

int state = ENERGY_STATE;
float curr_yaw=0, curr_pitch=0;
float mark_yaw=0, mark_pitch=0;
int mark = 0;

void uartReceive(Uart* uart);

int main(int argc, char *argv[])
{
    process_options(argc, argv);
    Uart uart;
    thread receive(uartReceive, &uart);
	bool flag = true;

	while (flag)
	{
        int ally_color = ALLY_RED;
        int energy_part_rotation = CLOCKWISE;

	    int from_camera = 1;
	    if(!run_with_camera) {
            cout << "Input 1 for camera, 0 for video files" << endl;
            cin >> from_camera;
        }

		WrapperHead *video_armor;
        WrapperHead *video_energy;
		if(from_camera) {
//            video_armor = new CameraWrapper();
            video_energy = new CameraWrapper();
        }else {
            video_armor = new VideoWrapper("r_l_640.avi");
            video_energy = new VideoWrapper("r_l_640.avi");
        }
		if (video_energy->init()) {
			cout << "Video source initialization successfully." << endl;
		}

		Mat energy_src, armor_src;

		ArmorFinder armorFinder(ENEMY_BLUE, uart, "/home/xinyang/Desktop/AutoAim/tools/para/");

        Energy energy(uart);
        energy.setAllyColor(ally_color);
        energy.setRotation(energy_part_rotation);

		while (video_energy->read(energy_src) && video_energy->read(armor_src))
		{
		    if(show_origin) {
                imshow("enery src", energy_src);
                imshow("armor src", armor_src);
            }
            if(state == ENERGY_STATE){
                if(from_camera==0){
                    energy.extract(energy_src);
                }
                energy.run(energy_src);
            }else{
                CNT_TIME(WORD_LIGHT_BLUE, "Armor Time", {
                    armorFinder.run(armor_src);
                });
            }
			if (waitKey(1) == 'q') {
				flag = false;
				break;
			}
		}
		delete video_energy;
		cout << "Program fails. Restarting" << endl;
	}

	return 0;
}


void uartReceive(Uart* uart){
    char buffer[100];
    int cnt=0;
    while(true){
        char data;
        while((data=uart->receive()) != '\n'){
            buffer[cnt++] = data;
            if(cnt >= 100){
//                LOGE("data receive over flow!");
            }
        }
        if(cnt == 10){
            if(buffer[8] == 'e'){
                state = ENERGY_STATE;
//                LOGM("Energy state");
            }else if(buffer[8] == 'a'){
                state = ARMOR_STATE;
//                LOGM("Armor state");
            }
            memcpy(&curr_yaw, buffer, 4);
            memcpy(&curr_pitch, buffer+4, 4);
//            LOGM("Get yaw:%f pitch:%f", curr_yaw, curr_pitch);
            if(buffer[9] == 1){
                if(mark == 0){
                    mark = 1;
                    mark_yaw = curr_yaw;
                    mark_pitch = curr_pitch;
                }

//                LOGM("Marked");
            }
        }
        cnt = 0;
    }
}
