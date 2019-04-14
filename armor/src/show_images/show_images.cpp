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

