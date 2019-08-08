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
//    imshow("dilate_1", src);
    erode(src,src, element_erode_1);
//    imshow("erode_1", src);
    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
    erode(src,src, element_erode_3);
//    imshow("erode_3", src);
//    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);
//    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);
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
//    imshow("dilate_1", src);
    erode(src,src, element_erode_1);
//    imshow("erode_1", src);
//    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
//    erode(src,src, element_erode_3);
//    imshow("erode_3", src);

//    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);
//    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);

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
//    imshow("dilate_1", src);
    erode(src,src, element_erode_1);
//    imshow("erode_1", src);
    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
    erode(src,src, element_erode_3);
//    imshow("erode_3", src);
//    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);
//    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);
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
//    imshow("dilate_1", src);
    erode(src,src, element_erode_1);
//    imshow("erode_1", src);
    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
    erode(src,src, element_erode_3);
//    imshow("erode_3", src);
//    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);
//    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数对图像进行腐蚀与膨胀操作
// ---------------------------------------------------------------------------------------------------------------------
void Energy::FlowStripStructSub(cv::Mat &src) {
    Mat element_dilate_1 = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat element_erode_1 = getStructuringElement(MORPH_RECT, Size(4, 4));
    Mat element_dilate_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    Mat element_erode_2 = getStructuringElement(MORPH_RECT, Size(3 , 3));
    Mat element_dilate_3 = getStructuringElement(MORPH_RECT, Size(2, 2));
    Mat element_erode_3 = getStructuringElement(MORPH_RECT, Size(2 , 2));
    Mat element_dilate_4 = getStructuringElement(MORPH_RECT, Size(2, 2));

    erode(src,src, element_erode_1);
//    imshow("sub_erode_1", src);
//    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
    erode(src,src, element_erode_3);
//    imshow("sub_erode_3", src);
//    erode(src,src, element_erode_4);
//    imshow("erode_4", src);
    dilate(src, src, element_dilate_1);
//    imshow("sub_dilate_1", src);
    dilate(src, src, element_dilate_2);
//    imshow("sub_dilate_2", src);
//    dilate(src, src, element_dilate_3);
//    imshow("dilate_3", src);
//    dilate(src, src, element_dilate_4);
//    imshow("dilate_4", src);
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
//    imshow("erode_1", src);
    dilate(src, src, element_dilate_1);
//    imshow("dilate_1", src);
//    dilate(src, src, element_dilate_2);
//    imshow("dilate_2", src);
//    erode(src,src, element_erode_2);
//    imshow("erode_2", src);
}