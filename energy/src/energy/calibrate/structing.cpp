//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;




//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::FanStruct(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2 , 2));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1 , 1));

    dilate(src, src, element_dilate_1);
    erode(src,src, element_erode_1);
    erode(src,src, element_erode_2);
    erode(src,src, element_erode_3);
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::ArmorStruct(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2 , 2));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1 , 1));

    dilate(src, src, element_dilate_1);
    erode(src,src, element_erode_1);
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::FlowStripFanStruct(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2 , 2));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1 , 1));

    dilate(src, src, element_dilate_1);
    erode(src,src, element_erode_1);
    erode(src,src, element_erode_2);
    erode(src,src, element_erode_3);
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::FlowStripStruct(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(2 , 2));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(1 , 1));

    dilate(src, src, element_dilate_1);
    erode(src,src, element_erode_1);
    erode(src,src, element_erode_2);
    erode(src,src, element_erode_3);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::CenterRStruct(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(4, 4));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(2, 1));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(4 , 4));

    erode(src,src, element_erode_1);
    dilate(src, src, element_dilate_1);
}