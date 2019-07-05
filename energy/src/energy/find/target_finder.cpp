//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于匹配扇叶和装甲板，找到目标装甲板,计算其极坐标角度和中心坐标
// ---------------------------------------------------------------------------------------------------------------------
void Energy::findTarget() {
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
	int i, j = 0;
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

