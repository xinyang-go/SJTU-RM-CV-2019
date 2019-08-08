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

static systime getFrontTime(const vector<systime> time_seq, const vector<float> angle_seq) {
    double A = 0, B = 0, C = 0, D = 0;
    int len = time_seq.size();
    for (int i = 0; i < len; i++) {
        A += angle_seq[i] * angle_seq[i];
        B += angle_seq[i];
        C += angle_seq[i] * time_seq[i];
        D += time_seq[i];
        cout << "(" << angle_seq[i] << ", " << time_seq[i] << ") ";
    }
    double b = (A * D - B * C) / (len * A - B * B);
    cout << b << endl;
    return b;
}

void ArmorFinder::antiTop() {
    if (target_box.rect == cv::Rect2d()) return;
    if (getPointLength(last_box.getCenter() - target_box.getCenter()) > last_box.rect.height * 1.5) {
        auto front_time = getFrontTime(time_seq, angle_seq);
        auto once_periodms = getTimeIntervalms(front_time, last_front_time);
//        if (abs(once_periodms - top_periodms[-1]) > 50) {
//            sendBoxPosition(0);
//            return;
//        }

        LOGM(STR_CTR(WORD_GREEN, "Top period: %.1lf"), once_periodms);
        top_periodms.push(once_periodms);
        auto periodms = mean(top_periodms);
        systime curr_time;
        getsystime(curr_time);
        uint16_t shoot_delay = front_time + periodms * 2 - curr_time;
        if (anti_top_cnt < 4) {
            sendBoxPosition(0);
        } else if (abs(once_periodms - top_periodms[-1]) > 50) {
            sendBoxPosition(0);
        } else {
            sendBoxPosition(shoot_delay);
        }
        time_seq.clear();
        angle_seq.clear();
        last_front_time = front_time;
    } else {
        time_seq.emplace_back(frame_time);
        double dx = target_box.rect.x + target_box.rect.width / 2 - IMAGE_CENTER_X;
        double yaw = atan(dx / FOCUS_PIXAL) * 180 / PI;
        angle_seq.emplace_back(yaw);
        sendBoxPosition(0);
    }
    anti_top_cnt++;
}

