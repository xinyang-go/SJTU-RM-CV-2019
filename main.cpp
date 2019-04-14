//
// Created by xixiliadorabarry on 1/24/19.
//
#include <iostream>
#include <opencv2/core/core.hpp>

#include "energy/energy.h"
#include "uart/uart.h"
#include "energy/param_struct_define.h"
#include "energy/constant.h"
#include "camera/camera_wrapper.h"
#include "camera/video_wrapper.h"
#include "camera/wrapper_head.h"
#include "armor_finder/armor_finder.h"
#include <options/options.h>
#include <log.h>

#include <thread>

using namespace cv;
using namespace std;

#define ENERGY_STATE 1
#define ARMOR_STATE 0

int state = ARMOR_STATE;
float yaw=0, pitch=0;

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

		WrapperHead *video;
		if(from_camera)
		    video = new CameraWrapper;
		else
		    video = new VideoWrapper("r_l_640.avi", "fan_640.avi");

		if (video->init()) {
			cout << "Video source initialization successfully." << endl;
		}

		Mat energy_src, armor_src;

		ArmorFinder armorFinder(ENEMY_BLUE, uart);

        Energy energy(uart);
        energy.setAllyColor(ally_color);
        energy.setRotation(energy_part_rotation);

		while (video->read(energy_src, armor_src))
		{
		    if(show_origin) {
                imshow("enery src", energy_src);
                imshow("armor src", armor_src);
            }
            if(state == ENERGY_STATE){
                energy.run(energy_src);
            }else{
                armorFinder.run(armor_src);
            }

			if (waitKey(1) == 'q') {
				flag = false;
				break;
			}
		}
		delete video;
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
        }buffer[cnt] = 0;
        if(cnt==1 && buffer[0]=='e'){
            state = ENERGY_STATE;
            LOGM("State switch to energy!");
        }else if(cnt==1 && buffer[0]=='a'){
            state = ARMOR_STATE;
            LOGM("State switch to armor!");
        }else{
            sscanf(buffer, "%f %f", &yaw, &pitch);
            LOGM("Get yaw:%f pitch:%f", yaw, pitch);
        }
        cnt = 0;
    }
}
