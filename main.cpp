//
// Created by xixiliadorabarry on 1/24/19.
//
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "energy/energy.h"
#include "include/uart/uart.h"
#include "energy/param_struct_define.h"
#include "energy/constant.h"
#include "camera/camera_wrapper.h"
#include "camera/video_wrapper.h"
#include "camera/wrapper_head.h"
#include "armor_finder/armor_finder.h"

#include <time.h>
#include <thread>

using namespace cv;
using namespace std;

#define ENERGY_STATE 1
#define ARMOR_STATE 0

int state = ENERGY_STATE;
float yaw, pitch;

void uartReceive(Uart* uart);

int main()
{
    Uart uart;
	bool flag = true;
	short done = 0;//用于检测是否已经读完初始激光中心时的角度

	while (flag)
	{
        int ally_color = ALLY_RED;
        int energy_part_rotation = CLOCKWISE;

	    int from_camera = 1;
	    cout<<"Input 1 for camera, 0 for video files"<<endl;
	    cin>>from_camera;

		WrapperHead *video;
		if(from_camera)
		    video = new CameraWrapper;
		else
		    video = new VideoWrapper("r_l_640.avi", "fan_640.avi");

		if (video->init()) {
			cout << "Video source initialization successfully." << endl;
		}

		Mat src, src_none;

		ArmorFinder armorFinder(ENEMY_BLUE, uart);

        Energy energy(uart);
        energy.setAllyColor(ally_color);
        energy.setRotation(energy_part_rotation);

        static thread receive(uartReceive, &uart);

        if(state==1 && done == 0){
            energy.uart.receive_data();
            done = 1;
        }

//        energy.sendTargetByUart(-8,-8,-8);


		time_t t1 = time(nullptr), t2 = time(nullptr);

		while (video->read(src, src_none))
		{
//			if(!from_camera)energy.extract(src);
            if(state == 1){
                imshow("src", src);
                energy.run(src);
            }else{
                armorFinder.run(src_none);
            }

			if (waitKey(10) == 'q') {
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
        }else if(cnt==1 && buffer[0]=='a'){
            state = ARMOR_STATE;
        }else{
            sscanf(buffer, "%f, %f", &yaw, &pitch);
        }
        cnt = 0;
    }
}
