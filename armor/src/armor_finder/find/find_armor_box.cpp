//
// Created by xinyang on 19-7-18.
//

#include <armor_finder/armor_finder.h>
#include <show_images/show_images.h>
#include <options/options.h>
#include <opencv2/highgui.hpp>
#include <log.h>



static bool angelJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    float angle_i = light_blob_i.rect.size.width > light_blob_i.rect.size.height ? light_blob_i.rect.angle :
                    light_blob_i.rect.angle - 90;
    float angle_j = light_blob_j.rect.size.width > light_blob_j.rect.size.height ? light_blob_j.rect.angle :
                    light_blob_j.rect.angle - 90;
    return abs(angle_i - angle_j) < 20;
}

static bool heightJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    cv::Point2f centers = light_blob_i.rect.center - light_blob_j.rect.center;
    return abs(centers.y) < 30;
}

static bool lengthJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    double side_length;
    cv::Point2f centers = light_blob_i.rect.center - light_blob_j.rect.center;
    side_length = sqrt(centers.ddot(centers));
    return (side_length / light_blob_i.length < 8 && side_length / light_blob_i.length > 0.5);
}

static bool lengthRatioJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    return (light_blob_i.length / light_blob_j.length < 2.5
            && light_blob_i.length / light_blob_j.length > 0.4);
}

/* 判断两个灯条的错位度，不知道英文是什么！！！ */
static bool CuoWeiDuJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    float angle_i = light_blob_i.rect.size.width > light_blob_i.rect.size.height ? light_blob_i.rect.angle :
                    light_blob_i.rect.angle - 90;
    float angle_j = light_blob_j.rect.size.width > light_blob_j.rect.size.height ? light_blob_j.rect.angle :
                    light_blob_j.rect.angle - 90;
    float angle = (angle_i + angle_j) / 2.0 / 180.0 * 3.14159265459;
    if (abs(angle_i - angle_j) > 90) {
        angle += 3.14159265459 / 2;
    }
    Vector2f orientation(cos(angle), sin(angle));
    Vector2f p2p(light_blob_j.rect.center.x - light_blob_i.rect.center.x,
                 light_blob_j.rect.center.y - light_blob_i.rect.center.y);
    return abs(orientation.dot(p2p)) < 25;
}

static bool boxAngleJudge(const LightBlob &light_blob_i, const LightBlob &light_blob_j) {
    float angle_i = light_blob_i.rect.size.width > light_blob_i.rect.size.height ? light_blob_i.rect.angle :
                    light_blob_i.rect.angle - 90;
    float angle_j = light_blob_j.rect.size.width > light_blob_j.rect.size.height ? light_blob_j.rect.angle :
                    light_blob_j.rect.angle - 90;
    float angle = (angle_i + angle_j) / 2.0;
    if (abs(angle_i - angle_j) > 90) {
        angle += 90.0;
    }
    return (-120.0 < angle && angle < -60.0) || (60.0 < angle && angle < 120.0);
}

static bool isCoupleLight(const LightBlob &light_blob_i, const LightBlob &light_blob_j, uint8_t enemy_color) {
    return light_blob_i.blob_color == enemy_color &&
           light_blob_j.blob_color == enemy_color &&
           lengthRatioJudge(light_blob_i, light_blob_j) &&
           lengthJudge(light_blob_i, light_blob_j) &&
           //           heightJudge(light_blob_i, light_blob_j) &&
           angelJudge(light_blob_i, light_blob_j) &&
           boxAngleJudge(light_blob_i, light_blob_j) &&
           CuoWeiDuJudge(light_blob_i, light_blob_j);

}

static double centerDistance(const cv::Rect2d &box) {
    double dx = box.x - box.width / 2 - 320;
    double dy = box.y - box.height / 2 - 240;
    return dx * dx + dy * dy;
}

bool matchArmorBoxes(const cv::Mat &src, const LightBlobs &light_blobs, ArmorBoxes &armor_boxes, uint8_t color) {
    armor_boxes.clear();
    for (int i = 0; i < light_blobs.size() - 1; ++i) {
        for (int j = i + 1; j < light_blobs.size(); ++j) {
            if (!isCoupleLight(light_blobs.at(i), light_blobs.at(j), color)) {
                continue;
            }
            cv::Rect2d rect_left = light_blobs.at(static_cast<unsigned long>(i)).rect.boundingRect();
            cv::Rect2d rect_right = light_blobs.at(static_cast<unsigned long>(j)).rect.boundingRect();
            double min_x, min_y, max_x, max_y;
            min_x = fmin(rect_left.x, rect_right.x) - 4;
            max_x = fmax(rect_left.x + rect_left.width, rect_right.x + rect_right.width) + 4;
            min_y = fmin(rect_left.y, rect_right.y) - 0.5 * (rect_left.height + rect_right.height) / 2.0;
            max_y = fmax(rect_left.y + rect_left.height, rect_right.y + rect_right.height) +
                    0.5 * (rect_left.height + rect_right.height) / 2.0;
            if (min_x < 0 || max_x > src.cols || min_y < 0 || max_y > src.rows) {
                continue;
            }
            LightBlobs pair_blobs = {light_blobs.at(i), light_blobs.at(j)};
            armor_boxes.emplace_back(
                    cv::Rect2d(min_x, min_y, max_x - min_x, max_y - min_y),
                    pair_blobs,
                    color
            );
        }
    }
    return !armor_boxes.empty();
}

bool ArmorFinder::findArmorBox(const cv::Mat &src, ArmorBox &box) {
    LightBlobs light_blobs; // 存储所有可能的灯条
    ArmorBoxes armor_boxes; // 装甲板候选区

    box.rect = cv::Rect2d(0, 0, 0, 0);
    box.id = -1;

    if (!findLightBlobs(src, light_blobs)) {
        return false;
    }
    if (show_light_blobs && src.size() == cv::Size(640, 480)) {
        showLightBlobs("light_blobs", src, light_blobs);
        cv::waitKey(1);
    }

    if (!matchArmorBoxes(src, light_blobs, armor_boxes, enemy_color)) {
//        cout << "Box fail!" << endl;
        return false;
    }
    if (show_armor_boxes && src.size() == cv::Size(640, 480)) {
        showArmorBoxes("boxes", src, armor_boxes);
        cv::waitKey(1);
    }

    if (classifier && use_classifier) {
        for (auto &armor_box : armor_boxes) {
            cv::Mat roi = src(armor_box.rect).clone();
            cv::resize(roi, roi, cv::Size(48, 36));
            int c = classifier(roi);
            armor_box.id = c;
        }
        sort(armor_boxes.begin(), armor_boxes.end());
        if(armor_boxes[0].id != 0){
            box = armor_boxes[0];
        }
        if (save_labelled_boxes) {
            for (const auto &one_box : armor_boxes) {
                char filename[100];
                sprintf(filename, PROJECT_DIR"/armor_box_photo/%s_%d.jpg", id2name[one_box.id].data(),
                        time(nullptr) + clock());
                cv::imwrite(filename, src(armor_box.rect & cv::Rect2d(0, 0, src.rows, src.cols)));
            }
        }
        if (box.rect == cv::Rect2d(0, 0, 0, 0)) {
            return false;
        }
        if (show_armor_boxes && src.size() == cv::Size(640, 480)) {
            showArmorBoxesClass("class", src, armor_boxes);
        }
    } else {
        box = armor_boxes[0];
    }
    return true;
}


