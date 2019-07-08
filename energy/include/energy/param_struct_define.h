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



//----------------------------------------------------------------------------------------------------------------------
// 此结构体为能量机关模块的结构体，用于寻找矩形轮廓
// ---------------------------------------------------------------------------------------------------------------------
struct EnergyPart {
	cv::RotatedRect rect;
	float angle;
	vector<cv::Point> contour;

	explicit EnergyPart(vector<cv::Point> &c) : contour(c) {
		rect = cv::minAreaRect(c);
		angle = cv::minAreaRect(c).angle;
	};
};



//----------------------------------------------------------------------------------------------------------------------
// 此结构体包括能量机关参数
// ---------------------------------------------------------------------------------------------------------------------
struct EnergyPartParam {
	int GRAY_THRESH;//二值化阈值
	int SPLIT_GRAY_THRESH;//通道分离二值化阈值
	int FAN_GRAY_THRESH;//扇叶识别二值化阈值
	int ARMOR_GRAY_THRESH;//装甲板识别二值化阈值

	long FAN_CONTOUR_AREA_MAX;//扇叶面积最大值
	long FAN_CONTOUR_AREA_MIN;//扇叶面积最小值
	long FAN_CONTOUR_LENGTH_MIN;//扇叶长边长度最小值
    long FAN_CONTOUR_LENGTH_MAX;//扇叶长边长度最大值
	long FAN_CONTOUR_WIDTH_MIN;//扇叶宽边长度最小值
    long FAN_CONTOUR_WIDTH_MAX;//扇叶宽边长度最大值
	float FAN_CONTOUR_HW_RATIO_MAX;//扇叶长宽比最大值
	float FAN_CONTOUR_HW_RATIO_MIN;//扇叶长宽比最小值

	long ARMOR_CONTOUR_AREA_MAX;//装甲板面积最大值
	long ARMOR_CONTOUR_AREA_MIN;//装甲板面积最小值
	long ARMOR_CONTOUR_LENGTH_MIN;//装甲板长边长度最小值
	long ARMOR_CONTOUR_WIDTH_MIN;//装甲板长边长度最大值
	long ARMOR_CONTOUR_LENGTH_MAX;//装甲板宽边长度最小值
	long ARMOR_CONTOUR_WIDTH_MAX;//装甲板宽边长度最大值
	float ARMOR_CONTOUR_HW_RATIO_MAX;//装甲板长宽比最大值
	float ARMOR_CONTOUR_HW_RATIO_MIN;//装甲板长宽比最小值

    long CENTER_R_CONTOUR_AREA_MAX;//风车中心R面积最大值
    long CENTER_R_CONTOUR_AREA_MIN;//风车中心R面积最小值
    long CENTER_R_CONTOUR_LENGTH_MIN;//风车中心R长边长度最小值
    long CENTER_R_CONTOUR_WIDTH_MIN;//风车中心R长边长度最大值
    long CENTER_R_CONTOUR_LENGTH_MAX;//风车中心R宽边长度最小值
    long CENTER_R_CONTOUR_WIDTH_MAX;//风车中心R宽边长度最大值
    float CENTER_R_CONTOUR_HW_RATIO_MAX;//风车中心R长宽比最大值
    float CENTER_R_CONTOUR_HW_RATIO_MIN;//风车中心R长宽比最小值

    long FLOW_LIGHT_CONTOUR_HW_RATIO_MIN;//流动条长宽比最小值_

	float TWIN_ANGEL_MAX;//扇叶和装甲板匹配时极坐标角度差的最大值
	long INTERSETION_CONTOUR_AREA_MIN;//扇叶与装甲板匹配时的最小重合面积

	long TARGET_CHANGE_DISTANCE_MAX;//目标未更改时，目标装甲板中心与原目标装甲板中心的距离变化最大值
};


#endif //PARAM_STRUCT_DEFINE_H

