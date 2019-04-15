//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

extern float mark_yaw, mark_pitch;
extern int mark;

int Energy::run(cv::Mat &src){
    fans.clear();
    armors.clear();
    fanPosition.clear();
    armorPosition.clear();
    gimble_zero_points.clear();

    if(mark==0)return 0;

//    if(all_armor_centers.size()>200)all_armor_centers.clear();
//    if(first_armor_centers.size()>200)first_armor_centers.clear();
//    cout<<"first_armor_centers.size(): "<<first_armor_centers.size()<<endl;

//    imagePreprocess(src);
//    imshow("img_preprocess",src);

    threshold(src, src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
//    imshow("bin",src);


    fans_cnt = findFan(src, fans, last_fans_cnt);
//    cout<<"fans_cnt: "<<fans_cnt<<endl;
    if(fans_cnt==-1) return 0;//滤去漏判的帧
//    if(fans_cnt>0)showFanContours("fan",src,fans);
//    fans_cnt=0;

    armors_cnt = findArmor(src, armors, last_armors_cnt);
//    cout<<"armors_cnt: "<<armors_cnt<<endl;
    if(armors_cnt==-1) return 0;//滤去漏判的帧
//    if(armors_cnt>0) showArmorContours("armor",src,armors);

    if(armors_cnt>0||fans_cnt>0) showBothContours("Both",src, fans, armors);

    if(armors_cnt != fans_cnt+1) return 0;


/*
//此处用于标定云台在摄像头视频中的零点
    findGimbleZeroPoint(src,gimble_zero_points);
    cout<<"gimble zero points: :"<<gimble_zero_points.size()<<endl;
    showFanContours("zero",src,gimble_zero_points);
    cycle_center = cv::Point(291,305);
    if(gimble_zero_points.size()>0)hit_point = gimble_zero_points.at(0).rect.center;
*/


    getAllArmorCenters();
    cout<<"all_armor_centers.size(): "<<all_armor_centers.size()<<endl;
    cycleLeastFit();

    cycle_center = cv::Point(416,227);
    radius = 203.665;
    getFanPosition(fanPosition, fans, cycle_center, radius);
    getArmorPosition(armorPosition, armors, cycle_center, radius);
    findTarget(fanPosition, armorPosition, target_armor);
    cout << "The target armor's position is " << target_armor << endl;
    cout<<"The target armor center is: "<<target_center<<endl;

    getHitPoint();
    hit_point = target_center;
    cout << "The hit point position is " << hit_point << endl;
//    hit_point = cycle_center;

    gimbleRotation();

    sendTargetByUart(yaw_rotation, pitch_rotation, attack_distance);
    cout<<"yaw: "<<yaw_rotation<<'\t'<<"pitch: "<<pitch_rotation<<endl;
    cout<<"mark_yaw: "<<mark_yaw<<'\t'<<"mark_pitch: "<<mark_pitch<<endl;

    cout<<"send_cnt: "<<send_cnt<<endl;



}



