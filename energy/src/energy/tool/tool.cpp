//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数选取图像中的一部分进行处理
// ---------------------------------------------------------------------------------------------------------------------
void Energy::extract(cv::Mat &src){
	cv::Rect rect(EXTRACT_POINT_X, EXTRACT_POINT_Y, EXTRACT_WIDTH, EXTRACT_HEIGHT);
	src = src(rect).clone();
	cv::resize(src, src, cv::Size(640, 480), 2);
	imshow("extract", src);
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于计算预测的击打点坐标
// ---------------------------------------------------------------------------------------------------------------------
void Energy::rotate() {
	int x1, x2, y1, y2;
	//    为了减小强制转换的误差
	x1 = circle_center_point.x * 100;
	x2 = target_point.x * 100;
	y1 = circle_center_point.y * 100;
	y2 = target_point.y * 100;

	predict_point.x = static_cast<int>((x1 + (x2 - x1)*cos(-predict_rad * d2r) - (y1 - y2)*sin(-predict_rad * d2r))/100);
	predict_point.y = static_cast<int>((y1 - (x2 - x1)*sin(-predict_rad * d2r) - (y1 - y2)*cos(-predict_rad * d2r))/100);
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数将像素差转换到实际距离差
// ---------------------------------------------------------------------------------------------------------------------
void Energy::stretch(cv::Point point_1, cv::Point2f &point_2){
    if(point_1==circle_center_point){
//        cout<<"stretch wrong!"<<endl;
        return;
    }
	double x_0 = point_1.x - circle_center_point.x;
	double y_0 = point_1.y - circle_center_point.y;
    double r_0 = sqrt(pow(x_0, 2)+ pow(y_0, 2));

	point_2.x = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * x_0 / r_0);
	point_2.y = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * y_0 / r_0);
}