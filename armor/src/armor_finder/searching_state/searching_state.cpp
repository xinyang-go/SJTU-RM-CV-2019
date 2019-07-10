//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>
#include <opencv2/highgui.hpp>
#include <show_images/show_images.h>
#include <options/options.h>
#include <log.h>


static string prior_blue[] = {
        "B8", "B1", "B3", "B4", "B5", "B7", "B2",
        "R8", "R1", "R3", "R4", "R5", "R7", "R2",
};

static string prior_red[] = {
        "R8", "R1", "R3", "R4", "R5", "R7", "R2",
        "B8", "B1", "B3", "B4", "B5", "B7", "B2",
};

void imagePreProcess(cv::Mat &src) {
    static cv::Mat kernel_erode = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode);

    static cv::Mat kernel_dilate = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate);

    static cv::Mat kernel_dilate2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    dilate(src, src, kernel_dilate2);

    static cv::Mat kernel_erode2 = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 5));
    erode(src, src, kernel_erode2);

    float alpha = 1.5;
    int beta = 0;
    src.convertTo(src, -1, alpha, beta);
}

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    std::vector<cv::Mat> channels;      // 通道拆分
    cv::Mat src_bin, color;             // 二值图和颜色通道图
    LightBlobs light_blobs;             // 存储所有可能的灯条
    std::vector<cv::Rect2d> armor_boxes; // 装甲板候选区
    std::vector<cv::Rect2d> boxes_number[15]; // 装甲板候选区放置在对应id位置

    armor_box = cv::Rect2d(0, 0, 0, 0);      // 重置目标装甲板位置
    boxid = -1;                              // 重置目标装甲板id

    cv::split(src, channels);               /************************/
    if (enemy_color == ENEMY_BLUE)          /*                      */
        color = channels[0];                /* 根据目标颜色进行通道提取 */
    else if (enemy_color == ENEMY_RED)      /*                      */
        color = channels[2];                /************************/
    cv::threshold(color, src_bin, 170, 255, CV_THRESH_BINARY); // 二值化对应通道
    imagePreProcess(src_bin);                                  // 开闭运算
    if (!findLightBlobs(src_bin, light_blobs)) {
        return false;
    }
    if (show_light_blobs) {
        showContours("light_blobs", src, light_blobs);
        cv::waitKey(1);
    }

    if (!findArmorBoxes(light_blobs, armor_boxes)) {
        return false;
    }
    if (show_armor_boxes) {
        showArmorBoxVector("boxes", src, armor_boxes);
        cv::waitKey(1);
    }

    if (classifier && use_classifier) {
        for (auto box : armor_boxes) {
            cv::Mat roi = src(box).clone();
            cv::resize(roi, roi, cv::Size(48, 36));
            int c = classifier(roi);
            boxes_number[c].emplace_back(box);
        }
        if (enemy_color == ENEMY_BLUE) {
            for (auto name : prior_blue) {
                if (!boxes_number[name2id[name]].empty()) {
                    armor_box = boxes_number[name2id[name]][0];
                    boxid = name2id[name];
                    break;
                }
            }
        } else if (enemy_color == ENEMY_RED) {
            for (auto name : prior_red) {
                if (!boxes_number[name2id[name]].empty()) {
                    armor_box = boxes_number[name2id[name]][0];
                    boxid = name2id[name];
                    break;
                }
            }
        } else {
            LOGE_INFO("enemy_color ERROR!");
        }
        if (armor_box == cv::Rect2d(0, 0, 0, 0)) {
            return false;
        }
        if (show_armor_boxes) {
            showArmorBoxClass("class", src, boxes_number);
        }
        if (save_labelled_boxes) {
            for (int i = 0; i < sizeof(boxes_number) / sizeof(boxes_number[0]); i++) {
                for (auto &box : boxes_number[i]) {
                    char filename[100];
                    sprintf(filename, PROJECT_DIR"/armor_box_photo/%s_%d.jpg", id2name[i].data(),
                            time(nullptr) + clock());
                    cv::imwrite(filename, src(box));
                }
            }
        }
    } else {
        armor_box = armor_boxes[0];
        boxid = -1;
    }
    return sendBoxPosition();
}
