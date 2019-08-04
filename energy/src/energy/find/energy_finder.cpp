//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内所有的大风车扇叶
// ---------------------------------------------------------------------------------------------------------------------
int Energy::findFans(const cv::Mat src) {
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return 0;
    }
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > fan_contours;
    FanStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    if (show_process)imshow("fan struct", src_bin);
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
//        float length_width_ratio = length / width;
//        cout << "area: " << cur_contour_area << '\t' << endl;
//        cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//        cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//        cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//        cout<<endl;

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
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return 0;
    }
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > armor_contours;
    std::vector<vector<Point> > armor_contours_external;//用总轮廓减去外轮廓，只保留内轮廓，除去流动条的影响。

    ArmorStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    findContours(src_bin, armor_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    if (show_process)imshow("armor struct", src_bin);

    findContours(src_bin, armor_contours_external, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < armor_contours_external.size(); i++)//去除外轮廓
    {
        unsigned long external_contour_size = armor_contours_external[i].size();
        for (int j = 0; j < armor_contours.size(); j++) {
            unsigned long all_size = armor_contours[j].size();
            if (external_contour_size == all_size) {
                swap(armor_contours[j], armor_contours[armor_contours.size() - 1]);
                armor_contours.pop_back();
                break;
            }
        }
    }

    for (auto &armor_contour : armor_contours) {
        if (!isValidArmorContour(armor_contour)) {
            continue;
        }
        armors.emplace_back(cv::minAreaRect(armor_contour));

//        RotatedRect cur_rect = minAreaRect(armor_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        double cur_contour_area = contourArea(armor_contour);
//        float length_width_ratio = length / width;
//        cout << "area: " << cur_contour_area << '\t' << endl;
//        cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//        cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//        cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//        cout<<endl;

    }

    if (show_info) {
//        if (armors.size() < 1)cout << "no armors!" << endl;
    }

    return static_cast<int>(armors.size());
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内大风车中心字母“R”
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findCenterR(const cv::Mat src) {
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return false;
    }
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);
    }
    std::vector<vector<Point> > center_R_contours;
    CenterRStruct(src_bin);
    if (show_process)imshow("R struct", src_bin);
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
//        double cur_contour_area = contourArea(center_R_contour);
//        float length_width_ratio = length / width;
//        cout << "area: " << cur_contour_area << '\t' << endl;
//        cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//        cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//        cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//        cout<<endl;

        return true;
    }
    if (show_info)cout << "find center R false!" << endl;
//    cv::waitKey(0);
    return false;

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为含流动条的扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStripFan(const cv::Mat src) {
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return false;
    }
    static Mat src_bin;
    static Mat src_copy;
    src_bin = src.clone();
    src_copy = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > flow_strip_fan_contours;
    FlowStripFanStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    if (show_process)imshow("flow strip fan struct", src_bin);

    findContours(src_bin, flow_strip_fan_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    std::vector<cv::RotatedRect> candidate_flow_strip_fans;

    for (auto &flow_strip_fan_contour : flow_strip_fan_contours) {
        if (!isValidFlowStripFanContour(src_bin, flow_strip_fan_contour)) {
            continue;
        }
        flow_strip_fans.emplace_back(cv::minAreaRect(flow_strip_fan_contour));

//        RotatedRect cur_rect = minAreaRect(flow_strip_fan_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        double cur_contour_area = contourArea(flow_strip_fan_contour);
//        float length_width_ratio = length / width;
//        cout << "area: " << cur_contour_area << '\t' << endl;
//        cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//        cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//        cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//        cout<<endl;
    }
    if (flow_strip_fans.empty()) {
        if (show_info)cout << "flow strip fan false!" << endl;\
//        waitKey(0);
        return false;
    }
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找流动条
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStrip(const cv::Mat src) {
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return false;
    }
    cv::Mat src_bin;
    src_bin = src.clone();

    if (src_bin.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src_bin, src_bin, COLOR_GRAY2RGB);

    }
    std::vector<cv::RotatedRect> candidate_target_armors = target_armors;
    for (auto &candidate_target_armor: candidate_target_armors) {
        Point2f vertices[4];
        candidate_target_armor.size.height *= 1.3;
        candidate_target_armor.size.width *= 1.3;
        candidate_target_armor.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++) {
            line(src_bin, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 0), 20);
        }
    }

    cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道

    FlowStripStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    if (show_process)imshow("flow strip struct", src_bin);

    std::vector<vector<Point> > flow_strip_contours;
    findContours(src_bin, flow_strip_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto candidate_flow_strip_fan: flow_strip_fans) {
        for (auto &flow_strip_contour : flow_strip_contours) {
            if (!isValidFlowStripContour(flow_strip_contour)) {
                continue;
            }

            std::vector<cv::Point2f> intersection;
            RotatedRect cur_rect = minAreaRect(flow_strip_contour);

            if (rotatedRectangleIntersection(cur_rect, candidate_flow_strip_fan, intersection) == 0) {
                continue;
            } else if (contourArea(intersection) > energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN) {
                flow_strips.emplace_back(cv::minAreaRect(flow_strip_contour));
//                cout << "intersection: " << contourArea(intersection) << '\t' << cur_rect.center << endl;
            } else {
                continue;
            }

//            Size2f cur_size = cur_rect.size;
//            float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//            float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//            double cur_contour_area = contourArea(flow_strip_contour);
//            float length_width_ratio = length / width;
//            cout << "area: " << cur_contour_area << '\t' << endl;
//            cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//            cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//            cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//            cout<<endl;
        }
    }
    if (flow_strips.empty()) {
        if (show_info)cout << "flow strip false!" << endl;
//        waitKey(0);
        return false;
    } else if (flow_strips.size() > 1) {
        if (show_info)cout << "Too many flow strips!" << endl;
//        waitKey(0);
        return false;
    } else {
        flow_strip = flow_strips.at(0);
        for (auto &candidate_flow_strip_fan: flow_strip_fans) {
            std::vector<cv::Point2f> intersection;
            if (rotatedRectangleIntersection(flow_strip, candidate_flow_strip_fan, intersection) == 0) {
                continue;
            } else if (contourArea(intersection) > energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN) {
                flow_strip_fan = candidate_flow_strip_fan;
            }
        }
        int i = 0;
        for (i = 0; i < target_armors.size(); ++i) {
            std::vector<cv::Point2f> intersection;
            if (rotatedRectangleIntersection(target_armors.at(i), flow_strip_fan, intersection) == 0)
                continue;//返回0表示没有重合面积
            double cur_contour_area = contourArea(intersection);
            if (cur_contour_area > energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN) {
                target_armor = target_armors.at(i);
                target_point = target_armor.center;
            }
        }
    }
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于弱识别寻找流动条
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStripWeak(const cv::Mat src) {
    if (src.empty()) {
        if (show_info) cout << "empty!" << endl;
        return false;
    }
    cv::Mat src_bin;
    src_bin = src.clone();

    if (src_bin.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src_bin, src_bin, COLOR_GRAY2RGB);

    }
    std::vector<cv::RotatedRect> candidate_armors = armors;
    for (auto &candidate_armor: candidate_armors) {
        Point2f vertices[4];
        candidate_armor.size.height *= 1.3;
        candidate_armor.size.width *= 1.3;
        candidate_armor.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++) {
            line(src_bin, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 0), 20);
        }
    }

    cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道

    FlowStripStruct(src_bin);//图像膨胀，防止图像断开并更方便寻找
    if (show_process)imshow("weak struct", src_bin);
//    waitKey(0);

    std::vector<vector<Point> > flow_strip_contours;
    findContours(src_bin, flow_strip_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto &flow_strip_contour : flow_strip_contours) {
        if (!isValidFlowStripContour(flow_strip_contour)) {
            continue;
        }

        flow_strips.emplace_back(cv::minAreaRect(flow_strip_contour));

//        RotatedRect cur_rect = minAreaRect(flow_strip_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        double cur_contour_area = contourArea(flow_strip_contour);
//        float length_width_ratio = length / width;
//        cout << "area: " << cur_contour_area << '\t' << endl;
//        cout << "length: " << length << '\t' << "width: " << width << '\t' << cur_rect.center << endl;
//        cout << "HW: " << length_width_ratio << '\t' << cur_rect.center << endl;
//        cout << "area ratio: " << cur_contour_area / cur_size.area() << '\t' << cur_rect.center << endl;
//        cout << endl;

    }
//    cout << "size: " << flow_strips.size() << endl;

    if (flow_strips.empty()) {
        if (show_info)cout << "weak flow strip false!" << endl;
//        waitKey(0);
        return false;
    } else {
        for (const auto &candidate_flow_strip: flow_strips) {
            for (const auto &candidate_armor: armors) {
                if (pointDistance(candidate_flow_strip.center, candidate_armor.center) <
                    energy_part_param_.STRIP_ARMOR_DISTANCE_MIN ||
                    pointDistance(candidate_flow_strip.center, candidate_armor.center) >
                    energy_part_param_.STRIP_ARMOR_DISTANCE_MAX) {
                    continue;
                }
                float angle_armor = candidate_armor.size.width > candidate_armor.size.height ? candidate_armor.angle :
                                    candidate_armor.angle - 90;
                float angle_strip = candidate_flow_strip.size.width > candidate_flow_strip.size.height ?
                                    candidate_flow_strip.angle: candidate_flow_strip.angle - 90;

                if (abs(angle_armor - angle_strip) < 60 || abs(angle_armor - angle_strip) > 120) {
                    continue;
                }
                target_armor = candidate_armor;
                target_point = candidate_armor.center;
                flow_strip = candidate_flow_strip;
                return true;
            }
        }
        if (show_info)cout << "weak flow strip false!" << endl;
//        waitKey(0);
        return false;
    }
}

//----------------------------------------------------------------------------------------------------------------------
// 此函数用于框取中心R的寻找范围
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findCenterROI(const cv::Mat src) {
    float length = target_armor.size.height > target_armor.size.width ?
                   target_armor.size.height : target_armor.size.width;

    Point2f p2p(flow_strip.center.x - target_point.x,
                flow_strip.center.y - target_point.y);
    p2p = p2p / pointDistance(flow_strip.center, target_point);//单位化
    center_ROI = cv::RotatedRect(cv::Point2f(flow_strip.center + p2p * length * 1.7),
                                 Size2f(length * 1.4, length * 1.4), -90);
    return true;

}


