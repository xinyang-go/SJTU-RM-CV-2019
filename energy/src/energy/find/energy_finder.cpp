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
    StructingElementErodeDilate(src_bin);//图像膨胀，防止图像断开并更方便寻找
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
//        if(length>20&&width>20){
//			fans.emplace_back(cv::minAreaRect(fan_contour));
//			cout<<"fan area: "<<length<<'\t'<<width<<endl;
//			cout<<nonZeroRateOfRotateRect(src_bin,cur_rect)<<endl;
//		}
    }
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

    StructingElementErodeDilate(src_bin);//图像膨胀，防止图像断开并更方便寻找
//    imshow("armor struct", src_bin);

    findContours(src_bin, armor_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
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
//        if(length>10&&width>5){
//            armors.emplace_back(cv::minAreaRect(armor_contour));
//            cout<<"armor area: "<<length<<'\t'<<width<<'\t'<<cur_rect.center<<endl;
//        }

    }
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
    StructingElementErodeDilate(src_bin);
//    imshow("R struct",src_bin);
    findContours(src_bin, center_R_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    for (auto &center_R_contour : center_R_contours) {
        if (!isValidCenterRContour(center_R_contour)) {
            continue;
        }
        centerR = cv::minAreaRect(center_R_contour);
        circle_center_point = centerR.center;
        return true;

//        RotatedRect cur_rect = minAreaRect(center_R_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if(length>10 && width>5){
//            centerRs.emplace_back(cv::minAreaRect(center_R_contour));
//            cout<<"center R area: "<<length<<'\t'<<width<<'\t'<<cur_rect.center<<endl;
//        }
    }
    return false;

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为含流动条的扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStripFan(const cv::Mat src) {
    if (src.empty())return false;
    static Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    std::vector<vector<Point> > flow_strip_fan_contours;
    StructingElementErodeDilate(src_bin);//图像膨胀，防止图像断开并更方便寻找
    imshow("flow strip fan struct", src_bin);

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
//        if (length > 10 && width > 10) {
//            cout << cur_rect.center;
//            flow_strip_fan = cv::minAreaRect(flow_strip_fan_contour);
//            cout << "flow strip fan area: " << length << '\t' << width << endl;
//        }

        return true;
    }
    return false;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找流动条
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findFlowStrip(const cv::Mat src) {
    imshow("1", src);
    if (src.empty())return false;
    cv::Mat src_bin;
    src_bin = src.clone();
    if (src.type() == CV_8UC3) {
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
    StructingElementErodeDilate(src_bin);//图像膨胀，防止图像断开并更方便寻找
//    imshow("flow strip struct", src_bin);

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
//        if (length > 40 && width > 5) {
//            cout << cur_rect.center << endl;
//            flow_strip = cv::minAreaRect(flow_strip_contour);
//            cout << "flow strip fan area: " << length << '\t' << width << endl;
//        }
        return true;
    }
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
    center_ROI = cv::RotatedRect(cv::Point2f(flow_strip.center + p2p * length * 1.4),
                                 Size2f(length * 1.2, length * 1.2), -90);
    return true;

}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidFanContour(cv::Mat &src, const vector<cv::Point> &fan_contour) {
    double cur_contour_area = contourArea(fan_contour);
    if (cur_contour_area > energy_part_param_.FAN_CONTOUR_AREA_MAX ||
        cur_contour_area < energy_part_param_.FAN_CONTOUR_AREA_MIN) {
        //cout<<cur_contour_area<<" "<<energy_fan_param_.CONTOUR_AREA_MIN<<" "<<energy_fan_param_.CONTOUR_AREA_MAX<<endl;
        //cout<<"area fail."<<endl;
        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(fan_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;//将矩形的长边设置为长
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;//将矩形的短边设置为宽
    if (length < energy_part_param_.FAN_CONTOUR_LENGTH_MIN || width < energy_part_param_.FAN_CONTOUR_WIDTH_MIN ||
        length > energy_part_param_.FAN_CONTOUR_LENGTH_MAX || width > energy_part_param_.FAN_CONTOUR_WIDTH_MAX) {
        //cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }
    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN) {
        //cout<<"length width ratio fail."<<endl;
        return false;
        //长宽比不合适
    }
//    if (cur_contour_area / cur_size.area() < energy_part_param_.FAN_CONTOUR_AREA_RATIO_MIN)
//        return false;//轮廓对矩形的面积占有率不合适
    double non_zero_rate = nonZeroRateOfRotateRect(src, cur_rect);
    if (non_zero_rate > energy_part_param_.FAN_NON_ZERO_RATE_MAX ||
        non_zero_rate < energy_part_param_.FAN_NON_ZERO_RATE_MIN)
        return false;
    //亮点占比不合格
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为装甲板
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidArmorContour(const vector<cv::Point> &armor_contour) {
    double cur_contour_area = contourArea(armor_contour);
    if (cur_contour_area > energy_part_param_.ARMOR_CONTOUR_AREA_MAX ||
        cur_contour_area < energy_part_param_.ARMOR_CONTOUR_AREA_MIN) {
        //cout<<cur_contour_area<<" "<<energy_fan_param_.CONTOUR_AREA_MIN<<" "<<energy_fan_param_.CONTOUR_AREA_MAX<<endl;
        //cout<<"area fail."<<endl;
        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(armor_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;//将矩形的长边设置为长
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;//将矩形的短边设置为宽
    if (length < energy_part_param_.ARMOR_CONTOUR_LENGTH_MIN || width < energy_part_param_.ARMOR_CONTOUR_WIDTH_MIN ||
        length > energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX || width > energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX) {
        //cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }

    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN) {
        //cout<<"length width ratio fail."<<endl;
        return false;
        //长宽比不合适
    }
    if (cur_contour_area / cur_size.area() < energy_part_param_.ARMOR_CONTOUR_AREA_RATIO_MIN)
        return false;//轮廓对矩形的面积占有率不合适
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为可能的风车中心R候选区
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidCenterRContour(const vector<cv::Point> &center_R_contour) {
    double cur_contour_area = contourArea(center_R_contour);
    if (cur_contour_area > energy_part_param_.ARMOR_CONTOUR_AREA_MAX ||
        cur_contour_area < energy_part_param_.ARMOR_CONTOUR_AREA_MIN) {
        //cout<<cur_contour_area<<" "<<energy_fan_param_.CONTOUR_AREA_MIN<<" "<<energy_fan_param_.CONTOUR_AREA_MAX<<endl;
        //cout<<"area fail."<<endl;
        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(center_R_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;//将矩形的长边设置为长
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;//将矩形的短边设置为宽
    if (length < energy_part_param_.CENTER_R_CONTOUR_LENGTH_MIN || width < energy_part_param_.CENTER_R_CONTOUR_WIDTH_MIN
        || length > energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX ||
        width > energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX) {
        //cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }
    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN) {
        //cout<<"length width ratio fail."<<endl;
        return false;
        //长宽比不合适
    }
    if (cur_contour_area / cur_size.area() < energy_part_param_.CENTER_R_CONTOUR_AREA_RATIO_MIN)
        return false;//轮廓对矩形的面积占有率不合适
    std::vector<cv::Point2f> intersection;
    if (rotatedRectangleIntersection(cur_rect, center_ROI, intersection) == 0 ||
        contourArea(intersection) < energy_part_param_.CENTER_R_CONTOUR_INTERSETION_AREA_MIN) {
        return false;
    }
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为流动条扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidFlowStripFanContour(cv::Mat &src, const vector<cv::Point> &flow_strip_fan_contour) {
    double cur_contour_area = contourArea(flow_strip_fan_contour);
    if (cur_contour_area > energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MAX ||
        cur_contour_area < energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_MIN) {
        //cout<<cur_contour_area<<" "<<energy_fan_param_.CONTOUR_AREA_MIN<<" "<<energy_fan_param_.CONTOUR_AREA_MAX<<endl;
        //cout<<"area fail."<<endl;
        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(flow_strip_fan_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;//将矩形的长边设置为长
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;//将矩形的短边设置为宽
    if (length < energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MIN
        || width < energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MIN
        || length > energy_part_param_.FLOW_STRIP_FAN_CONTOUR_LENGTH_MAX
        || width > energy_part_param_.FLOW_STRIP_FAN_CONTOUR_WIDTH_MAX) {
        //cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }

    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.FLOW_STRIP_FAN_CONTOUR_HW_RATIO_MIN) {
        //cout<<"length width ratio fail."<<endl;
        return false;
        //长宽比不合适
    }
//    if (cur_contour_area / cur_size.area() < energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MIN
//    || cur_contour_area / cur_size.area() > energy_part_param_.FLOW_STRIP_FAN_CONTOUR_AREA_RATIO_MAX)
//        //    轮廓对矩形的面积占有率不合适
//        return false;
    double non_zero_rate = nonZeroRateOfRotateRect(src, cur_rect);
    if (non_zero_rate > energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MAX ||
        non_zero_rate < energy_part_param_.FLOW_STRIP_FAN_NON_ZERO_RATE_MIN)
        return false;
    //亮点占比不合格
    return true;
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为流动条
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidFlowStripContour(const vector<cv::Point> &flow_strip_contour) {
    double cur_contour_area = contourArea(flow_strip_contour);
    if (cur_contour_area > energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MAX ||
        cur_contour_area < energy_part_param_.FLOW_STRIP_CONTOUR_AREA_MIN) {
//        cout<<"area fail."<<endl;

        return false;
        //选区面积大小不合适
    }
    RotatedRect cur_rect = minAreaRect(flow_strip_contour);
    Size2f cur_size = cur_rect.size;
    float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;//将矩形的长边设置为长
    float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;//将矩形的短边设置为宽
    if (length < energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MIN ||
        width < energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MIN ||
        length > energy_part_param_.FLOW_STRIP_CONTOUR_LENGTH_MAX ||
        width > energy_part_param_.FLOW_STRIP_CONTOUR_WIDTH_MAX) {
//        cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }
    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.FLOW_STRIP_CONTOUR_HW_RATIO_MIN) {
//        cout<<"hw fail."<<endl;
        return false;
        //长宽比不合适
    }
    if (cur_contour_area / cur_size.area() < energy_part_param_.FLOW_STRIP_CONTOUR_AREA_RATIO_MIN)
        return false;//轮廓对矩形的面积占有率不合适
    std::vector<cv::Point2f> intersection;
    if (rotatedRectangleIntersection(cur_rect, flow_strip_fan, intersection) != 0) {
        if (contourArea(intersection) < energy_part_param_.FLOW_STRIP_CONTOUR_INTERSETION_AREA_MIN) {
            return false;
        }
    }
    return true;
}
