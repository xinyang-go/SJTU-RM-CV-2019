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
int Energy::findFan(const cv::Mat src, int &last_fans_cnt) {
    if (src.empty())return 0;
    static Mat src_bin;
    src_bin = src.clone();
//    threshold(src, src_bin, energy_part_param_.FAN_GRAY_THRESH, 255, THRESH_BINARY);
    if(src.type() == CV_8UC3){
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
	std::vector<vector<Point> > fan_contours;
	StructingElementClose(src_bin,6,6);//图像膨胀，防止图像断开并更方便寻找
//	imshow("fan struct",src_bin);
	findContours(src_bin, fan_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (auto &fan_contour : fan_contours) {
		if (!isValidFanContour(fan_contour)) {
			continue;
		}
        fans.emplace_back(fan_contour);

//        RotatedRect cur_rect = minAreaRect(fan_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if(length>20&&width>20){
//			cout<<cur_rect.center;
//			fans.emplace_back(fan_contour);
//			cout<<"fan area: "<<length<<'\t'<<width<<endl;
//		}
	}
	if(fans.size() < last_fans_cnt){
		last_fans_cnt = static_cast<int>(fans.size());
		return -1;//寻找到的扇叶比上一帧少，说明该帧有误，返回-1
	}
	last_fans_cnt = static_cast<int>(fans.size());
	return static_cast<int>(fans.size());
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内所有的大风车装甲板模块
// ---------------------------------------------------------------------------------------------------------------------
int Energy::findArmor(const cv::Mat src, int &last_armors_cnt) {
	if (src.empty())return 0;
    static Mat src_bin;
    src_bin = src.clone();
//    threshold(src, src_bin, energy_part_param_.ARMOR_GRAY_THRESH, 255, THRESH_BINARY);
    if(src.type() == CV_8UC3){
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);//若读取三通道视频文件，需转换为单通道
    }
	std::vector<vector<Point> > armor_contours;
    std::vector<vector<Point> > armor_contours_external;//用总轮廓减去外轮廓，只保留内轮廓，除去流动条的影响。

    StructingElementErodeDilate(src_bin);//图像膨胀，防止图像断开并更方便寻找
//    imshow("armor struct",src_bin);

	findContours(src_bin, armor_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    findContours(src_bin, armor_contours_external, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (int i = 0; i < armor_contours_external.size(); i++)//去除外轮廓
    {
        unsigned long external_contour_size = armor_contours_external[i].size();
        for (int j = 0; j < armor_contours.size(); j++)
        {
            unsigned long all_size = armor_contours[j].size();
            if (external_contour_size == all_size)
            {
                swap(armor_contours[j], armor_contours[armor_contours.size() - 1]);
                armor_contours.pop_back();
                break;
            }
        }
    }
    for (auto &armor_contour : armor_contours) {
		if (!isValidArmorContour(armor_contour))
		{
			continue;
		}
        armors.emplace_back(armor_contour);

//        RotatedRect cur_rect = minAreaRect(armor_contour);
//        Size2f cur_size = cur_rect.size;
//        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
//        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;
//        if(length>10&&width>5){
//            armors.emplace_back(armor_contour);
//            cout<<"armor area: "<<length<<'\t'<<width<<'\t'<<cur_rect.center<<endl;
//        }

	}
	if(armors.size() < last_armors_cnt){
		last_armors_cnt = static_cast<int>(armors.size());
		return -1;//寻找到的装甲板比上一帧少，说明该帧有误，返回-1
	}
	last_armors_cnt = static_cast<int>(armors.size());
	return static_cast<int>(armors.size());
}





//----------------------------------------------------------------------------------------------------------------------
// 此函数用于寻找图像内大风车中心字母“R”
// ---------------------------------------------------------------------------------------------------------------------
int Energy::findCenterR(const cv::Mat src) {
    if (src.empty())return 0;
    static Mat src_bin;
    src_bin = src.clone();
//    threshold(src, src_bin, energy_part_param_.ARMOR_GRAY_THRESH, 255, THRESH_BINARY);
    if(src.type() == CV_8UC3){
        cvtColor(src_bin, src_bin, CV_BGR2GRAY);
    }
    std::vector<vector<Point> > center_R_contours;
    StructingElementErodeDilate(src_bin);
//    imshow("R struct",src_bin);
    findContours(src_bin, center_R_contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (auto &center_R_contour : center_R_contours) {
        if (!isValidCenterRContour(center_R_contour))
        {
            continue;
        }
        centerRs.emplace_back(center_R_contour);

        /*RotatedRect cur_rect = minAreaRect(center_R_contour);
        Size2f cur_size = cur_rect.size;
        float length = cur_size.height > cur_size.width ? cur_size.height : cur_size.width;
        float width = cur_size.height < cur_size.width ? cur_size.height : cur_size.width;

        if(length>10 && width>5){
            centerRs.emplace_back(center_R_contour);
            cout<<"center R area: "<<length<<'\t'<<width<<'\t'<<cur_rect.center<<endl;
        }
        cout<<"armor area: "<<length<<'\t'<<width<<endl;*/
    }
    if(centerRs.size() == 0) return -1;//未找到合适的中心候选区，说明该帧有误，返回-1
    return static_cast<int>(centerRs.size());
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为扇叶
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidFanContour(const vector<cv::Point> fan_contour) {
	double cur_contour_area = contourArea(fan_contour);
	if (cur_contour_area > energy_part_param_.FAN_CONTOUR_AREA_MAX ||
		cur_contour_area < energy_part_param_.FAN_CONTOUR_AREA_MIN)
	{
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
            length > energy_part_param_.FAN_CONTOUR_LENGTH_MAX || width > energy_part_param_.FAN_CONTOUR_WIDTH_MAX)
	{
		//cout<<"length width fail."<<endl;
		return false;
		//矩形边长不合适
	}
	float length_width_ratio = length / width;//计算矩形长宽比
	if (length_width_ratio > energy_part_param_.FAN_CONTOUR_HW_RATIO_MAX ||
		length_width_ratio < energy_part_param_.FAN_CONTOUR_HW_RATIO_MIN)
	{
		//cout<<"length width ratio fail."<<endl;
		return false;
		//长宽比不合适
	}
	if (cur_contour_area / cur_size.area() < 0.6) return false;//轮廓对矩形的面积占有率不合适
	return true;
}





//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为装甲板
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidArmorContour(const vector<cv::Point> armor_contour) {
	double cur_contour_area = contourArea(armor_contour);
	if (cur_contour_area > energy_part_param_.ARMOR_CONTOUR_AREA_MAX ||
		cur_contour_area < energy_part_param_.ARMOR_CONTOUR_AREA_MIN)
	{
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
            length > energy_part_param_.ARMOR_CONTOUR_LENGTH_MAX||width>energy_part_param_.ARMOR_CONTOUR_WIDTH_MAX)
	{
		//cout<<"length width fail."<<endl;
		return false;
        //矩形边长不合适
	}

	float length_width_ratio = length / width;//计算矩形长宽比
	if (length_width_ratio > energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MAX ||
		length_width_ratio < energy_part_param_.ARMOR_CONTOUR_HW_RATIO_MIN)
	{
		//cout<<"length width ratio fail."<<endl;
		return false;
        //长宽比不合适
	}
	if (cur_contour_area / cur_size.area() < 0.7) return false;//轮廓对矩形的面积占有率不合适
	return true;
}





//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断找到的矩形候选区是否为可能的风车中心R候选区
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::isValidCenterRContour(const vector<cv::Point> center_R_contour) {
    double cur_contour_area = contourArea(center_R_contour);
	if (cur_contour_area > energy_part_param_.ARMOR_CONTOUR_AREA_MAX ||
		cur_contour_area < energy_part_param_.ARMOR_CONTOUR_AREA_MIN)
	{
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
        ||length > energy_part_param_.CENTER_R_CONTOUR_LENGTH_MAX ||width>energy_part_param_.CENTER_R_CONTOUR_WIDTH_MAX)
    {
        //cout<<"length width fail."<<endl;
        return false;
        //矩形边长不合适
    }
    float length_width_ratio = length / width;//计算矩形长宽比
    if (length_width_ratio > energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MAX ||
        length_width_ratio < energy_part_param_.CENTER_R_CONTOUR_HW_RATIO_MIN)
    {
        //cout<<"length width ratio fail."<<endl;
        return false;
        //长宽比不合适
    }
    if (cur_contour_area / cur_size.area() < 0.7) return false;//轮廓对矩形的面积占有率不合适
    return true;
}