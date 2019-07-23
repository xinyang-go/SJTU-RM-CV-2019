//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;



//----------------------------------------------------------------------------------------------------------------------
// 此函数根据矩形重合面积匹配扇叶与装甲板
// ---------------------------------------------------------------------------------------------------------------------
void Energy::findTargetByIntersection() {
    if (fans.size() >= armors.size()) return;//扇叶多于装甲板，识别错误
    for (const auto &fan : fans) {
        for (const auto &armor : armors) {

        }
    }
   /* if (fans.empty()) {
        target_point = armors.at(0).rect.center;
        return;
    }
    int i = 0, j = 0;
    while (i < armors.size()) {
        for (j = 0; j < fans.size(); ++j) {
            std::vector<cv::Point2f> intersection;
            if (rotatedRectangleIntersection(armors.at(i).rect, fans.at(j).rect, intersection) == 0)//返回0表示没有重合面积
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
        if (j == fans.size()) {
            target_point = armors.at(i).rect.center;
            break;
        }
        i++;
    }*/
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数在流动条区域内寻找装甲板
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findTargetInFlowStripFan() {
    int i = 0;
    for (i = 0; i < armors.size(); ++i) {
        std::vector<cv::Point2f> intersection;
        if (rotatedRectangleIntersection(armors.at(i), flow_strip_fan, intersection) == 0)
            continue;//返回0表示没有重合面积
        double cur_contour_area = contourArea(intersection);
//        cout<<cur_contour_area<<endl;
        if (cur_contour_area < energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN)
            continue;
        else {
            target_armor = armors.at(i);
            target_point = armors.at(i).center;
            return true;
        }
    }
    cout<<"find target false"<<endl;
//    cout<<armors.size()<<'\t'<<armors.at(0).size<<endl;
    return false;
}