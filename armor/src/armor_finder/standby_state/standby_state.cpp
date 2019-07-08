//
// Created by xinyang on 19-3-27.
//

#include <armor_finder/armor_finder.h>

bool ArmorFinder::stateStandBy() {
    state = SEARCHING_STATE;
    return true;
}

