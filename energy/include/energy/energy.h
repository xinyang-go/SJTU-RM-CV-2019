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
    int runSmall(cv::Mat &gimble_src);
	Serial &serial;//串口
	void setEnergyRotationInit();//判断顺逆时针函数
	void extract(cv::Mat &src);//框取图像中的一块区域进行处理
    void sendBigTarget(Serial& serial, float x, float y, float z);
    void sendSmallTarget(Serial& serial, float x, float y, char change, char shoot);


private:
	EnergyPartParam energy_part_param_;//能量机关的参数设置
	bool isMark;//若操作手正在手动标定，则为true
	bool centered=false;//云台是否对准中心
	int fans_cnt;//图像中的扇叶个数
	int armors_cnt;//图像中的装甲板个数
	int centerRs_cnt;//图像中可能的风车中心字母R选区个数
	int last_fans_cnt;//上一帧的扇叶个数
	int last_armors_cnt;//上一帧的装甲板个数
	int gimble_cnt; //经过的帧数
	double radius;//大风车半径
	float target_polar_angle;//待击打装甲板的极坐标角度
    float last_target_polar_angle;//上一帧待击打装甲板的极坐标角度
	uint8_t &ally_color;//我方颜色
	int energy_rotation_direction;//风车旋转方向
	float attack_distance;//步兵与风车平面距离
	int send_cnt;//向主控板发送的数据总次数
	float yaw_rotation;//云台yaw轴应该转到的角度
	float pitch_rotation;//云台pitch轴应该转到的角度
	uint8_t last_mark;//用于记录上一帧操作手是否进行标定
    double predict_rad;//预测提前角
	bool energy_rotation_init;//若仍在判断风车旋转方向，则为true
	int clockwise_rotation_init_cnt;//装甲板顺时针旋转次数
	int anticlockwise_rotation_init_cnt;//装甲板逆时针旋转次数
	float red_origin_yaw, red_origin_pitch;//红方的初始云台对心角度设定值
	float blue_origin_yaw, blue_origin_pitch;//蓝方的初始云台对心角度设定值
	float origin_yaw, origin_pitch;//初始的云台角度设定值
	float target_cnt;//用于记录寻找到的装甲板总数，该值变化则立即中断主控板发射进程，防止重复击打已点亮的装甲板
    bool save_new_mark;//若操作手进行过手动标定，则为true
    bool small_energy_shoot;//若为true，则要求主控板发弹
	std::vector<EnergyPart> fans;//图像中所有扇叶
	std::vector<EnergyPart> armors;//图像中所有装甲板
    std::vector<EnergyPart> centerRs;//风车中心字母R的可能候选区

	cv::Point circle_center_point;//风车圆心坐标
	cv::Point target_point;//目标装甲板中心坐标
	cv::Point last_target_point;//上一帧目标装甲板中心坐标
	cv::Point predict_point;//预测的击打点坐标
	cv::Point former_point;//之前预测的圆心坐标
	std::vector<float>fan_polar_angle;//当前帧所有扇叶的极坐标角度
	std::vector<float>armor_polar_angle;//当前帧所有装甲板的极坐标角度
    std::vector<cv::Point> all_armor_centers;//记录全部的装甲板中心，用于风车圆心和半径的计算
	cv::Mat src_blue, src_red, src_green;//通道分离中的三个图像通道

	void initEnergy();//能量机关初始化
	void initEnergyPartParam();//能量机关参数初始化
	void initRotation();//顺逆时针初始化

	int findFan(const cv::Mat src, int &last_fans_cnt);//寻找图中所有扇叶
	int findArmor(const cv::Mat src, int &last_armors_cnt);//寻找图中所有装甲板
    int findCenterR(const cv::Mat src);//寻找图中可能的风车中心字母R

    bool isValidFanContour(const vector<cv::Point> fan_contour);//扇叶矩形尺寸要求
    bool isValidArmorContour(const vector<cv::Point> armor_contour);//装甲板矩形尺寸要求
    bool isValidCenterRContour(const vector<cv::Point> center_R_contour);//风车中心选区尺寸要求

	void showFanContours(std::string windows_name, const cv::Mat src);//显示扇叶
	void showArmorContours(std::string windows_name, const cv::Mat src);//显示装甲板
	void showBothContours(std::string windows_name, const cv::Mat src);//显示扇叶和装甲板
    void showCenterRContours(std::string windows_name, const cv::Mat src);//显示风车中心候选区R

    void getFanPolarAngle();//获取扇叶极坐标角度
	void getArmorPolarAngle();//获取装甲板极坐标角度
	void getAllArmorCenters();//记录所有装甲板中心坐标

    void circleLeastFit();//利用所有记录的装甲板中心最小二乘法计算圆心和半径

	void findTargetByPolar();//通过极坐标角度匹配获取目标装甲板的极坐标角度和装甲板中心坐标
    void findTargetByIntersection();//通过面积重合度匹配获取目标装甲板的极坐标角度和装甲板中心坐标

    void rotate();//获取预测点位
	void stretch(cv::Point point_1, cv::Point2f &point_2);//将像素差转换为实际距离差
    double pointDistance(cv::Point point_1, cv::Point point_2);//计算两点距离

	void writeDownMark();//记录操作手标定的云台初始角度

    void getPredictPoint();//获取预测点位
    void getAimPoint();//通过自瞄逻辑计算点位
	bool changeTarget();//判断目标是否改变
	void changeMark();//操作手手动修改标定值
    void gimbleRotation();//计算云台旋转角度

	void splitBayerBG(cv::Mat src, cv::Mat &blue, cv::Mat &red);//拜耳阵列分离
	void imagePreprocess(cv::Mat &src);//图像通道分离
    void hsvFilter(cv::Mat &src);//此函数通过HSV颜色空间对图像纯度进行限制，进行滤光

	void StructingElementClose(cv::Mat &src,int length, int width);//闭运算
	void StructingElementErodeDilate(cv::Mat &src);//腐蚀和膨胀

};

#endif //ENERGY_H

