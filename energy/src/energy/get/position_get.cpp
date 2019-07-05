//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于获得图像中所有扇叶的当前极坐标角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getFanPosition() {
	if (radius == 0)return;
	for (const auto &fan : fans)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (fan.rect.center.y - circle_center_point.y),
		        (fan.rect.center.x - circle_center_point.x)));
		fan_polar_angle.push_back(angle);
	}
//	cout << "fanPosition.size() = " << fanPosition.size() << '\t' << endl;
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于获得图像中所有装甲板的当前极坐标角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getArmorPosition() {
	if (radius == 0)return;
	for (const auto &armor : armors)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - circle_center_point.y),
		        (armor.rect.center.x - circle_center_point.x)));
		armor_polar_angle.push_back(angle);

	}
//	cout << "armorPosition.size() = " << armorPosition.size() << '\t' << endl;
}




//----------------------------------------------------------------------------------------------------------------------
// 此函数用于存储图像中所有装甲板的中心坐标，以便后续最小二乘法计算圆心和半径
// ---------------------------------------------------------------------------------------------------------------------
void Energy::getAllArmorCenters()
{
	for (const auto &armor : armors) {
		all_armor_centers.push_back(armor.rect.center);
	}
}