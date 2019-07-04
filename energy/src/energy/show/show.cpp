//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::showFanContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &fans) {
	if (src.empty())return;
    static Mat image2show;

    if(src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
	//cvtColor(image2show, image2show, COLOR_GRAY2RGB);
	for (const auto &fan : fans)
	{
		Point2f vertices[4];      //定义矩形的4个顶点
		fan.rect.points(vertices);   //计算矩形的4个顶点
		for (int i = 0; i < 4; i++)
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 2);
		//cout << fan.rect.center << '\t' << fan.rect.angle << '\t';
		//cout << endl;
	}
	imshow(windows_name, image2show);
}

void Energy::showArmorContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &armors) {
	if (src.empty())return;
    static Mat image2show;

    if(src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
	//cvtColor(image2show, image2show, COLOR_GRAY2RGB);
	for (const auto &armor : armors)
	{
		Point2f vertices[4];      //定义矩形的4个顶点
		armor.rect.points(vertices);   //计算矩形的4个顶点
		for (int i = 0; i < 4; i++)
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
		//cout << armor.rect.center << '\t' << armor.rect.angle << '\t';
		//cout << endl;
	}
	imshow(windows_name, image2show);
}

void Energy::showCenterRContours(std::string windows_name, const cv::Mat src) {
    if (src.empty())return;
    static Mat image2show;

    if(src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    //cvtColor(image2show, image2show, COLOR_GRAY2RGB);
    for (const auto &center_R : centerRs)
    {
        Point2f vertices[4];      //定义矩形的4个顶点
        center_R.rect.points(vertices);   //计算矩形的4个顶点
        for (int i = 0; i < 4; i++)
            line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 255), 2);
        //cout << armor.rect.center << '\t' << armor.rect.angle << '\t';
        //cout << endl;
    }
    imshow(windows_name, image2show);
}

void Energy::showBothContours(std::string windows_name, const cv::Mat &src, const std::vector<EnergyPart> &fans,
	const std::vector<EnergyPart> &armors) {
	if (src.empty())return;
	static Mat image2show;
    if(src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);

    } else if (src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
	//cvtColor(image2show, image2show, COLOR_GRAY2RGB);
	for (const auto &fan : fans)
	{
		Point2f vertices[4];      //定义矩形的4个顶点
		fan.rect.points(vertices);   //计算矩形的4个顶点
		for (int i = 0; i < 4; i++)
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(255, 0, 0), 4);
//		cout << "fan" << fan.rect.size.height <<'\t'<< fan.rect.size.width << '\t' << '\t';
//		cout << endl;
	}
	for (const auto &armor : armors)
	{
		Point2f vertices[4];      //定义矩形的4个顶点
		armor.rect.points(vertices);   //计算矩形的4个顶点
		for (int i = 0; i < 4; i++)
			line(image2show, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 4);
//		cout << "armor center: "<< armor.rect.center << '\t'<< "armor angle: "<< armor.rect.angle;
//		cout << endl;

        cv::Point2f point = armor.rect.center;
        cv::circle(image2show, point, 2, cv::Scalar(0, 0, 255));//在图像中画出特征点，2是圆的半径

	}

    imshow(windows_name, image2show);
}


