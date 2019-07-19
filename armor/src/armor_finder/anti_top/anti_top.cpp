//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>
#include <log.h>

static double getTimeIntervalms(const timeval& now, const timeval &last){
    return (now.tv_sec-last.tv_sec)*1000.0 + (now.tv_usec-last.tv_usec)/1000.0;
}

void ArmorFinder::antiTop() {
    double top_periodms = 0;
    timeval curr_time;
    if(anti_top_state == ANTI_TOP){
        cout << "anti top" << endl;
    }else if(anti_top_state == NORMAL){
        cout << "Normal" << endl;
    }
    ArmorBox::BoxOrientation orientation = armor_box.getOrientation();
    if(orientation == ArmorBox::UNKNOWN){
        if(anti_top_state == NORMAL){
            sendBoxPosition();
            return;
        }else{
            return;
        }
    }
    if(orientation != last_orient){
        gettimeofday(&curr_time, nullptr);
        auto interval = getTimeIntervalms(curr_time, last_front_time);
        if(interval > 700){
            anti_top_cnt = 0;
            anti_top_state = NORMAL;
            if(orientation == ArmorBox::FRONT){
                last_front_time = curr_time;
            }
        }else if(interval > 150){
            if(orientation == ArmorBox::FRONT){
                anti_top_cnt++;
                if(anti_top_state == ANTI_TOP){
                    top_periodms = interval;
                    LOGM(STR_CTR(WORD_LIGHT_GREEN, "top period: %.1lf ms"), top_periodms);
                }
                last_front_time = curr_time;
            }
        }
        last_orient = orientation;
    }
    if(anti_top_cnt > 4){
        anti_top_state = ANTI_TOP;
    }

    if(anti_top_state == ANTI_TOP){
        if(orientation == ArmorBox::FRONT){
            sendBoxPosition();
        }
    }else if(anti_top_state == NORMAL){
        sendBoxPosition();
    }


    last_orient = orientation;
}

