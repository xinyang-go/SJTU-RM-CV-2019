//
// Created by sun on 19-7-11.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于清空各vector
// ---------------------------------------------------------------------------------------------------------------------
void Energy::clearAll(){
    fans.clear();
    armors.clear();
}



//----------------------------------------------------------------------------------------------------------------------
// 此函数用于图像预处理
// ---------------------------------------------------------------------------------------------------------------------
void Energy::initImage(cv::Mat &src){
    imagePreprocess(src);
    if(show_process)imshow("img_preprocess", src);
    if (src.type() == CV_8UC3)cvtColor(src, src, COLOR_BGR2GRAY);
    threshold(src, src, energy_part_param_.GRAY_THRESH, 255, THRESH_BINARY);
    if (show_process)imshow("bin", src);
}
