#include <show_images/show_images.h>

using namespace cv;

void showArmorBoxVector(std::string windows_name, const cv::Mat &src, const std::vector<cv::Rect2d> &armor_box) {
    static Mat image2show;
    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if(src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }

    for (auto &box:armor_box) {
        rectangle(image2show, box, Scalar(0, 255, 0), 1);
    }
    imshow(windows_name, image2show);
}

void showArmorBoxClass(std::string window_names, const cv::Mat &src, vector<cv::Rect2d> boxes[10]){
    static Mat image2show;
    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if(src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    if(!boxes[0].empty()){
        for(auto box : boxes[0]){
            cv::rectangle(image2show, box, Scalar(255, 0, 0), 1);
        }
    }else if(!boxes[1].empty()){
        for(auto box : boxes[1]){
            cv::rectangle(image2show, box, Scalar(0, 255, 0), 1);
        }
    }else if(!boxes[2].empty()){
        for(auto box : boxes[2]){
            cv::rectangle(image2show, box, Scalar(0, 0, 255), 1);
        }
    }else if(!boxes[3].empty()){
        for(auto box : boxes[3]){
            cv::rectangle(image2show, box, Scalar(0, 255, 255), 1);
        }
    }else if(!boxes[4].empty()){
        for(auto box : boxes[4]){
            cv::rectangle(image2show, box, Scalar(255, 0, 255), 1);
        }
    }else if(!boxes[5].empty()){
        for(auto box : boxes[5]){
            cv::rectangle(image2show, box, Scalar(255, 255, 0), 1);
        }
    }
    imshow(window_names, image2show);
}

void showArmorBox(std::string windows_name, const cv::Mat &src, cv::Rect2d armor_box) {
    static Mat image2show;
    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if(src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    rectangle(image2show, armor_box, Scalar(0, 255, 0), 1);
    imshow(windows_name, image2show);
}

void showContours(std::string windows_name, const cv::Mat &src, const std::vector<LightBlob> &light_blobs) {
    static Mat image2show;

    if(src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    }
    else if(src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }

    for(const auto &light_blob:light_blobs)
    {
        rectangle(image2show, light_blob.rect.boundingRect(), Scalar(255,0,0), 3);
    }
    imshow(windows_name, image2show);
}

