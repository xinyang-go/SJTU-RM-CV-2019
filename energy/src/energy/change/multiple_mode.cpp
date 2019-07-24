//
// Created by sun on 19-7-23.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;

void Energy::multipleMode(cv::Mat &src) {
    if (is_predicting) {
        getPredictPoint(target_point);
        getAimPoint(predict_point);
        judgeShootInGimbal();
        sendEnergy();
    } else if (is_guessing && stayGuessing()) {
        findFans(src);
        if (show_energy)showFans("fans", src);
        if (save_mark)writeDownMark(src);
        guessTarget();
        if (show_energy)showGuessTarget("guess", src);
        getPredictPoint(guess_point);
        getAimPoint(predict_point);
        sendEnergy();
    }
}