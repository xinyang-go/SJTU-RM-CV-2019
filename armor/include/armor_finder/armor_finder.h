//
// Created by xinyang on 19-3-27.
//

#ifndef _ARMOR_FINDER_H_
#define _ARMOR_FINDER_H_

#include <map>
#include <constants.h>
#include <opencv2/core.hpp>
#include <opencv2/tracking.hpp>
#include <serial/serial.h>
#include <armor_finder/classifier/classifier.h>
#include <additions/additions.h>

#define BLOB_RED    ENEMY_RED
#define BLOB_BLUE   ENEMY_BLUE

#define BOX_RED     ENEMY_RED
#define BOX_BLUE    ENEMY_BLUE

#define DISTANCE_HEIGHT_5MM (113.0)     // 单位: m*pixel
#define DISTANCE_HEIGHT     DISTANCE_HEIGHT_5MM

extern std::map<int, string> id2name;   //装甲板id到名称的map
extern std::map<string, int> name2id;   //装甲板名称到id的map

/******************* 灯条类定义 ***********************/
class LightBlob {
public:
    cv::RotatedRect rect;   //灯条位置
    double length;          //灯条长度
    uint8_t blob_color;      //灯条颜色

    LightBlob(cv::RotatedRect &r, uint8_t color) : rect(r), blob_color(color) {
        length = max(rect.size.height, rect.size.width);
    };
    LightBlob() = default;
};

typedef std::vector<LightBlob> LightBlobs;



/******************* 装甲板类定义　**********************/
class ArmorBox{
public:
    cv::Rect2d rect;
    LightBlobs light_blobs;
    uint8_t box_color;
    int id;

    explicit ArmorBox(const cv::Rect &pos=cv::Rect2d(), const LightBlobs &blobs=LightBlobs(), uint8_t color=0, int i=0);

    double blobsDistance() const{
        if(light_blobs.size() == 2){
            auto &x = light_blobs[0].rect.center;
            auto &y = light_blobs[1].rect.center;
            return sqrt((x.x-y.x)*(x.x-y.x) + (x.y-y.y)*(x.y-y.y));
        }
    }

    double lengthDistanceRatio() const {
        if(light_blobs.size() == 2){
            return (light_blobs[0].length+light_blobs[1].length)/2.0
                   / blobsDistance();
        }else{
            return 100;
        }
    }
};

typedef std::vector<ArmorBox> ArmorBoxes;

/********************* 自瞄类定义 **********************/
class ArmorFinder{
public:
    ArmorFinder(uint8_t &color, Serial &u, const string &paras_folder, const uint8_t &use);
    ~ArmorFinder() = default;

private:
    typedef cv::TrackerKCF TrackerToUse;                // Tracker类型定义

    typedef enum{
        SEARCHING_STATE, TRACKING_STATE, STANDBY_STATE
    } State;                                            // 自瞄状态枚举定义

    const uint8_t &enemy_color;                         // 敌方颜色，引用外部变量，自动变化
    State state;                                        // 自瞄状态对象实例
    ArmorBox armor_box;                                 // 当前目标装甲板
    cv::Ptr<cv::Tracker> tracker;                       // tracker对象实例
    Classifier classifier;                              // CNN分类器对象实例，用于数字识别
    int  contour_area;                                  // 装甲区域亮点个数，用于数字识别未启用时判断是否跟丢（已弃用）
    int tracking_cnt;                                   // 记录追踪帧数，用于定时退出追踪
    Serial &serial;                                     // 串口对象，引用外部变量，用于和能量机关共享同一个变量
    const uint8_t &use_classifier;                      // 标记是否启用CNN分类器，引用外部变量，自动变化

    bool findLightBlobs(const cv::Mat &src, LightBlobs &light_blobs);
    bool findArmorBox(const cv::Mat &src, ArmorBox &box);

    bool stateSearchingTarget(cv::Mat &src);            // searching state主函数
    bool stateTrackingTarget(cv::Mat &src);             // tracking state主函数
    bool stateStandBy();                                // stand by state主函数（已弃用）

    void anti_top();                                    // 反小陀螺

public:
    void run(cv::Mat &src);                             // 自瞄主函数
    bool sendBoxPosition();                             // 和主控板通讯
};

#endif /* _ARMOR_FINDER_H_ */
