//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>
#include <additions.h>
#include <log.h>

static double boxDistance(const cv::Rect2d &a, const cv::Rect2d &b) {
    cv::Point2d centerA(a.x + a.width / 2, a.y + a.height / 2);
    cv::Point2d centerB(b.x + b.width / 2, b.y + b.height / 2);
    auto dist = centerA - centerB;
    return sqrt(dist.x * dist.x + dist.y * dist.y);
}

template<int length>
static double mean(RoundQueue<double, length> &vec) {
    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum / length;
}

ArmorFinder::BoxRatioChangeType ArmorFinder::getRatioChangeType(RoundQueue<double, 5> &vec) {
    auto d = (vec[0] - vec[1] + vec[3] + vec[4]);
    if (d > 0.15) {
        return INCREASE;
    } else if (d < -0.15) {
        return DECREASE;
    } else {
        return NOCHANGE;
    }
}

/*
void ArmorFinder::antiTop() {
    if (target_box.rect == cv::Rect2d()) return;
    uint16_t shoot_delay = 0;
    auto interval = getTimeIntervalms(frame_time, last_front_time);
    box_ratioes.push(target_box.rect.width / target_box.rect.height);
    auto change_type = getRatioChangeType(box_ratioes);
    auto orientation = target_box.getOrientation();
    if (interval > 700) {
        anti_top_cnt = 0;
        if (anti_top_state == ANTI_TOP) {
            anti_top_state = NORMAL;
            LOGM(STR_CTR(WORD_YELLOW, "switch to normal"));
        }
    }
    if (change_type == INCREASE && last_ratio_type != change_type) {
        last_front_time = frame_time;
        if (150 < interval && interval < 700) {
            if (anti_top_state == ANTI_TOP) {
                top_periodms.push(interval);
                LOGM(STR_CTR(WORD_LIGHT_GREEN, "top period: %.1lf ms"), interval);
                systime curr_time;
                getsystime(curr_time);
                auto calculate_time = getTimeIntervalms(curr_time, frame_time);
                shoot_delay = mean(top_periodms) - calculate_time;
            } else if (anti_top_state == NORMAL) {
                if (++anti_top_cnt > 4) {
                    anti_top_state = ANTI_TOP;
                    LOGM(STR_CTR(WORD_CYAN, "switch to anti-top"));
                }
            }
        }
    }
    if (change_type != NOCHANGE) {
        last_ratio_type = change_type;
    }
    if (anti_top_state == ANTI_TOP) {
        if (orientation == ArmorBox::FRONT) {
            sendBoxPosition(shoot_delay);
        }
    } else if (anti_top_state == NORMAL) {
        sendBoxPosition(shoot_delay);
    }
}
*/

void ArmorFinder::antiTop() {
    if (target_box.rect == cv::Rect2d()) return;
    uint16_t shoot_delay = 0;
    auto interval = getTimeIntervalms(frame_time, last_front_time);
    if (anti_top_state == ANTI_TOP && interval > 700) {
        anti_top_state = NORMAL;
        LOGM(STR_CTR(WORD_YELLOW, "switch to normal"));
    }
//    cout << getPointLength(last_box.getCenter() - target_box.getCenter()) << endl;
    if (getPointLength(last_box.getCenter() - target_box.getCenter()) > last_box.rect.height * 2.0) {
        LOGM("switch!");
        if (150 < interval && interval < 700) {
            if (anti_top_state == ANTI_TOP) {
                top_periodms.push(interval);
                LOGM(STR_CTR(WORD_LIGHT_GREEN, "top period: %.1lf ms"), interval);
                systime curr_time;
                getsystime(curr_time);
                auto calculate_time = getTimeIntervalms(curr_time, frame_time);
                shoot_delay = mean(top_periodms) - calculate_time;
                sendBoxPosition(shoot_delay);
            } else {
                if (++anti_top_cnt > 4) {
                    anti_top_state = ANTI_TOP;
                    LOGM(STR_CTR(WORD_CYAN, "switch to anti-top"));
                }
            }
        }
        last_front_time = frame_time;
    }
    if (anti_top_state == NORMAL) {
        sendBoxPosition(0);
    } else if (interval < top_periodms[-1] * 0.2){
        sendBoxPosition(0);
    }
    last_box = target_box;
}

