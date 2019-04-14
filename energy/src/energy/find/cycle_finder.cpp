//
// Created by xixiliadorabarry on 19-3-23.
//

#include "energy/energy.h"
#include <iostream>

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::findWholeCycle(const std::vector<cv::Point>&first_armor_centers) {
    int cur_size = static_cast<int>(first_armor_centers.size());
    //cout << "first armor centers' size: " << first_armor_centers.size() << endl;
    if (cur_size == 0)return;
    int vertex = 0;
    for (int i = 1; i < cur_size - 1; ++i)
    {
        if (vertex == 4)break;
        if (first_armor_centers.at(i).x >= first_armor_centers.at(i - 1).x && first_armor_centers.at(i).x >= first_armor_centers.at(i + 1).x)
        {
            if (isRightVertexFound == -1) {
                vertex += 1;
                isRightVertexFound = 1;
                right = first_armor_centers.at(i);
                cout << "right vertex: " << right << endl;
                continue;
            }
            else if (right.x > first_armor_centers.at(i).x)continue;
            else {
                right = first_armor_centers.at(i);
                continue;
            }
        }
        if (first_armor_centers.at(i).x <= first_armor_centers.at(i - 1).x && first_armor_centers.at(i).x <= first_armor_centers.at(i + 1).x)
        {
            if (isLeftVertexFound == -1) {
                vertex += 1;
                isLeftVertexFound = 1;
                left = first_armor_centers.at(i);
                cout << "left vertex: " << left << endl;
                continue;
            }
            else if (left.x < first_armor_centers.at(i).x)continue;
            else {
                left = first_armor_centers.at(i);
                continue;
            }
        }
        if (first_armor_centers.at(i).y <= first_armor_centers.at(i - 1).y && first_armor_centers.at(i).y <= first_armor_centers.at(i + 1).y)
        {
            if (isTopVertexFound == -1) {
                vertex += 1;
                isTopVertexFound = 1;
                top = first_armor_centers.at(i);
                cout << "top vertex: " << top << endl;
                continue;
            }
            else if (top.y < first_armor_centers.at(i).y)continue;
            else {
                top = first_armor_centers.at(i);
                continue;
            }

        }
        if (first_armor_centers.at(i).y >= first_armor_centers.at(i - 1).y && first_armor_centers.at(i).y >= first_armor_centers.at(i + 1).y)
        {
            if (isBottomVertexFound == -1) {
                vertex += 1;
                isBottomVertexFound = 1;
                bottom = first_armor_centers.at(i);
                cout << "bottom vertex: " << bottom << endl;
                continue;
            }
            else if (bottom.y > first_armor_centers.at(i).y)continue;
            else {
                bottom = first_armor_centers.at(i);
                continue;
            }
        }
    }

    /*for (int k = 0; k < first_armor_centers.size(); ++k) {
        cout << k << " : " << first_armor_centers.at(k) << '\t';
        float angle = static_cast<float>(180 / PI * atan2(-1 * (first_armor_centers.at(k).y - 298), (first_armor_centers.at(k).x - 298)));
        cout << angle << endl;
    }*/
}
