//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::getFanPosition(std::vector<float> &fanPosition, const std::vector<EnergyPart> &fans, cv::Point cycle_center, double radius) {
	if (radius == 0)return;
	for (const auto &fan : fans)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (fan.rect.center.y - cycle_center.y), (fan.rect.center.x - cycle_center.x)));
		fanPosition.push_back(angle);
	}
//	cout << "fanPosition.size() = " << fanPosition.size() << '\t' << endl;
}

void Energy::getArmorPosition(std::vector<float> &armorPosition, const std::vector<EnergyPart> &armors, cv::Point cycle_center, double radius) {
	if (radius == 0)return;
	for (const auto &armor : armors)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - cycle_center.y), (armor.rect.center.x - cycle_center.x)));
		armorPosition.push_back(angle);

	}
//	cout << "armorPosition.size() = " << armorPosition.size() << '\t' << endl;
}

void Energy::getFirstArmorCenters(vector<EnergyPart> &armors, std::vector<cv::Point> &first_armor_centers)
{
	for (const auto &armor : armors) {
		if (armors.size() < 2)first_armor_centers.push_back(armor.rect.center);
	}
}

void Energy::getAllArmorCenters()
{
	for (const auto &armor : armors) {
		all_armor_centers.push_back(armor.rect.center);
	}
}

void Energy::getPosition(cv::Point point, double &angle){
	if (radius == 0)return;
	angle = (180 / PI * atan2(-1 * (point.y - cycle_center.y), (point.x - cycle_center.x)));
}
