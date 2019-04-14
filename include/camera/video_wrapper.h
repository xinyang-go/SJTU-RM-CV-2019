//
// Created by zhikun on 18-11-16.
// wrapper for video read from file
//

#ifndef STEREOVISION_FROM_VIDEO_FILE_VIDEO_WRAPPER_H
#define STEREOVISION_FROM_VIDEO_FILE_VIDEO_WRAPPER_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "wrapper_head.h"


class VideoWrapper:public WrapperHead {
public:
    VideoWrapper(const std::string& filename0, const std::string& filename1);
    ~VideoWrapper();


    /**
     * @brief initialize cameras
     * @return bool value: whether it success
     */
    bool init() final;


    /**
     * @brief read images from camera
     * @param src_left : output source video of left camera
     * @param src_right : output source video of right camera
     * @return bool value: whether the reading is successful
     */
    bool read(cv::Mat &src_left, cv::Mat &src_right) final;
private:
    cv::VideoCapture video0, video1;

};


#endif //STEREOVISION_FROM_VIDEO_FILE_VIDEO_WRAPPER_H
