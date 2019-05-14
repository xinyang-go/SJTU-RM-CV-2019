//
// Created by xinyang on 19-3-27.
//

#ifndef _ARMOR_FINDER_H_
#define _ARMOR_FINDER_H_

#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <serial/serial.h>
#include <armor_finder/classifier/classifier.h>

typedef enum{
    ENEMY_BLUE, ENEMY_RED
} EnemyColor;

class ArmorFinder{
public:
    ArmorFinder(EnemyColor &color, Serial &u, string paras_folder, const bool &use);
    ~ArmorFinder() = default;

private:
    typedef cv::TrackerKCF TrackerToUse;

    typedef enum{
        SEARCHING_STATE, TRACKING_STATE, STANDBY_STATE
    } State;

    const EnemyColor &enemy_color;
    State state;
    cv::Rect2d armor_box;
    cv::Ptr<cv::Tracker> tracker;
    cv::Mat src_gray;

    Classifier classifier;

    int  contour_area;
	Serial &serial;
    const bool &use_classifier;

    bool stateSearchingTarget(cv::Mat &src);
    bool stateTrackingTarget(cv::Mat &src);
    bool stateStandBy();
public:
    void run(cv::Mat &src);
    bool sendBoxPosition();
};

struct LightBlob {
    cv::RotatedRect rect;
    double length;

    explicit LightBlob(cv::RotatedRect &r) : rect(r) {
        length = max(rect.size.height, rect.size.width);
    };
    bool operator<(LightBlob &l2) { return this->rect.center.x < l2.rect.center.x; }
    bool operator<=(LightBlob &l2) { return this->rect.center.x <= l2.rect.center.x; }
    bool operator>(LightBlob &l2) { return this->rect.center.x > l2.rect.center.x; }
    bool operator>=(LightBlob &l2) { return this->rect.center.x >= l2.rect.center.x; }
};

#endif /* _ARMOR_FINDER_H_ */
