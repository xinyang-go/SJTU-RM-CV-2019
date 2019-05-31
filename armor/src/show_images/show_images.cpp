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
    for(int i=0; i<10; i++){
        if(!boxes[i].empty()){
            for(auto box : boxes[i]){
                char buff[2] = {0};
                buff[0] = i + '0';
                rectangle(image2show, box, Scalar(0, 255, 0), 1);
                putText(image2show, buff, Point(box.x+2, box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(255,0,0));
            }
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
        if(light_blob.BlobColor == BLOB_RED)
            rectangle(image2show, light_blob.rect.boundingRect(), Scalar(0,0,255), 3);
        if(light_blob.BlobColor == BLOB_BLUE)
            rectangle(image2show, light_blob.rect.boundingRect(), Scalar(255,0,0), 3);

    }
    imshow(windows_name, image2show);
}

