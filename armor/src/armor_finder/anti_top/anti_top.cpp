//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>
#include <additions.h>
#include <log.h>

template<int length>
static double mean(RoundQueue<double, length> &vec) {
    double sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum / length;
}

void ArmorFinder::antiTop() {
    if (target_box.rect == cv::Rect2d()) return;
    uint16_t shoot_delay = 0;
    auto interval = getTimeIntervalms(frame_time, last_front_time);
    if (anti_top_state == ANTI_TOP && interval > 700) {
        anti_top_state = NORMAL;
        LOGM(STR_CTR(WORD_YELLOW, "switch to normal"));
    }
    if (getPointLength(last_box.getCenter() - target_box.getCenter()) > last_box.rect.height * 1.5) {
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
    } else if (interval < top_periodms[-1] * 0.1){
        sendBoxPosition(shoot_delay);
    }
    last_box = target_box;
}

