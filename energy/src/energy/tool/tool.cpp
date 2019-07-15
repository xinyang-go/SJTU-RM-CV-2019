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

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于计算预测的击打点坐标
// ---------------------------------------------------------------------------------------------------------------------
void Energy::rotate(cv::Point target_point) {
    int x1, x2, y1, y2;
    //    为了减小强制转换的误差
    x1 = circle_center_point.x * 100;
    x2 = target_point.x * 100;
    y1 = circle_center_point.y * 100;
    y2 = target_point.y * 100;

    predict_point.x = static_cast<int>(
            (x1 + (x2 - x1) * cos(-predict_rad * PI / 180.0) - (y1 - y2) * sin(-predict_rad * PI / 180.0)) / 100);
    predict_point.y = static_cast<int>(
            (y1 - (x2 - x1) * sin(-predict_rad * PI / 180.0) - (y1 - y2) * cos(-predict_rad * PI / 180.0)) / 100);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数将像素差转换到实际距离差
// ---------------------------------------------------------------------------------------------------------------------
void Energy::stretch(cv::Point point_1, cv::Point2f &point_2) {
    if (point_1 == circle_center_point) {
//        cout<<"stretch wrong!"<<endl;
        return;
    }
    double x_0 = point_1.x - circle_center_point.x;
    double y_0 = point_1.y - circle_center_point.y;
    double r_0 = sqrt(pow(x_0, 2) + pow(y_0, 2));

    point_2.x = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * x_0 / r_0);
    point_2.y = static_cast<float >( ARMOR_CENTER_TO_CYCLE_CENTER * y_0 / r_0);
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于计算两点距离
// ---------------------------------------------------------------------------------------------------------------------

double Energy::pointDistance(cv::Point point_1, cv::Point point_2) {
    double distance = 0;
    distance = sqrt(pow(static_cast<double>(point_1.x - point_2.x), 2)
                    + pow(static_cast<double>(point_1.y - point_2.y), 2));
    return distance;
}


//----------------------------------------------------------------------------------------------------------------------
// 计算角度所处的极坐标分区，共五个
// ---------------------------------------------------------------------------------------------------------------------
int Energy::devide(float angle) {
    if (angle < 0)angle += 360;//若angle小于0，说明当前角度范围为-180°~180°
    return angle / 72.0;
}


//----------------------------------------------------------------------------------------------------------------------
// 计算直线上一点的横坐标
// ---------------------------------------------------------------------------------------------------------------------
int Energy::linePointX(const cv::Point2f &p1, const cv::Point2f &p2, int y) {
    return (p2.x - p1.x) / (p2.y - p1.y) * (y - p1.y) + p1.x;
}



//----------------------------------------------------------------------------------------------------------------------
// 计算旋转矩形内的两点占比
// ---------------------------------------------------------------------------------------------------------------------
double Energy::nonZeroRateOfRotateRect(cv::Mat &bin, const cv::RotatedRect &rotatedRect) {
    int cnt = 0;
    cv::Point2f corners[4];
    rotatedRect.points(corners);
    sort(corners, &corners[4], [](cv::Point2f p1, cv::Point2f p2) {
        return p1.y < p2.y;
    });
    for (int r = corners[0].y; r < corners[1].y; r++) {
        auto start = min(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) - 1;
        auto end = max(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) + 1;
        if (start < 0)start = 0;
        if (end > 640)end = 640;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    for (int r = corners[1].y; r < corners[2].y; r++) {
        auto start = min(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) - 1;
        auto end = max(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) + 1;
        if (start < 0)start = 0;
        if (end > 640)end = 640;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    for (int r = corners[2].y; r < corners[3].y; r++) {
        auto start = min(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) - 1;
        auto end = max(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) + 1;
        if (start < 0)start = 0;
        if (end > 640)end = 640;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    return double(cnt) / rotatedRect.size.area();
}