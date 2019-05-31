//
// Created by xixiliadorabarry on 3/5/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

//extern float curr_yaw, curr_pitch, mark_yaw, mark_pitch;
//extern int mark;


int Energy::run(cv::Mat &src){
//    imshow("src",src);
    fans.clear();
    armors.clear();
    fanPosition.clear();
    armorPosition.clear();
//    gimble_zero_points.clear();
    isSendTarget = false;

	changeMark();
	if (isMark)return 0;
//	cout<<"yaw"<<origin_yaw<<endl;

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


    if(armors_cnt>=4 && fans_cnt>=3) {
        FILE *fp = fopen(PROJECT_DIR"/Mark/mark.txt", "w");
        if (fp) {
            fprintf(fp, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp);
            save_new_mark = false;
        }
        FILE *fp_all = fopen(PROJECT_DIR"/Mark/mark_all.txt", "a");
        if (fp_all) {
            fprintf(fp_all, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp_all);
        }
    }
    if(armors_cnt==5){
        FILE *fp_best = fopen(PROJECT_DIR"/Mark/mark_best.txt", "a");
        if(fp_best){
            fprintf(fp_best, "yaw: %f, pitch: %f\n",origin_yaw, origin_pitch);
            fclose(fp_best);
        }
    }
//    cout<<"armors_cnt: "<<armors_cnt<<"fans_cnt: "<<fans_cnt<<endl;
//    cout<<"armors_cnt: "<<armors_cnt<<"fans_cnt: "<<fans_cnt<<endl;
//    if(armors_cnt != fans_cnt+1)
//    {
//        return 0;
//    }
    //cout<<"clock: "<<energy_part_rotation<<endl;
    getAllArmorCenters();
//    cout<<"all_armor_centers.size(): "<<all_armor_centers.size()<<endl;
    cycleLeastFit();

//    cycle_center = cv::Point(335, 246);
//    radius = 116.936;
//    attack_distance = ATTACK_DISTANCE * 120/ radius;

//	attack_distance = 674 + 1286 * 75 * (1/radius - 1/133.85);
//	cout<<"radius"<<radius<<endl;
//	cout << "attack distance: " << attack_distance << endl;
//    attack_distance = 752;//单项赛
    attack_distance = 718;

    getFanPosition(fanPosition, fans, cycle_center, radius);
    getArmorPosition(armorPosition, armors, cycle_center, radius);
    findTarget(fanPosition, armorPosition, target_armor);
//    cout << "The target armor's position is " << target_armor << endl;
//    cout<<"The target armor center is: "<<target_center<<endl;

//    cout<<target_armor<<endl;
	if (energy_rotation_init) {
		initRotation();
		return 0;
	}

    getHitPoint();
//    hit_point = target_center;
//    cout << "The hit point position is " << hit_point << endl;
    
//    cout<<"send"<<endl;
//    cout<<"position mode: "<<position_mode<<endl;

    gimbleRotation();
    if(changeTarget())target_cnt++;

//	if (!isSendTarget)return 0;
    sendTargetByUart(yaw_rotation, pitch_rotation, target_cnt);

//    cout<<target_cnt<<endl;

//    cout<<"yaw: "<<yaw_rotation<<'\t'<<"pitch: "<<pitch_rotation<<endl;
//    cout<<"curr_yaw: "<<mcuData.curr_yaw<<'\t'<<"curr_pitch: "<<mcuData.curr_pitch<<endl;

//    cout<<"send_cnt: "<<send_cnt<<endl;


}

//-----------------------------------------------------------------------------------

/*
//此处用于标定云台在摄像头视频中的零点
    findGimbleZeroPoint(src,gimble_zero_points);
    cout<<"gimble zero points: :"<<gimble_zero_points.size()<<endl;
    showFanContours("zero",src,gimble_zero_points);
    cycle_center = cv::Point(291,305);
    if(gimble_zero_points.size()>0)hit_point = gimble_zero_points.at(0).rect.center;
*/




