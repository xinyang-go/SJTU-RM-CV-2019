//
// Created by xinyang on 19-7-13.
//

#include <armor_finder/armor_finder.h>
#include <log.h>

ArmorBox::ArmorBox(const cv::Rect &pos, const LightBlobs &blobs, uint8_t color, int i) :
        rect(pos), light_blobs(blobs), box_color(color), id(i) {};

// 获取装甲板中心点
cv::Point2f ArmorBox::getCenter() const {
    return cv::Point2f(
            rect.x + rect.width / 2,
            rect.y + rect.height / 2
    );
}

// 获取两个灯条中心点的间距
double ArmorBox::getBlobsDistance() const {
    if (light_blobs.size() == 2) {
        auto &x = light_blobs[0].rect.center;
        auto &y = light_blobs[1].rect.center;
        return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y));
    } else {
        return 0;
    }
}

// 获取灯条长度和间距的比例
double ArmorBox::lengthDistanceRatio() const {
    if (light_blobs.size() == 2) {
        return max(light_blobs[0].length, light_blobs[1].length)
               / getBlobsDistance();
    } else {
        return 100;
    }
}

// 计算装甲板到摄像头的距离
double ArmorBox::getBoxDistance() const {
    if (light_blobs.size() == 2) {
        return DISTANCE_HEIGHT / 2 / max(light_blobs[0].length, light_blobs[1].length);
    } else {
        return DISTANCE_HEIGHT / rect.height;
    }
}

// 判断装甲板的正对还是侧对(已弃用，误差过大)
ArmorBox::BoxOrientation ArmorBox::getOrientation() const {
    if (light_blobs.size() != 2) {
        return UNKNOWN;
    }
    switch (id) {
        case R1:
        case R7:
        case R8:
        case B1:
        case B7:
        case B8:
            if (lengthDistanceRatio() < 0.26) {
                return FRONT;
            } else {
                return SIDE;
            }
        case R2:
        case R3:
        case R4:
        case R5:
        case B2:
        case B3:
        case B4:
        case B5:
            if (lengthDistanceRatio() < 0.51) {
                return FRONT;
            } else {
                return SIDE;
            }
        default:
            return UNKNOWN;
    }
}
// 装甲板的优先级比较
bool ArmorBox::operator<(const ArmorBox &box) const {
    if (id != box.id) {
        if (box_color == BOX_BLUE) {
            return prior_blue[id2name[id]] < prior_blue[id2name[box.id]];
        } else {
            return prior_red[id2name[id]] < prior_red[id2name[box.id]];
        }
    } else {
        auto d1 = (rect.x - IMAGE_CENTER_X) * (rect.x - IMAGE_CENTER_X)
                  + (rect.y - IMAGE_CENTER_Y) * (rect.y - IMAGE_CENTER_Y);
        auto d2 = (box.rect.x - IMAGE_CENTER_X) * (box.rect.x - IMAGE_CENTER_X)
                  + (box.rect.y - IMAGE_CENTER_Y) * (box.rect.y - IMAGE_CENTER_Y);
        return d1 < d2;
    }
}

