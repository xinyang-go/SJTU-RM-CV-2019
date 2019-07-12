//
// Created by xinyang on 19-7-10.
//

#include <armor_finder/armor_finder.h>

static double lw_rate(const cv::RotatedRect &rect) {
    return rect.size.height > rect.size.width ?
           rect.size.height / rect.size.width :
           rect.size.width / rect.size.height;
}

bool rectangleContainPoint(cv::RotatedRect rectangle, cv::Point2f point) {
    //转化为轮廓
    cv::Point2f corners[4];
    rectangle.points(corners);
    cv::Point2f *lastItemPointer = (corners + sizeof corners / sizeof corners[0]);
    vector<cv::Point2f> contour(corners, lastItemPointer);
    //判断
    double indicator = pointPolygonTest(contour, point, true);
    return indicator >= 0;
}

// 下面的函数可以有性能优化，暂时未做。
static double nonZeroRateOfRotateRect(const cv::Mat &bin, const cv::RotatedRect &rotrect) {
    auto rect = rotrect.boundingRect();
    if (rect.x < 0 || rect.y < 0 || rect.x + rect.width > bin.cols || rect.y + rect.height > bin.rows) {
        return 0;
    }
    auto roi = bin(rect);
    int cnt = 0;
    for (int r = 0; r < roi.rows; r++) {
        for (int c = 0; c < roi.cols; c++) {
            if (rectangleContainPoint(rotrect, cv::Point(c + rect.x, r + rect.y))) {
                if (roi.at<uint8_t>(r, c)) {
                    cnt++;
                }
            }
        }
    }
    return double(cnt) / rotrect.size.area();
}

int linePointX(const cv::Point2f &p1, const cv::Point2f &p2, int y) {
    return (p2.x - p1.x) / (p2.y - p1.y) * (y - p1.y) + p1.x;
}

// 性能优化后的函数
static double nonZeroRateOfRotateRect_opt(const cv::Mat &bin, const cv::RotatedRect &rotrect) {
    int cnt = 0;
    cv::Point2f corners[4];
    rotrect.points(corners);
    sort(corners, &corners[4], [](cv::Point2f p1, cv::Point2f p2) {
        return p1.y < p2.y;
    });
    for (int r = corners[0].y; r < corners[1].y; r++) {
        auto start = min(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) - 1;
        auto end = max(linePointX(corners[0], corners[1], r), linePointX(corners[0], corners[2], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    for (int r = corners[1].y; r < corners[2].y; r++) {
        auto start = min(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) - 1;
        auto end = max(linePointX(corners[0], corners[2], r), linePointX(corners[1], corners[3], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    for (int r = corners[2].y; r < corners[3].y; r++) {
        auto start = min(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) - 1;
        auto end = max(linePointX(corners[1], corners[3], r), linePointX(corners[2], corners[3], r)) + 1;
        if (start < 0 || end > 640) return 0;
        for (int c = start; c < end; c++) {
            if (bin.at<uint8_t>(r, c)) {
                cnt++;
            }
        }
    }
    return double(cnt) / rotrect.size.area();
}

static bool isValidLightBlob(const cv::Mat &bin, const cv::RotatedRect &rect) {
    return (lw_rate(rect) > 1.5) &&
           //           (rect.size.width*rect.size.height < 3000) &&
           (rect.size.width * rect.size.height > 1) &&
           (nonZeroRateOfRotateRect_opt(bin, rect) > 0.8);
//           (nonZeroRateOfRotateRect(bin, rect) > 0.8);
}

void get_blob_color(const cv::Mat &src, std::vector<LightBlob> &blobs) {
    for (auto &blob : blobs) {
        auto region = blob.rect.boundingRect();
        region.x -= fmax(2, region.width * 0.1);
        region.y -= fmax(2, region.height * 0.05);
        region.width += 2 * fmax(2, region.width * 0.1);
        region.height += 2 * fmax(2, region.height * 0.05);
        region &= cv::Rect(0, 0, 640, 480);
        cv::Mat roi = src(region);
        long long int red_cnt = 0, blue_cnt = 0;
        for (int row = 0; row < roi.rows; row++) {
            for (int col = 0; col < roi.cols; col++) {
                red_cnt += roi.at<cv::Vec3b>(row, col)[2];
                blue_cnt += roi.at<cv::Vec3b>(row, col)[0];
            }
        }
        if (red_cnt > blue_cnt) {
            blob.BlobColor = BLOB_RED;
        } else {
            blob.BlobColor = BLOB_BLUE;
        }
    }
}

bool ArmorFinder::findLightBlobs(const cv::Mat &src_bin, LightBlobs &light_blobs) {
    std::vector<std::vector<cv::Point> > light_contours;
    cv::findContours(src_bin, light_contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

    for (auto &light_contour : light_contours) {
        cv::RotatedRect rect = cv::minAreaRect(light_contour);
        if (isValidLightBlob(src_bin, rect)) {
            light_blobs.emplace_back(rect);
        }
    }
    get_blob_color(src_raw, light_blobs);
    return light_blobs.size() >= 2;
}