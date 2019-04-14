//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::findTarget(std::vector<float>fanPosition, std::vector<float>armorPosition, float &target_armor) {
	if (fanPosition.size() >= armorPosition.size()) return;
	if (armorPosition.size()==0)return;
	if (fanPosition.size() == 0) {
		target_armor = armorPosition.at(0);
		for (const auto &armor : armors)
		{
			target_center = armor.rect.center;
//			cout<<"target center: "<<target_center<<endl;
		}
		return;
	}
	sort(fanPosition.begin(), fanPosition.end());
	/*for (vector<float>::iterator it = fanPosition.begin(); it != fanPosition.end(); it++) {
		cout << *it << endl;
	}*/
	sort(armorPosition.begin(), armorPosition.end());
	/*for (vector<float>::iterator it = armorPosition.begin(); it != armorPosition.end(); it++) {
		cout << *it << endl;
	}*/
	int i, j = 0;
	for (i = 0; i < fanPosition.size(); ++i) {
		if (armorPosition.at(i) - fanPosition.at(j) < energy_part_param_.TWIN_ANGEL_MAX && armorPosition.at(i) - fanPosition.at(j) > -1 * energy_part_param_.TWIN_ANGEL_MAX) {
			j++;
			continue;
		}
		else {
			target_armor = armorPosition.at(j);
			for (const auto &armor : armors)
			{
				float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - cycle_center.y), (armor.rect.center.x - cycle_center.x)));
				if(target_armor==angle){
					target_center = armor.rect.center;
//					cout<<"target center: "<<target_center<<endl;
				}
			}
			return;
		}
	}
	target_armor = armorPosition.at(armorPosition.size() - 1);
	for (const auto &armor : armors)
	{
		float angle = static_cast<float>(180 / PI * atan2(-1 * (armor.rect.center.y - cycle_center.y), (armor.rect.center.x - cycle_center.x)));
		if(target_armor == angle){
			target_center = armor.rect.center;
//			cout<<"target center: "<<target_center<<endl;
		}
	}

}

