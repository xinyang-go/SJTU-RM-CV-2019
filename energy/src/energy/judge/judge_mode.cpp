//
// Created by sun on 19-7-12.
//

#include "energy/energy.h"
#include "log.h"

using namespace std;
using namespace cv;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于判断大小符
// ---------------------------------------------------------------------------------------------------------------------
void Energy::JudgeMode() {
    getRecentTargetArmorCenters();
    if (recent_target_armor_centers.size() < 30) {
        return;
    } else {
        if (abs(recent_target_armor_centers.back() - recent_target_armor_centers.front()) > 10) {
            if(last_mode!=BIG){
                isBig = true;
                isSmall = false;
                energy_mode_init = false;
                LOGM(STR_CTR(WORD_CYAN,"start big!"));
            }
            last_mode = BIG;
        } else {
            if(last_mode!=SMALL){
                isBig = false;
                isSmall = true;
                energy_mode_init = false;
                LOGM(STR_CTR(WORD_GREEN,"start small!"));
            }
            last_mode = SMALL;
        }
    }
}