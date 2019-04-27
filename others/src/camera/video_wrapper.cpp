//
// Created by xixiliadorabarry on 1/24/19.
//

#include "camera/video_wrapper.h"


VideoWrapper::VideoWrapper(const std::string &filename) {
    video.open(filename);
}

VideoWrapper::~VideoWrapper() = default;


bool VideoWrapper::init() {
    return video.isOpened();
}

bool VideoWrapper::read(cv::Mat &src) {
    return video.read(src);

}
