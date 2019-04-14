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

void Energy::extract(cv::Mat &src){
	cv::Rect rect(EXTRACT_POINT_X, EXTRACT_POINT_Y, EXTRACT_WIDTH, EXTRACT_HEIGHT);
	src = src(rect).clone();
	cv::resize(src, src, cv::Size(640, 480), 2);
	imshow("extract", src);
}

void Energy::saveFourPoints(std::vector<cv::Point> &FourPoints, cv::Point point_1, cv::Point point_2, cv::Point point_3, cv::Point point_4) {
	FourPoints.push_back(point_1);
	FourPoints.push_back(point_2);
	FourPoints.push_back(point_3);
	FourPoints.push_back(point_4);
}

void Energy::savePoint2f(std::vector<cv::Point2f> &point_save, cv::Point point) {
	point_save.push_back(static_cast<cv::Point2f>(point));
}

double Energy::pointDistance(cv::Point point_1, cv::Point point_2){
	double distance = 0;
	distance = sqrt(pow(static_cast<double>(point_1.x - point_2.x),2)
			+ pow(static_cast<double>(point_1.y - point_2.y),2));
	return distance;
}

void Energy::rotate(double rad, double radius, cv::Point center, cv::Point point_old, cv::Point &point_new) {
	int x1, x2, y1, y2;
	//    为了减小强制转换的误差
	x1 = center.x * 100;
	x2 = point_old.x * 100;
	y1 = center.y * 100;
	y2 = point_old.y * 100;

	point_new.x = static_cast<int>((x1 + (x2 - x1)*cos(-rad * d2r) - (y1 - y2)*sin(-rad * d2r))/100);
	point_new.y = static_cast<int>((y1 - (x2 - x1)*sin(-rad * d2r) - (y1 - y2)*cos(-rad * d2r))/100);
}

void Energy::stretch(cv::Point point_1, cv::Point2f &point_2){
    if(point_1==cycle_center){
        cout<<"stretch wrong!"<<endl;
        return;
    }
	double x_0 = point_1.x - cycle_center.x;
	double y_0 = point_1.y - cycle_center.y;
    double r_0 = sqrt(pow(x_0, 2)+ pow(y_0, 2));

	point_2.x = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * x_0 / r_0);
	point_2.y = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * y_0 / r_0);
}

void Energy::cycle(cv::Point p1, cv::Point p2, cv::Point p3, cv::Point &center, double &radius){
	double x1, y1, x2, y2, x3, y3;
	double a, b, c, g, e, f;
	x1 = p1.x;
	y1 = p1.y;
	x2 = p2.x;
	y2 = p2.y;
	x3 = p3.x;
	y3 = p3.y;

	//三点确定圆的方程：(2x2-2x1)X+(2y2-2y1)Y=x2²-x1²+y2²-y1²；(2x3-2x2)X+(2y3-2y2)Y=x3²-x2²+y3²-y2²
	e = 2 * (x2 - x1);
	f = 2 * (y2 - y1);
	g = x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1;
	a = 2 * (x3 - x2);
	b = 2 * (y3 - y2);
	c = x3 * x3 - x2 * x2 + y3 * y3 - y2 * y2;
	cycle_center.x = static_cast<int>((g*b - c * f) / (e*b - a * f));
	cycle_center.y = static_cast<int>((a*g - c * e) / (a*f - b * e));
	radius = sqrt((cycle_center.x - x1)*(cycle_center.x - x1) + (cycle_center.y - y1)*(cycle_center.y - y1));

}

