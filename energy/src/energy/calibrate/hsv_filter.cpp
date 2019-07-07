//
// Created by sun on 19-7-7.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于利用HSV颜色空间对图像进行预处理
// ---------------------------------------------------------------------------------------------------------------------

void Energy::hsvFilter(cv::Mat &src){
    Mat hsv, hsv_in_range;
    cvtColor(src, hsv, CV_BGR2HSV);
//    imshow("hsv", hsv);
    vector<Mat> hsv_channels;
    split(hsv, hsv_channels);
    Mat H = hsv_channels.at(0);
    Mat S = hsv_channels.at(1);
    Mat V = hsv_channels.at(2);
//    imshow("S", S);
    inRange(hsv,Scalar(0,150,0),Scalar(180,255,255),hsv_in_range);
//    imshow("in range", hsv_in_range);
}