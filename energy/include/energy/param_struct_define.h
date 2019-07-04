//
// Created by xixiliadorabarry on 1/24/19.
//
#ifndef PARAM_STRUCT_DEFINE_H
#define PARAM_STRUCT_DEFINE_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using std::vector;

struct EnergyPart {
	cv::RotatedRect rect;
	float angle;
	vector<cv::Point> contour;

	explicit EnergyPart(vector<cv::Point> &c) : contour(c) {
		rect = cv::minAreaRect(c);
		angle = cv::minAreaRect(c).angle;
	};
};

struct EnergyPartParam {
	double RPM;
	double HIT_TIME;

	int GRAY_THRESH;
	int SPLIT_GRAY_THRESH;
	int FAN_GRAY_THRESH;
	int ARMOR_GRAY_THRESH;

	long FAN_CONTOUR_AREA_MAX;
	long FAN_CONTOUR_AREA_MIN;
	long FAN_CONTOUR_LENGTH_MIN;
    long FAN_CONTOUR_LENGTH_MAX;
	long FAN_CONTOUR_WIDTH_MIN;
    long FAN_CONTOUR_WIDTH_MAX;
	float FAN_CONTOUR_HW_RATIO_MAX;
	float FAN_CONTOUR_HW_RATIO_MIN;

	long ARMOR_CONTOUR_AREA_MAX;
	long ARMOR_CONTOUR_AREA_MIN;
	long ARMOR_CONTOUR_LENGTH_MIN;
	long ARMOR_CONTOUR_WIDTH_MIN;
	long ARMOR_CONTOUR_LENGTH_MAX;
	long ARMOR_CONTOUR_WIDTH_MAX;
	float ARMOR_CONTOUR_HW_RATIO_MAX;
	float ARMOR_CONTOUR_HW_RATIO_MIN;

    long CENTER_R_CONTOUR_AREA_MAX;
    long CENTER_R_CONTOUR_AREA_MIN;
    long CENTER_R_CONTOUR_LENGTH_MIN;
    long CENTER_R_CONTOUR_WIDTH_MIN;
    long CENTER_R_CONTOUR_LENGTH_MAX;
    long CENTER_R_CONTOUR_WIDTH_MAX;
    float CENTER_R_CONTOUR_HW_RATIO_MAX;
    float CENTER_R_CONTOUR_HW_RATIO_MIN;

	float TWIN_ANGEL_MAX;
};

struct LiftHeight{
    float LIFT_0;
    float LIFT_30;
    float LIFT_60;
    float LIFT_90;
    float LIFT_minus_30;
    float LIFT_minus_60;
    float LIFT_minus_90;
};

typedef struct GMAngle_t{
    float yaw;
    float pitch;
}GMAngle_t;

extern GMAngle_t aim;

#endif //PARAM_STRUCT_DEFINE_H

