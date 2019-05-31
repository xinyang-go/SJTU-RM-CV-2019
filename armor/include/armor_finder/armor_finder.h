//
// Created by xinyang on 19-3-27.
//

#ifndef _ARMOR_FINDER_H_
#define _ARMOR_FINDER_H_

#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <serial/serial.h>
#include <armor_finder/classifier/classifier.h>
#include "additions/additions.h"

class ArmorFinder{
public:
    ArmorFinder(uint8_t &color, Serial &u, string paras_folder, const uint8_t &use);
    ~ArmorFinder() = default;

private:
    typedef cv::TrackerKCF TrackerToUse;

    typedef enum{
        SEARCHING_STATE, TRACKING_STATE, STANDBY_STATE
    } State;

    const uint8_t &enemy_color;
    State state;
    cv::Rect2d armor_box;
    cv::Ptr<cv::Tracker> tracker;
    cv::Mat src_gray;

    Classifier classifier;

    int  contour_area;
	Serial &serial;
    const uint8_t &use_classifier;

    bool stateSearchingTarget(cv::Mat &src);
    bool stateTrackingTarget(cv::Mat &src);
    bool stateStandBy();
public:
    void run(cv::Mat &src);
    bool sendBoxPosition();
};

#define BLOB_RED ENEMY_RED
#define BLOB_BLUE ENEMY_BLUE

class LightBlob {
public:
    cv::RotatedRect rect;
    double length;
    uint8_t BlobColor;

    explicit LightBlob(cv::RotatedRect &r) : rect(r) {
        length = max(rect.size.height, rect.size.width);
    };
    bool operator<(LightBlob &l2) { return this->rect.center.x < l2.rect.center.x; }
    bool operator<=(LightBlob &l2) { return this->rect.center.x <= l2.rect.center.x; }
    bool operator>(LightBlob &l2) { return this->rect.center.x > l2.rect.center.x; }
    bool operator>=(LightBlob &l2) { return this->rect.center.x >= l2.rect.center.x; }
};

#endif /* _ARMOR_FINDER_H_ */
