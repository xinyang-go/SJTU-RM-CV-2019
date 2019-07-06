//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数通过极坐标角度匹配扇叶和装甲板，找到目标装甲板,计算其极坐标角度和中心坐标
// ---------------------------------------------------------------------------------------------------------------------
void Energy::findTargetByPolar() {
	if (fan_polar_angle.size() >= armor_polar_angle.size()) return;//扇叶多于装甲板，识别错误
	if (armor_polar_angle.empty())return;//找不到扇叶，识别错误
	if (fan_polar_angle.empty()) {
        target_polar_angle = armor_polar_angle.at(0);//视野中没有扇叶，说明在击打第一个装甲板
		for (const auto &armor : armors)
		{
			target_point = armor.rect.center;
		}
		return;
	}
	sort(fan_polar_angle.begin(), fan_polar_angle.end());//对扇叶的极坐标角度进行排序
	sort(armor_polar_angle.begin(), armor_polar_angle.end());//对装甲板的极坐标角度进行排序
	int i = 0, j = 0;
	for (i = 0; i < fan_polar_angle.size(); ++i) {
		if (armor_polar_angle.at(i) - fan_polar_angle.at(j) < energy_part_param_.TWIN_ANGEL_MAX
		    && armor_polar_angle.at(i) - fan_polar_angle.at(j) > -1 * energy_part_param_.TWIN_ANGEL_MAX) {
			j++;
			continue;//若第i个扇叶的极坐标角度与第j个装甲板的极坐标角度接近，则两者匹配成功，i与j都加1
		}
		else {
            target_polar_angle = armor_polar_angle.at(j);//无法被匹配到的装甲板为待击打装甲板
			for (const auto &armor : armors)
			{
				float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - circle_center_point.y),
				        (armor.rect.center.x - circle_center_point.x)));
				if(target_polar_angle == angle){
					target_point = armor.rect.center;//根据已经确定的目标装甲板极坐标角度，获得该装甲板的中心坐标
				}
			}
			return;
		}
	}
    target_polar_angle = armor_polar_angle.at(armor_polar_angle.size() - 1);//前几个扇叶都匹配到装甲板，则最后剩下的装甲板为目标
	for (const auto &armor : armors)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - circle_center_point.y),
		        (armor.rect.center.x - circle_center_point.x)));
		if(target_polar_angle == angle){
			target_point = armor.rect.center;//根据已经确定的目标装甲板极坐标角度，获得该装甲板的中心坐标
		}
	}
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数根据矩形重合面积匹配扇叶与装甲板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::findTargetByIntersection() {
    if (fans.size() >= armors.size()) return;//扇叶多于装甲板，识别错误
    if (armors.empty())return;//找不到扇叶，识别错误
    if (fans.empty()) {
        target_point = armors.at(0).rect.center;
        return;
    }
    int i = 0, j = 0;
    while (i < armors.size()) {
        for (j = 0; j < fans.size(); ++j) {
            std::vector<cv::Point2f> intersection;
            if(rotatedRectangleIntersection(armors.at(i).rect, fans.at(j).rect, intersection) == 0)//返回0表示没有重合面积
                continue;
            else
                rotatedRectangleIntersection(armors.at(i).rect, fans.at(j).rect, intersection);
                double cur_contour_area = contourArea(intersection);
                if (cur_contour_area > energy_part_param_.INTERSETION_CONTOUR_AREA_MIN) {
//                    cout << endl;
//                    cout << "NO. " << i << " armor and No. " << j << "fans are matched, the intersection area is"
//                         << cur_contour_area << endl;
                    break;
                }
        }
        if(j == fans.size()){
            target_point = armors.at(i).rect.center;
            break;
        }
        i++;
    }
}