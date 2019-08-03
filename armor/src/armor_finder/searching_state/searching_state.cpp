//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>
#include <show_images/show_images.h>
#include <options.h>
#include <log.h>

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    if(anti_switch_cnt >= 3){
        last_box = ArmorBox();
    }
    if (findArmorBox(src, target_box)) {
        if (last_box.rect != cv::Rect2d() &&
            (getPointLength(last_box.getCenter() - target_box.getCenter()) > last_box.rect.height * 3.0) &&
            anti_switch_cnt++ < 3) {
            target_box = ArmorBox();
            return false;
        } else {
            last_box = target_box;
            anti_switch_cnt = 0;
            return true;
        }
    } else {
        target_box = ArmorBox();
        anti_switch_cnt++;
        return false;
    }
}
