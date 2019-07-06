#include <show_images/show_images.h>
#include <log.h>

using namespace cv;

std::map<int, string> id2name = {
        {-1, "NO"},
        { 0, "B1"},
        { 1, "B2"},
        { 2, "B3"},
        { 3, "B4"},
        { 4, "B5"},
        { 5, "B7"},
        { 6, "B8"},
        { 7, "R1"},
        { 8, "R2"},
        { 9, "R3"},
        {10, "R4"},
        {11, "R5"},
        {12, "R7"},
        {13, "R8"},
};

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
    for(int i=0; i<14; i++){
        if(!boxes[i].empty()){
            for(auto box : boxes[i]){
                rectangle(image2show, box, Scalar(0, 255, 0), 1);
                if(i == -1)
                    putText(image2show, id2name[i], Point(box.x+2, box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(0,255,0));
                else if(0<=i && i<7)
                    putText(image2show, id2name[i], Point(box.x+2, box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(255,0,0));
                else if(7<=i && i<14)
                    putText(image2show, id2name[i], Point(box.x+2, box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,255));
                else
                    LOGE_INFO("Invalid box id:%d!", i);
            }
        }
    }
    imshow(window_names, image2show);
}

void showArmorBox(std::string windows_name, const cv::Mat &src, cv::Rect2d armor_box, int boxid) {
    static Mat image2show;
    if (src.type() == CV_8UC1) // 黑白图像
    {
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if(src.type() == CV_8UC3) //RGB 彩色
    {
        image2show = src.clone();
    }
    rectangle(image2show, armor_box, Scalar(0, 255, 0), 1);
    if(boxid == -1)
        putText(image2show, id2name[boxid], Point(armor_box.x+2, armor_box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(0,255,0));
    else if(0<=boxid && boxid<7)
        putText(image2show, id2name[boxid], Point(armor_box.x+2, armor_box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(255,0,0));
    else if(7<=boxid && boxid<14)
        putText(image2show, id2name[boxid], Point(armor_box.x+2, armor_box.y+2), cv::FONT_HERSHEY_TRIPLEX, 1, Scalar(0,0,255));
    else
        LOGE_INFO("Invalid box id:%d!", boxid);
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
        Scalar color;
        if(light_blob.BlobColor == BLOB_RED)
            color = Scalar(0,0,255);
        else if(light_blob.BlobColor == BLOB_BLUE)
            color = Scalar(255,0,0);
        else
            color = Scalar(0,255,0);
        cv::Point2f vertices[4];
        light_blob.rect.points(vertices);
        for (int j = 0; j < 4; j++){
            cv::line(image2show, vertices[j], vertices[(j + 1) % 4], color, 2);
        }
    }
    imshow(windows_name, image2show);
}

void drawCuoWeiDu(cv::Mat &src, const LightBlob &light_blob_i, const LightBlob &light_blob_j){
    float angle_i = light_blob_i.rect.size.width > light_blob_i.rect.size.height ? light_blob_i.rect.angle:
                    light_blob_i.rect.angle - 90;
    float angle_j = light_blob_j.rect.size.width > light_blob_j.rect.size.height ? light_blob_j.rect.angle:
                    light_blob_j.rect.angle - 90;
    float angle = (angle_i+angle_j)/2.0/180.0*3.14159265459;
    if(abs(angle_i-angle_j)>90){
        angle += 3.14159265459/2;
    }
    Point2f orientation(cos(angle), sin(angle));
    Vector2f p2p(light_blob_j.rect.center.x-light_blob_i.rect.center.x, light_blob_i.rect.center.y-light_blob_j.rect.center.y);
    cv::line(
            src,
            (light_blob_j.rect.center+light_blob_i.rect.center)/2.0,
            (light_blob_j.rect.center+light_blob_i.rect.center)/2.0 + 100*orientation,
            Scalar(0,255,0),
            2
    );
}

void showCuoWeiDu(const cv::Mat &src, const std::vector<LightBlob> &light_blobs){
    Mat image2show = src.clone();
    for (int i = 0; i < light_blobs.size() - 1; ++i) {
        for (int j = i + 1; j < light_blobs.size(); ++j) {
            drawCuoWeiDu(image2show, light_blobs[i], light_blobs[j]);
        }
    }
    imshow("CuoWeiDu", image2show);
}

