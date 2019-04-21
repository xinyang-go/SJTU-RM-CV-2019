//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::StructingElementClose(cv::Mat &src){
    if (src.empty())return;
    //threshold(src, src, energy_part_param_.CAMERA_GRAY_THRESH, 255, THRESH_BINARY);
    Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
    morphologyEx(src, src, MORPH_CLOSE, element);
}

void Energy::StructingElementErodeDilate(cv::Mat &src) {
    cv::Mat src_out, src_out_out;
    Mat element_erode = getStructuringElement(MORPH_RECT, Size(4, 4));
    Mat element_dilate = getStructuringElement(MORPH_RECT, Size(20, 20));
    erode(src,src_out, element_erode);
    imshow("erode", src_out);
    dilate(src_out, src_out_out, element_dilate);
    imshow("dilate", src_out_out);
}
