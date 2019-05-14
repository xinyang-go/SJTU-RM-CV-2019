//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

bool sendTarget(Serial& serial, float x, float y, float z) {
	static short x_tmp, y_tmp, z_tmp;
	static time_t last_time = time(nullptr);
	static int fps;
	uint8_t buff[8];

	time_t t = time(nullptr);
	if (last_time != t) {
		last_time = t;
		std::cout << "fps:" << fps << ", (" << x << "," << y << "," << z << ")" << std::endl;
		fps = 0;
	}
	fps += 1;

	x_tmp = static_cast<short>(x * (32768 - 1) / 100);
	y_tmp = static_cast<short>(y * (32768 - 1) / 100);
	z_tmp = static_cast<short>(z * (32768 - 1) / 1000);

	buff[0] = 's';
	buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
	buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
	buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
	buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
	buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
	buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
	buff[7] = 'e';

	return serial.WriteData(buff, sizeof(buff));
}

void Energy::sendTargetByUart(float x, float y, float z) {
//    if(!changeTarget()){
//        return;
//    }
    sendTarget(serial, x, y, z);
    send_cnt+=1;
}



