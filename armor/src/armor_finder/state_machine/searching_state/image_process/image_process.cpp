//
// Created by xinyang on 19-3-27.
//

#include "image_process.h"

static void splitBayerBG(cv::Mat &src, cv::Mat &blue, cv::Mat &red) {
    uchar* data;
    uchar* bayer_data[2];
    for (int i = 0; i < src.rows; ++i) {
        data = src.ptr<uchar>(i);
        bayer_data[0] = blue.ptr<uchar>(i / 2);
        for (int j = 0; j < blue.cols; ++j, data += 2) {
            bayer_data[0][j] = *data;
        }
        data = src.ptr<uchar>(++i) + 1;
        bayer_data[1] = red.ptr<uchar>(i / 2);
        for (int j = 0; j < red.cols; ++j, data += 2) {
            bayer_data[1][j] = *data;
        }
    }
}

void imageColorSplit(cv::Mat &src_input, cv::Mat &split, EnemyColor color) {
    cv::Mat blue(240, 320, CV_8UC1), red(240, 320, CV_8UC1);
    if(src_input.type() == CV_8UC1){
        splitBayerBG(src_input, blue, red);
        if(color == ENEMY_RED){
            split = red - blue;
        }else if(color == ENEMY_BLUE){
            split = blue - red;
        }
    }else if(src_input.type() == CV_8UC3){
        std::vector<cv::Mat> channels;
        cv::split(src_input, channels);
        resize(channels.at(0), blue, cv::Size(640, 480));
        resize(channels.at(2), red, cv::Size(640, 480));
        if(color == ENEMY_RED){
            split = red;
        }else if(color == ENEMY_BLUE){
            split = blue;
        }
    }

}

void imagePreProcess(cv::Mat &src) {
    static cv::Mat kernel_erode = getStructuringElement(cv::MORPH_RECT, cv::Size(1, 4));
    erode(src, src, kernel_erode);

    static cv::Mat kernel_dilate = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 4));
    dilate(src, src, kernel_dilate);

    static cv::Mat kernel_erode2 = getStructuringElement(cv::MORPH_RECT, cv::Size(2, 4));
    erode(src, src, kernel_erode2);

    static cv::Mat kernel_dilate2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 6));
    dilate(src, src, kernel_dilate2);

    float alpha = 1.5;
    int beta = 0;
    src.convertTo(src, -1, alpha, beta);
}
