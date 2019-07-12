//
// Created by xixiliadorabarry on 1/24/19.
//
#ifndef ENERGY_H
#define ENERGY_H

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <constants.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include "energy/constant.h"
#include "energy/param_struct_define.h"
#include "serial/serial.h"
#include "additions/additions.h"
#include "options/options.h"

using std::vector;

class Energy {
public:
    Energy(Serial &u, uint8_t &color);//构造函数，参数为串口和敌方颜色
    ~Energy();//默认析构函数

    int runBig(cv::Mat &gimble_src, cv::Mat &chassis_src);

    int runBig(cv::Mat &gimble_src);

    int runSmall(cv::Mat &gimble_src, cv::Mat &chassis_src);

    int runSmall(cv::Mat &gimble_src);

    Serial &serial;//串口
    void setBigEnergyInit();//设置大符初始化，判断顺逆时针函数
    void setSmallEnergyInit();//设置小符初始化
    void extract(cv::Mat &src);//框取图像中的一块区域进行处理
    void sendTarget(Serial &serial, float x, float y, float z);


private:
    EnergyPartParam energy_part_param_;//能量机关的参数设置
    EnergyPartParam gimble_energy_part_param_;//云台摄像头能量机关的参数设置
    EnergyPartParam chassis_energy_part_param_;//底盘摄像头能量机关的参数设置

    bool isMark;//若操作手正在手动标定，则为true
    bool isGimble;//同时具有底盘和云台摄像头时，处于云台摄像头对心过程
    bool isChassis;//同时具有底盘和云台摄像头时，处于底盘摄像头击打过程
    bool isGuessing;//当前处于发弹到新目标出现的过程，则为true，此时猜测下一个目标
    bool isPredicting;//当前处于新目标出现到发弹的过程，则为true，此时正常击打
    bool energy_rotation_init;//若仍在判断风车旋转方向，则为true
    bool manual_mark;//若操作手进行过手动标定，则为true
    bool shoot;//若为true，则要求主控板发弹
    bool startguessing;//进入猜测状态的标志

    uint8_t last_mark;//用于记录上一帧操作手是否进行标定
    uint8_t &ally_color;//我方颜色

    double radius;//大风车半径

    int send_cnt;//向主控板发送的数据总次数
    int last_fans_cnt;//上一帧的扇叶个数
    int guess_devide;//刚进入猜测状态时，猜测目标点在极坐标中的分区
    int energy_rotation_direction;//风车旋转方向
    int clockwise_rotation_init_cnt;//装甲板顺时针旋转次数
    int anticlockwise_rotation_init_cnt;//装甲板逆时针旋转次数

    float target_polar_angle;//待击打装甲板的极坐标角度
    float last_target_polar_angle;//上一帧待击打装甲板的极坐标角度
    float guess_polar_angle;//猜测的下一个目标装甲板极坐标角度
    float last_base_angle;//上一帧的各扇叶在0区（0°~72°）的基础角度
    float predict_rad;//预测提前角
    float attack_distance;//步兵与风车平面距离
    float yaw_rotation;//云台yaw轴应该转到的角度
    float pitch_rotation;//云台pitch轴应该转到的角度
    float origin_yaw, origin_pitch;//初始的云台角度设定值

    timeval time_start_guess;

    std::vector<cv::RotatedRect> fans;//图像中所有扇叶
    std::vector<cv::RotatedRect> armors;//图像中所有可能装甲板（可能存在误识别)

    std::vector<cv::Point> all_target_armor_centers;//记录全部的装甲板中心，用于风车圆心和半径的计算

    cv::RotatedRect centerR;//风车中心字母R的可能候选区
    cv::RotatedRect flow_strip;//图像中所有流动条（理论上只有一个）
    cv::RotatedRect flow_strip_fan;//图像中所有流动条所在扇叶（理论上只有一个）
    cv::RotatedRect center_ROI;//风车中心候选区
    cv::RotatedRect target_armor;//目标装甲板（理论上仅一个）

    cv::Point circle_center_point;//风车圆心坐标
    cv::Point target_point;//目标装甲板中心坐标
    cv::Point last_target_point;//上一帧目标装甲板中心坐标
    cv::Point guess_point;
    cv::Point predict_point;//预测的击打点坐标

    cv::Mat src_blue, src_red, src_green;//通道分离中的三个图像通道

    void initEnergy();//能量机关初始化
    void initEnergyPartParam();//能量机关参数初始化
    void initRotation();//顺逆时针初始化

    void clearAll();//清空各vector
    void initImage(cv::Mat &src);//图像预处理

    void startChassis();//从云台摄像头对心状态进入底盘摄像头击打状态
    bool stayGuessing();//保持在猜测模式

    int findFans(const cv::Mat src);//寻找图中所有扇叶
    int findArmors(const cv::Mat src);//寻找图中所有装甲板
    bool findCenterR(const cv::Mat src);//寻找图中可能的风车中心字母R
    bool findFlowStrip(const cv::Mat src);//寻找图中的流动条
    bool findCenterROI(const cv::Mat src);//框取中心R候选区
    bool findFlowStripFan(const cv::Mat src);//寻找图中的流动条所在扇叶

    bool isValidFanContour(cv::Mat &src, const vector<cv::Point> &fan_contour);//扇叶矩形尺寸要求
    bool isValidArmorContour(const vector<cv::Point> &armor_contour);//装甲板矩形尺寸要求
    bool isValidCenterRContour(const vector<cv::Point> &center_R_contour);//风车中心选区尺寸要求
    bool isValidFlowStripContour(const vector<cv::Point> &flow_strip_contour);//流动条扇叶矩形尺寸要求
    bool isValidFlowStripFanContour(cv::Mat &src, const vector<cv::Point> &flow_strip_fan_contour);//流动条扇叶矩形尺寸要求

    void showFanContours(std::string windows_name, const cv::Mat src);//显示扇叶
    void showArmorContours(std::string windows_name, const cv::Mat src);//显示装甲板
    void showBothContours(std::string windows_name, const cv::Mat src);//显示扇叶和装甲板
    void showCenterRContours(std::string windows_name, const cv::Mat src);//显示风车中心候选区R
    void showFlowStripFanContours(std::string windows_name, const cv::Mat src);//显示流动条所在扇叶
    void showGuessTarget(std::string windows_name, const cv::Mat src);//显示猜测点位

    void getOrigin();//获得云台对心所需角度
    void guessTarget();//获得猜测击打点位

    void circleLeastFit();//利用所有记录的装甲板中心最小二乘法计算圆心和半径

    void findTargetByIntersection();//通过面积重合度匹配获取目标装甲板的极坐标角度和装甲板中心坐标
    bool findTargetInFlowStripFan();//在已发现的流动条区域中寻找待击打装甲板

    void rotate(cv::Point target_point);//获取预测点位
    void stretch(cv::Point point_1, cv::Point2f &point_2);//将像素差转换为实际距离差
    int devide(float angle);//将极坐标分为五个区域，判断一个角度处于哪个区域
    int linePointX(const cv::Point2f &p1, const cv::Point2f &p2, int y);//计算直线上一点横坐标
    double pointDistance(cv::Point point_1, cv::Point point_2);//计算两点距离
    double nonZeroRateOfRotateRect(cv::Mat &bin, const cv::RotatedRect &rotatedRect);//计算旋转矩形内亮点占比

    void writeDownMark();//记录操作手标定的云台初始角度

    void getTargetPolarAngle();
    void getPredictPoint(cv::Point target_point);//获取预测点位
    void getAimPoint(cv::Point target_point);//通过自瞄逻辑计算点位
    bool changeTarget();//判断目标是否改变
    void changeMark();//操作手手动修改标定值
    void gimbleRotation();//计算云台旋转角度
    void getAllArmorCenters();//记录所有装甲板中心坐标

    void judgeBigShoot();//判断大符模式是否可以发弹
    void judgeSmallShoot();//判断小符模式是否可以发弹
    bool is_guessing_timeout();//判断猜测模式是否超时（没打中）

    void splitBayerBG(cv::Mat src, cv::Mat &blue, cv::Mat &red);//拜耳阵列分离
    void imagePreprocess(cv::Mat &src);//图像通道分离
    void hsvFilter(cv::Mat &src);//此函数通过HSV颜色空间对图像纯度进行限制，进行滤光

    void StructingElementClose(cv::Mat &src, int length, int width);//闭运算
    void StructingElementErodeDilate(cv::Mat &src);//腐蚀和膨胀
    void StructingElementDilateErode(cv::Mat &src);//腐蚀和膨胀

};

#endif //ENERGY_H

