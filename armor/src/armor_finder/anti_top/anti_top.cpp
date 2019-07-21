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
    uint16_t shoot_delay = 0;
    timeval curr_time;
//    if(anti_top_state == ANTI_TOP){
//        cout << "anti top" << endl;
//    }else if(anti_top_state == NORMAL){
//        cout << "Normal" << endl;
//    }
    gettimeofday(&curr_time, nullptr);
    auto interval = getTimeIntervalms(curr_time, last_front_time);
    if(interval > 700){
        anti_top_state = NORMAL;
        anti_top_cnt = 0;
    }
    
    ArmorBox::BoxOrientation orientation = armor_box.getOrientation();
    if(orientation == ArmorBox::UNKNOWN){
        if(anti_top_state == NORMAL){
            sendBoxPosition(shoot_delay);
        }
        return;
    }


    if(orientation!=last_orient && orientation==ArmorBox::FRONT){
        last_front_time = curr_time;
        if(150<interval && interval<700){
            if(anti_top_state == ANTI_TOP){
                last_top_periodms = top_periodms;
                top_periodms = interval;
                LOGM(STR_CTR(WORD_LIGHT_GREEN, "top period: %.1lf ms"), top_periodms);
                shoot_delay = (last_top_periodms+top_periodms)/2.0-110;
                last_orient = orientation;
            }else if(anti_top_state == NORMAL){
//                LOGM("interval:%.1lf", interval);
                if(++anti_top_cnt > 4){
                    anti_top_state = ANTI_TOP;
                }
            }
        }
    }

    if(anti_top_state == ANTI_TOP){
        if(orientation == ArmorBox::FRONT){
            sendBoxPosition(shoot_delay);
        }
    }else if(anti_top_state == NORMAL){
        sendBoxPosition(shoot_delay);
    }

    last_orient = orientation;
}

