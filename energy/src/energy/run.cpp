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
// 此函数为大能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src, cv::Mat &chassis_src){
    if(chassis_src.empty())
        runBig(gimble_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else if(!centered) {
        armors.clear();
        armor_polar_angle.clear();
        changeMark();
        if (isMark)return 0;

        threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
        imshow("yun",gimble_src);

        armors_cnt = findArmor(gimble_src,  last_armors_cnt);
        if(armors_cnt!=1) return 0;//滤去漏判的帧

        getAllArmorCenters();
        circleLeastFit();

//    attack_distance = 752;//单项赛
        attack_distance = 718;

        if (energy_rotation_init) {
            initRotation();
            return 0;
        }

        if(++gimble_cnt==10){
            former_point=circle_center_point;
            gimble_cnt=0;
        }

        if(former_point==predict_point&&gimble_cnt==9&&predict_point!=Point(0,0)) {
            centered=true;
            cout<<"gimble focused!"<<endl;
        }
        predict_point=circle_center_point;
        cout<<gimble_cnt<<endl;
        cout<<"center:("<<predict_point.x<<','<<predict_point.y<<")\n";
        gimbleRotation();

//    cout<<"send"<<endl;
//    cout<<"position mode: "<<position_mode<<endl;
        sendTargetByUart(yaw_rotation, pitch_rotation, target_cnt);
        return 0;
    }
//    if(centered)
//        destroyAllWindows();
    return 0;
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数为大能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runBig(cv::Mat &gimble_src){
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

    threshold(gimble_src, gimble_src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
//    imshow("bin",src);

    fans_cnt = findFan(gimble_src, last_fans_cnt);
//    cout<<"fans_cnt: "<<fans_cnt<<endl;
    if(fans_cnt==-1) return 0;//滤去漏判的帧
//    if(fans_cnt>0)showFanContours("fan",src);
//    fans_cnt=0;

    armors_cnt = findArmor(gimble_src, last_armors_cnt);
//    cout<<"armors_cnt: "<<armors_cnt<<endl;
    if(armors_cnt==-1) return 0;//滤去漏判的帧
//    if(armors_cnt>0) showArmorContours("armor",src);

    if(armors_cnt != fans_cnt+1) return 0;

    centerRs_cnt = findCenterR(gimble_src);
//    if(centerRs_cnt>0)showCenterRContours("R", gimble_src);

    getAllArmorCenters();
    circleLeastFit();
    attack_distance = ATTACK_DISTANCE;

    getFanPolarAngle();
    getArmorPolarAngle();
    findTarget();

    if(armors_cnt>0||fans_cnt>0) showBothContours("Both", gimble_src);

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
    return 0;
}





//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关模式主控制流函数，且步兵需要同时拥有云台摄像头和底盘摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runSmall(cv::Mat &gimble_src, cv::Mat &chassis_src){
    if(chassis_src.empty())runSmall(gimble_src);//仅拥有云台摄像头则调用单摄像头的run函数
    else return 0;
}





//----------------------------------------------------------------------------------------------------------------------
// 此函数为小能量机关模式主控制流函数，且步兵仅拥有云台摄像头
// ---------------------------------------------------------------------------------------------------------------------
int Energy::runSmall(cv::Mat &gimble_src){

}




