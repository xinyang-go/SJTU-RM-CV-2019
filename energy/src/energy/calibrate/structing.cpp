//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::StructingElementClose(cv::Mat &src,int length, int width){
    if (src.empty())return;
    //threshold(src, src, energy_part_param_.CAMERA_GRAY_THRESH, 255, THRESH_BINARY);
    Mat element = getStructuringElement(MORPH_RECT, Size(length, width));
    morphologyEx(src, src, MORPH_CLOSE, element);
}

void Energy::StructingElementErodeDilate(cv::Mat &src) {
    cv::Mat src_out, src_out_out;
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(8, 6));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(4,4));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));


//    dilate(src, src, element_dilate_1);
//    imshow("dilate_1", src);

    erode(src,src, element_erode_1);
//    imshow("erode_1", src);

    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);

    erode(src,src, element_erode_2);
//    imshow("erode_2", src);

    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);
}
