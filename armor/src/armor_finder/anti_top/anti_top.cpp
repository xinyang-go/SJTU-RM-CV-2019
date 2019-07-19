//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>
#include <log.h>

static double getTimeIntervalms(const timeval& now, const timeval &last){
    return (now.tv_sec-last.tv_sec)*1000.0 + (now.tv_usec-last.tv_usec)/1000.0;
}

void ArmorFinder::antiTop() {
    static double top_periodms = 0;
    static double last_top_periodms = 0;
    timeval curr_time;
    bool shoot = 0;
    /*if(anti_top_state == ANTI_TOP){
        cout << "anti top" << endl;
    }else if(anti_top_state == NORMAL){
        cout << "Normal" << endl;
    }*/
    ArmorBox::BoxOrientation orientation = armor_box.getOrientation();
    if(orientation == ArmorBox::UNKNOWN){
        if(anti_top_state == NORMAL){
            sendBoxPosition(shoot);
            return;
        }else{
            return;
        }
    }
    gettimeofday(&curr_time, nullptr);
    auto interval = getTimeIntervalms(curr_time, last_front_time);
    LOGM("interval:%.1lf", interval);
    if(anti_top_state == ANTI_TOP && (top_periodms+last_top_periodms)/2.0-130<interval&&interval<(top_periodms+last_top_periodms)/2.0-70){
        shoot = 1;
//        LOGM(STR_CTR(WORD_RED,"Shoot!!!"));
    }else if(interval > 700){
        anti_top_state = NORMAL;
        anti_top_cnt = 0;
    }
    if(orientation != last_orient){
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
                    last_top_periodms = top_periodms;
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
            sendBoxPosition(shoot);
        }
    }else if(anti_top_state == NORMAL){
        sendBoxPosition(shoot);
    }


    last_orient = orientation;
}

