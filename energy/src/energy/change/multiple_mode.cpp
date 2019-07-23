//
// Created by sun on 19-7-23.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;

void Energy::multipleMode(cv::Mat gimbal_src) {
    if (is_predicting) {
        getPredictPoint(target_point);
        getAimPoint(predict_point);
        judgeShootInGimbal();
        sendEnergy();
    } else if (is_guessing && stayGuessing()) {
        findFans(gimbal_src);
        if (show_energy)showFans("fans", gimbal_src);
        if (save_mark)writeDownMark();
        guessTarget();
        if (show_energy)showGuessTarget("guess", gimbal_src);
        getPredictPoint(guess_point);
        getAimPoint(predict_point);
        sendEnergy();
    }
}