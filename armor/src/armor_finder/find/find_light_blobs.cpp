//
// Created by xinyang on 19-7-10.
//

#include <armor_finder/armor_finder.h>
#include <options.h>
#include <opencv2/highgui.hpp>

// 旋转矩形的长宽比
static double lw_rate(const cv::RotatedRect &rect) {
    return rect.size.height > rect.size.width ?
           rect.size.height / rect.size.width :
           rect.size.width / rect.size.height;
}
// 轮廓面积和其最小外接矩形面积之比
static double areaRatio(const std::vector<cv::Point> &contour, const cv::RotatedRect &rect) {
    return cv::contourArea(contour) / rect.size.area();
}
// 判断轮廓是否为一个灯条
static bool isValidLightBlob(const std::vector<cv::Point> &contour, const cv::RotatedRect &rect) {
    return (1.2 < lw_rate(rect) && lw_rate(rect) < 10) &&
           //           (rect.size.area() < 3000) &&
           ((rect.size.area() < 50 && areaRatio(contour, rect) > 0.4) ||
            (rect.size.area() >= 50 && areaRatio(contour, rect) > 0.6));
}
// 判断灯条颜色(此函数可以有性能优化).
static uint8_t get_blob_color(const cv::Mat &src, const cv::RotatedRect &blobPos) {
    auto region = blobPos.boundingRect();
    region.x -= fmax(3, region.width * 0.1);
    region.y -= fmax(3, region.height * 0.05);
    region.width += 2 * fmax(3, region.width * 0.1);
    region.height += 2 * fmax(3, region.height * 0.05);
    region &= cv::Rect(0, 0, src.cols, src.rows);
    cv::Mat roi = src(region);
    int red_cnt = 0, blue_cnt = 0;
    for (int row = 0; row < roi.rows; row++) {
        for (int col = 0; col < roi.cols; col++) {
            red_cnt += roi.at<cv::Vec3b>(row, col)[2];
            blue_cnt += roi.at<cv::Vec3b>(row, col)[0];
        }
    }
    if (red_cnt > blue_cnt) {
        return BLOB_RED;
    } else {
        return BLOB_BLUE;
    }
}
// 判断两个灯条区域是同一个灯条
static bool isSameBlob(LightBlob blob1, LightBlob blob2) {
    auto dist = blob1.rect.center - blob2.rect.center;
    return (dist.x * dist.x + dist.y * dist.y) < 9;
}
// 开闭运算
static void imagePreProcess(cv::Mat &src) {
    static cv::Mat kernel_erode = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode);

    static cv::Mat kernel_dilate = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate);

    static cv::Mat kernel_dilate2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate2);

    static cv::Mat kernel_erode2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode2);
}
// 在给定图像上寻找所有可能的灯条
bool ArmorFinder::findLightBlobs(const cv::Mat &src, LightBlobs &light_blobs) {
    cv::Mat color_channel;
    cv::Mat src_bin_light, src_bin_dim;
    std::vector<cv::Mat> channels;       // 通道拆分

    cv::split(src, channels);               /************************/
    if (enemy_color == ENEMY_BLUE) {         /*                      */
        color_channel = channels[0];        /* 根据目标颜色进行通道提取 */
    } else if (enemy_color == ENEMY_RED) {    /*                      */
        color_channel = channels[2];        /************************/
    }

    int light_threshold;
    if(enemy_color == ENEMY_BLUE){
        light_threshold = 225;
    }else{
        light_threshold = 200;
    }
    cv::threshold(color_channel, src_bin_light, light_threshold, 255, CV_THRESH_BINARY); // 二值化对应通道
    if (src_bin_light.empty()) return false;
    imagePreProcess(src_bin_light);                                  // 开闭运算

    cv::threshold(color_channel, src_bin_dim, 140, 255, CV_THRESH_BINARY); // 二值化对应通道
    if (src_bin_dim.empty()) return false;
    imagePreProcess(src_bin_dim);                                  // 开闭运算

    if (src_bin_light.size() == cv::Size(640, 480) && show_light_blobs) {
        imshow("bin_light", src_bin_light);
        imshow("bin_dim", src_bin_dim);
    }
// 使用两个不同的二值化阈值同时进行灯条提取，减少环境光照对二值化这个操作的影响。
// 同时剔除重复的灯条，剔除冗余计算，即对两次找出来的灯条取交集。
    std::vector<std::vector<cv::Point>> light_contours_light, light_contours_dim;
    LightBlobs light_blobs_light, light_blobs_dim;
    std::vector<cv::Vec4i> hierarchy_light, hierarchy_dim;
    cv::findContours(src_bin_light, light_contours_light, hierarchy_light, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
    cv::findContours(src_bin_dim, light_contours_dim, hierarchy_dim, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
    for (int i = 0; i < light_contours_light.size(); i++) {
        if (hierarchy_light[i][2] == -1) {
            cv::RotatedRect rect = cv::minAreaRect(light_contours_light[i]);
            if (isValidLightBlob(light_contours_light[i], rect)) {
                light_blobs_light.emplace_back(
                        rect, areaRatio(light_contours_light[i], rect), get_blob_color(src, rect)
                );
            }
        }
    }
    for (int i = 0; i < light_contours_dim.size(); i++) {
        if (hierarchy_dim[i][2] == -1) {
            cv::RotatedRect rect = cv::minAreaRect(light_contours_dim[i]);
            if (isValidLightBlob(light_contours_dim[i], rect)) {
                light_blobs_dim.emplace_back(
                        rect, areaRatio(light_contours_dim[i], rect), get_blob_color(src, rect)
                );
            }
        }
    }
    vector<int> light_to_remove, dim_to_remove;
    for (int l = 0; l != light_blobs_light.size(); l++) {
        for (int d = 0; d != light_blobs_dim.size(); d++) {
            if (isSameBlob(light_blobs_light[l], light_blobs_dim[d])) {
                if (light_blobs_light[l].area_ratio > light_blobs_dim[d].area_ratio) {
                    dim_to_remove.emplace_back(d);
                } else {
                    light_to_remove.emplace_back(l);
                }
            }
        }
    }
    sort(light_to_remove.begin(), light_to_remove.end(), [](int a, int b) { return a > b; });
    sort(dim_to_remove.begin(), dim_to_remove.end(), [](int a, int b) { return a > b; });
    for (auto x : light_to_remove) {
        light_blobs_light.erase(light_blobs_light.begin() + x);
    }
    for (auto x : dim_to_remove) {
        light_blobs_dim.erase(light_blobs_dim.begin() + x);
    }
    for (const auto &light : light_blobs_light) {
        light_blobs.emplace_back(light);
    }
    for (const auto &dim : light_blobs_dim) {
        light_blobs.emplace_back(dim);
    }
    return light_blobs.size() >= 2;
}
