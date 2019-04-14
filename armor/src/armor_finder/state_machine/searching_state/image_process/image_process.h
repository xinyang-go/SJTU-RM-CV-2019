//
// Created by xinyang on 19-3-27.
//

#ifndef _IMAGE_PROCESS_H_
#define _IMAGE_PROCESS_H_

#include <opencv2/core.hpp>
#include <armor_finder/armor_finder.h>

void imageColorSplit(cv::Mat &src_input, cv::Mat &split, EnemyColor color);
void imagePreProcess(cv::Mat &src);

#endif /* _IMAGE_PROCESS_H_ */
