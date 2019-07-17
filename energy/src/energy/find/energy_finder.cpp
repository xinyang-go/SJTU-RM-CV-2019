//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内所有的大风车扇叶
// ---------------------------------------------------------------------------------------------------------------------
int Energy::findFans(const cv::Mat src) {
    if (src.empty())return 0;
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > fan_contours;
    FanStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
//	imshow("fan struct",src_bin);
    findContours(src_bin, fan_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto &fan_contour : fan_contours) {
        if (!isValidFanContour(src_bin, fan_contour)) {
            continue;
        }
        fans.emplace_back(cv::minAreaRect(fan_contour));

//        RotatedRect cur_rect = minAreaRect(fan_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        double cur_contour_area = contourArea(fan_contour);
//        double non_zero_rate = nonZeroRateOfRotateRect(src_bin, cur_rect);
//        if (length > 60 && width > 20) {
//            fans.emplace_back(cv::minAreaRect(fan_contour));
//            cout << cur_rect.center << endl;
//            cout << "fan area: " << length << '\t' << width << endl;
//            cout << "non zero: " << nonZeroRateOfRotateRect(src_bin, cur_rect) << endl;
//            cout << "rate: " << cur_contour_area / cur_size.area() << endl;
//        }
    }
//    showFans("fan", src_bin);
    if (fans.size() < last_fans_cnt) {
        last_fans_cnt = static_cast<int>(fans.size());
        return -1;//寻找到的扇叶比上一帧少，说明该帧有误，返回-1
    }
    last_fans_cnt = static_cast<int>(fans.size());
    return static_cast<int>(fans.size());
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内所有的大风车装甲板模块
// ---------------------------------------------------------------------------------------------------------------------
int Energy::findArmors(const cv::Mat src) {
    if (src.empty())return 0;
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > armor_contours;
    std::vector<vector<Point> > armor_contours_external;//用总轮廓减去外轮廓，只保留内轮廓，除去流动条的影响。

    ArmorStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    findContours(src_bin, armor_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    imshow("armor struct", src_bin);
//    findContours(src_bin, armor_contours_external, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

//    for (int i = 0; i < armor_contours_external.size(); i++)//去除外轮廓
//    {
//        unsigned long external_contour_size = armor_contours_external[i].size();
//        for (int j = 0; j < armor_contours.size(); j++) {
//            unsigned long all_size = armor_contours[j].size();
//            if (external_contour_size == all_size) {
//                swap(armor_contours[j], armor_contours[armor_contours.size() - 1]);
//                armor_contours.pop_back();
//                break;
//            }
//        }
//    }
    for (auto &armor_contour : armor_contours) {
        if (!isValidArmorContour(armor_contour)) {
            continue;
        }
        armors.emplace_back(cv::minAreaRect(armor_contour));
//        RotatedRect cur_rect = minAreaRect(armor_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if (length > 5 && width > 5) {
//            armors.emplace_back(cv::minAreaRect(armor_contour));
//            cout << "armor area: " << length << '\t' << width << '\t' << cur_rect.center << endl;
//        }

    }

//    cout<<armors.size()<<endl;
//    showArmors("armor",src);

//    if (armors.size() < 1)cout << "no armors!" << endl;

    return static_cast<int>(armors.size());
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内大风车中心字母“R”
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findCenterR(const cv::Mat src) {
    if (src.empty())return false;
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);
    }
    std::vector<vector<Point> > center_R_contours;
    CenterRStruct(src_bin);
//    imshow("R struct",src_bin);
    findContours(src_bin, center_R_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (auto &center_R_contour : center_R_contours) {
        if (!isValidCenterRContour(center_R_contour)) {
            continue;
        }
        centerR = cv::minAreaRect(center_R_contour);
        float target_length =
                target_armor.size.height > target_armor.size.width ? target_armor.size.height : target_armor.size.width;
        circle_center_point = centerR.center;
        circle_center_point.y += target_length / 7.5;//实际最小二乘得到的中心在R的下方

//        RotatedRect cur_rect = minAreaRect(center_R_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if (length < 10 || width < 5 || length>19) {
//            continue;
//        }
//        std::vector<cv::Point2f> intersection;
//        if (rotatedRectangleIntersection(cur_rect, center_ROI, intersection) != 0 &&
//            contourArea(intersection) > energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN) {
//            centerR = cv::minAreaRect(center_R_contour);
//            cout << "center R area: " << length << '\t' << width << '\t' << cur_rect.center << endl;
//            cout << "R intersection: " << contourArea(intersection) << endl;
//            return true;
//        }

        return true;
    }
    cout << "find center R false!" << endl;
    return false;

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为含流动条的扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy:: findFlowStripFan(const cv::Mat src) {
    if (src.empty())return false;
    static Mat src_bin;
    static Mat src_copy;
    src_bin = src.clone();
    src_copy = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > flow_strip_fan_contours;
    FlowStripFanStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
//    imshow("flow strip fan struct", src_bin);

    findContours(src_bin, flow_strip_fan_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto &flow_strip_fan_contour : flow_strip_fan_contours) {
        if (!isValidFlowStripFanContour(src_bin, flow_strip_fan_contour)) {
            continue;
        }
        flow_strip_fan = cv::minAreaRect(flow_strip_fan_contour);

//        RotatedRect cur_rect = minAreaRect(flow_strip_fan_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        double cur_contour_area = contourArea(flow_strip_fan_contour);
//        double non_zero_rate = nonZeroRateOfRotateRect(src_bin, cur_rect);
//        if (length > 40 && width > 30 && length < 110 && width < 100) {
//            cout << cur_rect.center<<endl;
//            flow_strip_fan = cv::minAreaRect(flow_strip_fan_contour);
//            cout << "flow strip fan area: " << length << '\t' << width << endl;
//            cout << "non zero: " << non_zero_rate << endl;
//            cout<<cur_contour_area / cur_size.area()<<endl;
//        }

        return true;
    }
//    showFlowStripFan("strip fan", src_bin);
    cout << "flow strip fan false!" << endl;
    return false;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找流动条
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStrip(const cv::Mat src) {
    if (src.empty())return false;
    cv::Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    FlowStripStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    imshow("flow strip struct", src_bin);

    std::vector<vector<Point> > flow_strip_contours;
    findContours(src_bin, flow_strip_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto &flow_strip_contour : flow_strip_contours) {
        if (!isValidFlowStripContour(flow_strip_contour)) {
            continue;
        }
        flow_strip = cv::minAreaRect(flow_strip_contour);
//        RotatedRect cur_rect = minAreaRect(flow_strip_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if (length / width > 4 && width > 7 && width<30) {
//            cout << cur_rect.center << endl;
//            flow_strip = cv::minAreaRect(flow_strip_contour);
//            cout << "flow strip area: " << length << '\t' << width << endl;
//        }
        return true;
    }
    cout << "flow strip false!" << endl;
    return false;

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于框取中心R的寻找范围
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findCenterROI(const cv::Mat src) {
    cv::Mat src_mask = src.clone();
    target_armor.size.height *= 1.3;
    target_armor.size.width *= 1.3;
    Point2f vertices[4];
    vector<Point2f> mask_rect;
    target_armor.points(vertices);   //计算矩形的4个顶点
    for (int i = 0; i < 4; i++)
        line(src_mask, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 0), 15);
//    imshow("fill", src_mask);
    if (!findFlowStrip(src_mask))return false;
    float length = target_armor.size.height > target_armor.size.width ?
                   target_armor.size.height : target_armor.size.width;

    Point2f p2p(flow_strip.center.x - target_point.x,
                flow_strip.center.y - target_point.y);
    p2p = p2p / pointDistance(flow_strip.center, target_point);//单位化
    center_ROI = cv::RotatedRect(cv::Point2f(flow_strip.center + p2p * length * 1.25),
                                 Size2f(length * 1.4, length * 1.4), -90);
    return true;

}


