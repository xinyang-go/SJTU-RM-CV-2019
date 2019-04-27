//
// Created by zhikun on 18-11-18.
//

#ifndef STEREOVISION_FROM_VIDEO_FILE_WRAPPER_HEAD_H
#define STEREOVISION_FROM_VIDEO_FILE_WRAPPER_HEAD_H

#include <opencv2/core/core.hpp>

/**
 * @brief A virtual class for wrapper of camera and video files
 */
class WrapperHead {
public:
    virtual ~WrapperHead() = default;;
    virtual bool init() = 0;
    virtual bool read(cv::Mat &src) = 0;

};



#endif //STEREOVISION_FROM_VIDEO_FILE_WRAPPER_HEAD_H
