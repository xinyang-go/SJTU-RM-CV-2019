//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示图像中所有扇叶
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showFans(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    for (const auto &fan : fans) {
        Point2f vertices[4];      //定义矩形的4个顶点
        fan.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 2);
    }
    imshow(windows_name, image2show);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示图像中所有装甲板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showArmors(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    for (const auto &armor : armors) {
        Point2f vertices[4];      //定义矩形的4个顶点
        armor.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    }
    imshow(windows_name, image2show);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示图像中所有扇叶和装甲板,并框出待击打装甲板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showBoth(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;
    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    for (const auto &fan : fans) {
        Point2f vertices[4];      //定义矩形的4个顶点
        fan.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 4);
    }
    for (const auto &armor : armors) {
        Point2f vertices[4];      //定义矩形的4个顶点
        armor.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++) {
            if (pointDistance(static_cast<cv::Point2f>(armor.center), target_point) < 5)
                line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 255, 0), 4);
            else
                line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 4);
        }
        cv::Point2f point = armor.center;
        cv::circle(image2show, point, 2, cv::Scalar(0, 0, 255));//在图像中画出特征点，2是圆的半径

    }

    imshow(windows_name, image2show);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示图像中所有可能的风车中心候选区R
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showCenterR(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    //cvtColor(image2show, image2show, COLOR_GRAY2RGB);
    Point2f vertices[4];      //定义矩形的4个顶点
    centerR.points(vertices);   //计算矩形的4个顶点
    for (int i = 0; i < 4; i++)
        line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 255, 0), 2);

    cv::circle(image2show, circle_center_point, 4, cv::Scalar(0, 0, 255), 2);//在图像中画出特征点，2是圆的半径

    imshow(windows_name, image2show);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示图像中所有流动条
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showFlowStripFan(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }

    Point2f strip_fan_vertices[4];      //定义矩形的4个顶点
    flow_strip_fan.points(strip_fan_vertices);   //计算矩形的4个顶点for (int i = 0; i < 4; i++)
    for (int i = 0; i < 4; i++)
        line(image2show, strip_fan_vertices[i], strip_fan_vertices[(i + 1) % 4], Scalar(127, 127, 255), 2);


    Point2f strip_vertices[4];      //定义矩形的4个顶点
    flow_strip.points(strip_vertices);   //计算矩形的4个顶点
    for (int i = 0; i < 4; i++)
        line(image2show, strip_vertices[i], strip_vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);

    for (const auto &armor : armors) {
        if (pointDistance(armor.center, target_point) < energy_part_param_.TWIN_POINT_MAX) {
            Point2f vertices[4];      //定义矩形的4个顶点
            armor.points(vertices);   //计算矩形的4个顶点
            for (int i = 0; i < 4; i++)
                line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 255, 0), 2);
        }
    }

    Point2f ROI_vertices[4];      //定义矩形的4个顶点
    center_ROI.points(ROI_vertices);   //计算矩形的4个顶点
    for (int i = 0; i < 4; i++)
        line(image2show, ROI_vertices[i], ROI_vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
    cout<<"show strip!"<<endl;
    imshow(windows_name, image2show);
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于显示猜测的下一个目标点
// ---------------------------------------------------------------------------------------------------------------------
void Energy::showGuessTarget(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    cv::Point2f point = guess_point;
    cv::circle(image2show, point, 4, cv::Scalar(0, 0, 255));//在图像中画出特征点，2是圆的半径

    imshow(windows_name, image2show);
}


