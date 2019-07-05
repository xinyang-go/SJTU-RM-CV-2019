//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数为能量机关模式主控制流函数
// ---------------------------------------------------------------------------------------------------------------------
int Energy::run(cv::Mat &gimble_src, cv::Mat &base_src){

    cv::Mat src = gimble_src;

//    imshow("src",src);
    fans.clear();
    armors.clear();
    centerRs.clear();
    fan_polar_angle.clear();
    armor_polar_angle.clear();

	changeMark();
	if (isMark)return 0;
//    imagePreprocess(src);
//    imshow("img_preprocess",src);

    threshold(src, src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
//    imshow("bin",src);

    fans_cnt = findFan(src, last_fans_cnt);
//    cout<<"fans_cnt: "<<fans_cnt<<endl;
    if(fans_cnt==-1) return 0;//滤去漏判的帧
//    if(fans_cnt>0)showFanContours("fan",src);
//    fans_cnt=0;

    armors_cnt = findArmor(src, last_armors_cnt);
//    cout<<"armors_cnt: "<<armors_cnt<<endl;
    if(armors_cnt==-1) return 0;//滤去漏判的帧
//    if(armors_cnt>0) showArmorContours("armor",src);

    if(armors_cnt>0||fans_cnt>0) showBothContours("Both",src);

    centerRs_cnt = findCenterR(src);
    if(centerRs_cnt>0)showCenterRContours("R",src);


    if(armors_cnt != fans_cnt+1)
    {
        return 0;
    }

    getAllArmorCenters();
    circleLeastFit();
    attack_distance = ATTACK_DISTANCE;

    getFanPolarAngle();
    getArmorPolarAngle();
    findTarget();

	if (energy_rotation_init) {
		initRotation();
		return 0;
	}
    getPredictPoint();
    gimbleRotation();
    sendTargetByUart(yaw_rotation, pitch_rotation, target_cnt);

//    cout<<"yaw: "<<yaw_rotation<<'\t'<<"pitch: "<<pitch_rotation<<endl;
//    cout<<"curr_yaw: "<<mcuData.curr_yaw<<'\t'<<"curr_pitch: "<<mcuData.curr_pitch<<endl;
//    cout<<"send_cnt: "<<send_cnt<<endl;
}




