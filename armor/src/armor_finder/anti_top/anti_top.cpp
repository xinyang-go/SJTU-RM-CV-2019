//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>

static double getTimeIntervalms(const timeval& now, const timeval &last){
    return (now.tv_sec-last.tv_sec)*1000.0 + (now.tv_usec-last.tv_usec)/1000.0;
}

void ArmorFinder::antiTop() {
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
    if(orientation!=last_orient){
        timeval curr_time;
        gettimeofday(&curr_time, nullptr);
        auto interval = getTimeIntervalms(curr_time, last_switch_time);
        cout << interval << endl;
        if(50 < interval && interval < 700){
            anti_top_cnt++;
        }else{
            anti_top_cnt = 0;
        }
        last_switch_time = curr_time;
    }else{
        timeval curr_time;
        gettimeofday(&curr_time, nullptr);
        if(getTimeIntervalms(curr_time, last_switch_time) > 700) {
            anti_top_state = NORMAL;
        }
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

