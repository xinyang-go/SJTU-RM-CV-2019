#include <show_images/show_images.h>
#include <opencv2/highgui.hpp>
#include <options/options.h>
#include <log.h>

using namespace cv;


void drawLightBlobs(cv::Mat &src, const LightBlobs &blobs){
    for (const auto &blob:blobs) {
        Scalar color(0,255,0);
        if (blob.blob_color == BLOB_RED)
            color = Scalar(0, 0, 255);
        else if (blob.blob_color == BLOB_BLUE)
            color = Scalar(255, 0, 0);
        cv::Point2f vertices[4];
        blob.rect.points(vertices);
        for (int j = 0; j < 4; j++) {
            cv::line(src, vertices[j], vertices[(j + 1) % 4], color, 2);
        }
    }
}

/**************************
 *     显示多个装甲板区域    *
 **************************/
void showArmorBoxes(std::string windows_name, const cv::Mat &src, const ArmorBoxes &armor_boxes) {
    static Mat image2show;
    if (src.type() == CV_8UC1) {// 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }

    for (auto &box:armor_boxes) {
        if(box.box_color == BOX_BLUE) {
            rectangle(image2show, box.rect, Scalar(0, 255, 0), 1);
            drawLightBlobs(image2show, box.light_blobs);
        }else if(box.box_color == BOX_RED){
            rectangle(image2show, box.rect, Scalar(0, 255, 0), 1);
            drawLightBlobs(image2show, box.light_blobs);
        }

    }
    imshow(windows_name, image2show);
}

/**************************
 * 显示多个装甲板区域及其类别 *
 **************************/
void showArmorBoxesClass(std::string window_names, const cv::Mat &src, const ArmorBoxes boxes[15]) {
    static Mat image2show;
    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }
    for (int i = 1; i < 15; i++) {
        if (!boxes[i].empty()) {
            for (auto box : boxes[i]) {
                rectangle(image2show, box.rect, Scalar(0, 255, 0), 1);
                drawLightBlobs(image2show, box.light_blobs);
                if (i == -1)
                    putText(image2show, id2name[i], Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                            Scalar(0, 255, 0));
                else if (1 <= i && i < 8)
                    putText(image2show, id2name[i], Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                            Scalar(255, 0, 0));
                else if (8 <= i && i < 15)
                    putText(image2show, id2name[i], Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
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
void showArmorBox(std::string windows_name, const cv::Mat &src, const ArmorBox &box) {
    static Mat image2show;
    if(box.rect == cv::Rect2d()){
        imshow(windows_name, src);
    }
    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }
    drawLightBlobs(image2show, box.light_blobs);
//    static FILE *fp = fopen(PROJECT_DIR"/ratio.txt", "w");
//    if(box.light_blobs.size() == 2)
//        fprintf(fp, "%lf %lf %lf\n", box.light_blobs[0].length, box.light_blobs[1].length, box.blobsDistance())
//    cout << box.lengthDistanceRatio() << endl;
    if(box.lengthDistanceRatio() < 0.4 && box.lengthRatio() > 0.9){
        rectangle(image2show, box.rect, Scalar(0, 255, 0), 3);
    }else{
        rectangle(image2show, box.rect, Scalar(0, 255, 0), 1);
    };

    char dist[5];
//    sprintf(dist, "%.1f", distance);
    if (box.id == -1)
        putText(image2show, id2name[box.id]+" "+dist, Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(0, 255, 0));
    else if (1 <= box.id && box.id < 8)
        putText(image2show, id2name[box.id]+" "+dist, Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(255, 0, 0));
    else if (8 <= box.id && box.id < 15)
        putText(image2show, id2name[box.id]+" "+dist, Point(box.rect.x + 2, box.rect.y + 2), cv::FONT_HERSHEY_TRIPLEX, 1,
                Scalar(0, 0, 255));
    else if (box.id != 0)
        LOGE_INFO("Invalid box id:%d!", box.id);
    imshow(windows_name, image2show);
}

/**************************
 *      显示多个灯条区域     *
 **************************/
void showLightBlobs(std::string windows_name, const cv::Mat &src, const LightBlobs &light_blobs) {
    static Mat image2show;

    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }

    for (const auto &light_blob:light_blobs) {
        Scalar color(0, 255, 0);
        if (light_blob.blob_color == BLOB_RED)
            color = Scalar(0, 0, 255);
        else if (light_blob.blob_color == BLOB_BLUE)
            color = Scalar(255, 0, 0);
        cv::Point2f vertices[4];
        light_blob.rect.points(vertices);
        for (int j = 0; j < 4; j++) {
            cv::line(image2show, vertices[j], vertices[(j + 1) % 4], color, 2);
        }
    }
    imshow(windows_name, image2show);
}


void showTrackSearchingPos(std::string window_names, const cv::Mat &src, const cv::Rect2d pos){
    static Mat image2show;
    if (src.type() == CV_8UC1) { // 黑白图像
        cvtColor(src, image2show, COLOR_GRAY2RGB);
    } else if (src.type() == CV_8UC3) { //RGB 彩色
        image2show = src.clone();
    }
    rectangle(image2show, pos, Scalar(0, 255, 0), 1);
    imshow(window_names, image2show);
}