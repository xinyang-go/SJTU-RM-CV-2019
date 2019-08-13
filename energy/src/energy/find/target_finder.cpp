//
// Created by xixiliadorabarry on 1/24/19.
//

#include "energy/energy.h"
#include "log.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;




//----------------------------------------------------------------------------------------------------------------------
// 此函数在流动条区域内寻找装甲板
// ---------------------------------------------------------------------------------------------------------------------
bool Energy::findTargetInFlowStripFan() {
//    Mat draw(480,640,CV_8UC3,Scalar(0,0,0));
    for (auto &candidate_flow_strip_fan: flow_strip_fans) {
//        Point2f vertices[4];      //定义矩形的4个顶点
//        candidate_flow_strip_fan.points(vertices);   //计算矩形的4个顶点
//        for (int i = 0; i < 4; i++)
//            line(draw, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 2);
        int i = 0;
        for (i = 0; i < armors.size(); ++i) {
            std::vector<cv::Point2f> intersection;
            if (rotatedRectangleIntersection(armors.at(i), candidate_flow_strip_fan, intersection) == 0)
                continue;//返回0表示没有重合面积
            double cur_contour_area = contourArea(intersection);
//        cout<<cur_contour_area<<endl;
            if (cur_contour_area > energy_part_param_.TARGET_INTERSETION_CONTOUR_AREA_MIN) {
                target_armors.emplace_back(armors.at(i));
            }
        }
    }
//    imshow("draw",draw);
//    waitKey();
//    cout << "target armor cnt: " << target_armors.size() << endl;
    if (target_armors.empty()) {
        if (show_info)cout << "find target armor false" << endl;
        return false;
    } else {
        return true;
    }


}