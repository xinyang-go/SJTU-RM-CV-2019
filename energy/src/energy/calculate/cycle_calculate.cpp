//
// Created by xixiliadorabarry on 1/24/19.
//
#include "energy/energy.h"

using namespace cv;
using std::cout;
using std::endl;
using std::vector;

void Energy::cycleQuickCalculate(std::vector<cv::Point> &first_armor_centers, cv::Point &cycle_center, double &radius) {
    //if (isCalibrated()) return;

	int cur_size = static_cast<int>(first_armor_centers.size());
	if (cur_size < 3)return;
	cv::Point point_1, point_2, point_3;
	point_1 = first_armor_centers.at(0);
	point_2 = first_armor_centers.at(static_cast<unsigned long>(cur_size - 1));
	point_3 = first_armor_centers.at(static_cast<unsigned long>(cur_size / 2));
	//cout << point_1 << '\t' << point_2 << endl;
	//cout << first_armor_centers.at(point_1) << '\t' << first_armor_centers.at(point_2) << endl;
	cycle(point_1, point_2, point_3, cycle_center, radius);
	cout << "The cycle center is: " << cycle_center << endl;
	cout << "The radius is: " << radius << endl;
}

void Energy::cycleDefaultCalculateConst(cv::Point &cycle_center, double &radius) {
	if (count >= 5)
		return;
	clock_t end;
	double time_duration = 1.0, dt;
	if (Armor_center.size() < 3) {
		end = clock();
		dt = (end - start) / 1000000.00;
		if (dt >= time_duration * count) {
			getFirstArmorCenters(armors, Armor_center);
			count++;
		}
	}
	else {
		cycleQuickCalculate(Armor_center, cycle_center, radius);
		count++;
	}
}

void Energy::cycleCalculate(){
	cycle_center.x = (top.x + bottom.x)/2;
	cycle_center.y = (left.y + right.y)/2;
	radius = (right.x - left.x)/2;
	cout << "The cycle center is: " << cycle_center << endl;
	cout << "The radius is: " << radius << endl;
}

void Energy::cycleLeastFit()
{
    cycle_center.x = 0;
    cycle_center.y = 0;
    radius = 0.0f;
    if (all_armor_centers.size() < 3)
    {
//        cout<<"Cannot calculate a circle"<<endl;
        return;
    }

    double sum_x = 0.0f, sum_y = 0.0f;
    double sum_x2 = 0.0f, sum_y2 = 0.0f;
    double sum_x3 = 0.0f, sum_y3 = 0.0f;
    double sum_xy = 0.0f, sum_x1y2 = 0.0f, sum_x2y1 = 0.0f;

    int N = static_cast<int>(all_armor_centers.size());
    for (int i = 0; i < N; i++)
    {
        double x = all_armor_centers.at(i).x;
        double y = all_armor_centers.at(i).y;
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

    cycle_center.x = static_cast<int>(a / (-2));
    cycle_center.y = static_cast<int>(b / (-2));
    radius = sqrt(a * a + b * b - 4 * c) / 2;

//    cout << "The cycle center is: " << cycle_center << endl;
//    cout << "The radius is: " << radius << endl;
}
