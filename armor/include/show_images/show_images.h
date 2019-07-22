//
// Created by xinyang on 19-3-27.
//

#ifndef _SHOW_IMAGES_H_
#define _SHOW_IMAGES_H_

#include <opencv2/core.hpp>
#include <armor_finder/armor_finder.h>

//
void showArmorBoxes(std::string windows_name, const cv::Mat &src, const ArmorBoxes &armor_boxes);
void showArmorBox(std::string windows_name, const cv::Mat &src, const ArmorBox &armor_box);
void showLightBlobs(std::string windows_name, const cv::Mat &src, const LightBlobs &light_blobs);
void showArmorBoxesClass(std::string window_names, const cv::Mat &src, const ArmorBoxes &boxes);
void showTrackSearchingPos(std::string window_names, const cv::Mat &src, const cv::Rect2d pos);

#endif /* _SHOW_IMAGES_H_ */
