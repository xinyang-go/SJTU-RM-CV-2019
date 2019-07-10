#include <show_images/show_images.h>
#include <opencv2/highgui.hpp>
#include <log.h>

using namespace cv;

/**************************
 *     显示多个装甲板区域    *
 **************************/
void showArmorBoxVector(std::string windows_name, const cv::Mat &src, const std::vector<cv::Rect2d> &armor_box) {
    static Mat image2show;
    if (src.type() == CV_8UC1) {// 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }

    for (auto &box:armor_box) {
        rectangle(image2show, box, Scalar(0, 255, 0), 1);
    }
    imshow(windows_name, image2show);
}

/**************************
 * 显示多个装甲板区域及其类别 *
 **************************/
void showArmorBoxClass(std::string window_names, const cv::Mat &src, vector<cv::Rect2d> boxes[10]) {
    static Mat image2show;
    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }
    for (int i = 0; i < 14; i++) {
        if (!boxes[i].empty()) {
            for (auto box : boxes[i]) {
                rectangle(image2show, box, Scalar(0, 255, 0), 1);
                if (i == -1)
                    putText(image2show, id2name[i], Point(box.x + 2, box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                            Scalar(0, 255, 0));
                else if (1 <= i && i < 8)
                    putText(image2show, id2name[i], Point(box.x + 2, box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                            Scalar(255, 0, 0));
                else if (8 <= i && i < 15)
                    putText(image2show, id2name[i], Point(box.x + 2, box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                            Scalar(0, 0, 255));
                else if (i != 0)
                    LOGE_INFO("Invalid box id:%d!", i);
            }
        }
    }
    imshow(window_names, image2show);
}

/**************************
 * 显示单个装甲板区域及其类别 *
 **************************/
void showArmorBox(std::string windows_name, const cv::Mat &src, cv::Rect2d armor_box, int boxid) {
    static Mat image2show;
    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }
    rectangle(image2show, armor_box, Scalar(0, 255, 0), 1);
    char dist[5];
//    sprintf(dist, "%.1f", distance);
    if (boxid == -1)
        putText(image2show, id2name[boxid]+" "+dist, Point(armor_box.x + 2, armor_box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(0, 255, 0));
    else if (1 <= boxid && boxid < 8)
        putText(image2show, id2name[boxid]+" "+dist, Point(armor_box.x + 2, armor_box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(255, 0, 0));
    else if (8 <= boxid && boxid < 15)
        putText(image2show, id2name[boxid]+" "+dist, Point(armor_box.x + 2, armor_box.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(0, 0, 255));
    else if (boxid != 0)
        LOGE_INFO("Invalid box id:%d!", boxid);
    imshow(windows_name, image2show);
}

/**************************
 *      显示多个灯条区域     *
 **************************/
void showContours(std::string windows_name, const cv::Mat &src, const std::vector<LightBlob> &light_blobs) {
    static Mat image2show;

    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }

    for (const auto &light_blob:light_blobs) {
        Scalar color;
        if (light_blob.BlobColor == BLOB_RED)
            color = Scalar(0, 0, 255);
        else if (light_blob.BlobColor == BLOB_BLUE)
            color = Scalar(255, 0, 0);
        else
            color = Scalar(0, 255, 0);
        cv::Point2f vertices[4];
        light_blob.rect.points(vertices);
        for (int j = 0; j < 4; j++) {
            cv::line(image2show, vertices[j], vertices[(j + 1) % 4], color, 2);
        }
    }
    imshow(windows_name, image2show);
}
