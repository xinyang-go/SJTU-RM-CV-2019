//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>
#include <show_images/show_images.h>
#include <options.h>
#include <log.h>

bool ArmorFinder::stateSearchingTarget(cv::Mat &src) {
    if(findArmorBox(src, armor_box)){
        return true;
    }else{
        armor_box = ArmorBox();
        return false;
    }
}
