//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;




//----------------------------------------------------------------------------------------------------------------------
// 此函数通过最小二乘法计算大风车圆心和半径
// ---------------------------------------------------------------------------------------------------------------------
void Energy::circleLeastFit()
{
    circle_center_point.x = 0;
    circle_center_point.y = 0;
    radius = 0.0f;
    if (all_target_armor_centers.size() < 3)
    {
//        cout<<"Cannot calculate a circle"<<endl;
        return;
    }
    double sum_x = 0.0f, sum_y = 0.0f;
    double sum_x2 = 0.0f, sum_y2 = 0.0f;
    double sum_x3 = 0.0f, sum_y3 = 0.0f;
    double sum_xy = 0.0f, sum_x1y2 = 0.0f, sum_x2y1 = 0.0f;
    int N = static_cast<int>(all_target_armor_centers.size());
    for (int i = 0; i < N; i++)
    {
        double x = all_target_armor_centers.at(i).x;
        double y = all_target_armor_centers.at(i).y;
        double x2 = x * x;
        double y2 = y * y;
        sum_x += x;
        sum_y += y;
        sum_x2 += x2;
        sum_y2 += y2;
        sum_x3 += x2 * x;
        sum_y3 += y2 * y;
        sum_xy += x * y;
        sum_x1y2 += x * y2;
        sum_x2y1 += x2 * y;
    }
    double C, D, E, G, H;
    double a, b, c;
    C = N * sum_x2 - sum_x * sum_x;
    D = N * sum_xy - sum_x * sum_y;
    E = N * sum_x3 + N * sum_x1y2 - (sum_x2 + sum_y2) * sum_x;
    G = N * sum_y2 - sum_y * sum_y;
    H = N * sum_x2y1 + N * sum_y3 - (sum_x2 + sum_y2) * sum_y;
    a = (H * D - E * G) / (C * G - D * D);
    b = (H * C - E * D) / (D * D - G * C);
    c = -(a * sum_x + b * sum_y + sum_x2 + sum_y2) / N;
    circle_center_point.x = static_cast<int>(a / (-2));
    circle_center_point.y = static_cast<int>(b / (-2));
    radius = sqrt(a * a + b * b - 4 * c) / 2;
//    cout << "The cycle center is: " << cycle_center << endl;
//    cout << "The radius is: " << radius << endl;
}
