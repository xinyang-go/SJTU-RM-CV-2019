//
// Created by xinyang on 19-7-10.
//

#include <armor_finder/armor_finder.h>
#include <opencv2/highgui.hpp>

static double lw_rate(const cv::RotatedRect &rect) {
    return rect.size.height > rect.size.width ?
           rect.size.height / rect.size.width :
           rect.size.width / rect.size.height;
}


static double areaRatio(const std::vector<cv::Point> &contour, const cv::RotatedRect &rect){
    return cv::contourArea(contour) / rect.size.area();
}

static bool isValidLightBlob(const std::vector<cv::Point> &contour, const cv::RotatedRect &rect) {
    return (1.5 < lw_rate(rect) && lw_rate(rect) < 10) &&
//           (rect.size.area() < 3000) &&
            ((rect.size.area() < 50 && areaRatio(contour, rect) > 0.5) ||
            (rect.size.area() >= 50 && areaRatio(contour, rect) > 0.7));
}

// 此函数可以有性能优化.
static uint8_t get_blob_color(const cv::Mat &src, const cv::RotatedRect &blobPos) {
    auto region = blobPos.boundingRect();
    region.x -= fmax(2, region.width * 0.1);
    region.y -= fmax(2, region.height * 0.05);
    region.width += 2 * fmax(2, region.width * 0.1);
    region.height += 2 * fmax(2, region.height * 0.05);
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

static float linePointX(const cv::Point2f &p1, const cv::Point2f &p2, int y) {
    return (p2.x - p1.x) / (p2.y - p1.y) * (y - p1.y) + p1.x;
}

/// Todo:性能优化后的函数（还有点问题）
static double get_blob_color_opt(const cv::Mat &src, cv::RotatedRect blobPos) {
    int blue_cnt=0, red_cnt=0;
    blobPos.size.height *= 1.05;
    blobPos.size.width *= 1.1;
    cv::Point2f corners[4];
    blobPos.points(corners);
    sort(corners, &corners[4], [](cv::Point2f p1, cv::Point2f p2) {
        return p1.y < p2.y;
    });
    for (int r = corners[0].y; r < corners[1].y; r++) {
        auto start = min(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) - 1;
        auto end = max(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            red_cnt += src.at<cv::Vec3b>(r, c)[2];
            blue_cnt += src.at<cv::Vec3b>(r, c)[0];
        }
    }
    for (int r = corners[1].y; r < corners[2].y; r++) {
        auto start = min(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) - 1;
        auto end = max(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            red_cnt += src.at<cv::Vec3b>(r, c)[2];
            blue_cnt += src.at<cv::Vec3b>(r, c)[0];
        }
    }
    for (int r = corners[2].y; r < corners[3].y; r++) {
        auto start = min(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) - 1;
        auto end = max(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            red_cnt += src.at<cv::Vec3b>(r, c)[2];
            blue_cnt += src.at<cv::Vec3b>(r, c)[0];
        }
    }
    if (red_cnt > blue_cnt) {
        return BLOB_RED;
    } else {
        return BLOB_BLUE;
    }
}

static void imagePreProcess(cv::Mat &src) {
    static cv::Mat kernel_erode = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode);

    static cv::Mat kernel_dilate = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate);

    static cv::Mat kernel_dilate2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate2);

    static cv::Mat kernel_erode2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode2);

//    float alpha = 1.5;
//    int beta = 0;
//    src.convertTo(src, -1, alpha, beta);
}

bool ArmorFinder::findLightBlobs(const cv::Mat &src, LightBlobs &light_blobs) {
    cv::Mat src_bin, color_channel;
    std::vector<cv::Mat> channels;       // 通道拆分

    cv::split(src, channels);               /************************/
    if (enemy_color == ENEMY_BLUE)          /*                      */
        color_channel = channels[0];        /* 根据目标颜色进行通道提取 */
    else if (enemy_color == ENEMY_RED)      /*                      */
        color_channel = channels[2];        /************************/
    cv::threshold(color_channel, src_bin, 160, 255, CV_THRESH_BINARY); // 二值化对应通道
    imagePreProcess(src_bin);                                  // 开闭运算

    if(src_bin.size() == cv::Size(640, 480))
        imshow("bin", src_bin);

    std::vector<std::vector<cv::Point> > light_contours;
    cv::findContours(src_bin, light_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    for (auto &light_contour : light_contours) {
        cv::RotatedRect rect = cv::minAreaRect(light_contour);
        if (isValidLightBlob(light_contour, rect)) {
            light_blobs.emplace_back(rect, get_blob_color(src, rect));
        }
    }
    return light_blobs.size() >= 2;
}