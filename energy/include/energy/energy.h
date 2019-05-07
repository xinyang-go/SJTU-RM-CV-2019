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
#include "uart/uart.h"

using std::vector;

class Energy {
public:
	Energy(Uart &u);
	~Energy();
	int run(cv::Mat &src);

    cv::Point2f uart_hit_point;
	clock_t start;
	Uart &uart;

    void setAllyColor(int color);
    void setRotation(int rotation);

	void extract(cv::Mat &src);

	void sendTargetByUart(float x, float y, float z);


private:

	EnergyPartParam energy_part_param_;
	LiftHeight lift_height_;
	bool isSendTarget;
	int fans_cnt;
	int armors_cnt;
	int count;
	int last_fans_cnt;
	int last_armors_cnt;
	double radius;
	double target_position;
	double last_target_position;
	double last_hit_position;
	float target_armor;
	int ally_color_;
	int energy_part_rotation;
	float attack_distance;
	int send_cnt;
	double rectified_focal_length;
	double theta;//电机pitch轴应旋转的角度
	double phi;//电机yaw轴应旋转的角度
	float yaw_rotation;
	float pitch_rotation;
	int position_mode;
	int last_position_mode;
    int isLeftVertexFound, isTopVertexFound, isRightVertexFound, isBottomVertexFound;

	std::vector<EnergyPart> fans;
	std::vector<EnergyPart> armors;
    std::vector<EnergyPart> gimble_zero_points;

	cv::Point cycle_center;
	cv::Point target_center;
	cv::Point last_target_center;
	cv::Point hit_point;
	std::vector<float>fanPosition;
	std::vector<float>armorPosition;
	std::vector<cv::Point> Armor_center;
    std::vector<cv::Point> first_armor_centers;
    std::vector<cv::Point> all_armor_centers;
    cv::Point left, right, top, bottom;
	cv::Mat src_blue, src_red, src_green;
    


	void initEnergyPartParam();

	int findFan(const cv::Mat &src, vector<EnergyPart> &fans, int &last_fans_cnt);
	int findArmor(const cv::Mat &src, vector<EnergyPart> &armors, int &last_armors_cnt);
    int findGimbleZeroPoint(const cv::Mat &src, vector<EnergyPart> &gimble_zero_point);

	void showFanContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &fans);
	void showArmorContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &armors);
	void showBothContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &fans,
		const std::vector<EnergyPart> &armors);

	bool isValidFanContour(const vector<cv::Point> &fan_contour);
	bool isValidArmorContour(const vector<cv::Point> &armor_contour);

    void getFanPosition(std::vector<float> &fanPosition, const std::vector<EnergyPart> &fans, cv::Point cycle_center, double radius);
	void getArmorPosition(std::vector<float> &armorPosition, const std::vector<EnergyPart> &armors, cv::Point cycle_center, double radius);
	void getFirstArmorCenters(vector<EnergyPart> &armors, std::vector<cv::Point> &first_armor_centers);
	void getAllArmorCenters();
	void getPosition(cv::Point point, double &angle);

	void cycleQuickCalculate(std::vector<cv::Point> &first_armor_centers, cv::Point &cycle_center, double &radius);
    void cycleDefaultCalculateConst(cv::Point &cycle_center, double &radius);
    void cycleCalculate();
    void cycleLeastFit();

	void findTarget(const std::vector<float>fanPosition, const std::vector<float>armorPosition, float &target_armor);

    void findWholeCycle(const std::vector<cv::Point>&first_armor_centers);

	void saveFourPoints(std::vector<cv::Point> &FourPoints, cv::Point point_1, cv::Point point_2, cv::Point point_3, cv::Point point_4);
    void savePoint2f(std::vector<cv::Point2f> &point_save, cv::Point point);
    double pointDistance(cv::Point point_1, cv::Point point_2);
    void rotate(double rad, double radius, cv::Point center, cv::Point point_old, cv::Point &point_new);
	void stretch(cv::Point point_1, cv::Point2f &point_2);
	void cycle(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point &center, double &radius);

    void getHitPoint();
	bool changeTarget();
    void gimbleRotation();

	void splitBayerBG(cv::Mat &src, cv::Mat &blue, cv::Mat &red);
	void imagePreprocess(cv::Mat &src);

	void StructingElementClose(cv::Mat &src,int length, int width);
	void StructingElementErodeDilate(cv::Mat &src);

};

#endif //ENERGY_H

