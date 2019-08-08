//
// Created by sun on 19-7-5.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;

extern McuData mcu_data;


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于记录操作手的微调dx和dy
// ---------------------------------------------------------------------------------------------------------------------
void Energy::writeDownSlightChange(cv::Mat &src) {
    if (fans_cnt >= 2) {
        FILE *fp_delta = fopen(PROJECT_DIR"/Mark/delta.txt", "w");
        if (fp_delta) {
            fprintf(fp_delta, "delta_x: %d, delta_y: %d\n", mcu_data.delta_x + manual_delta_x,
                    mcu_data.delta_y + manual_delta_y);
            fclose(fp_delta);
        }
    }
    if(fans_cnt>=1){
        FILE *fp_data = fopen(PROJECT_DIR"/Mark/data.txt", "a");
        if (fp_data) {
            if(mcu_data.mark == 1){
                fprintf(fp_data, "PID: %s\t", "new");
            } else {
                fprintf(fp_data, "PID: %s\t", "default");
            }
            if(is_big){
                fprintf(fp_data, "state: %s\t", "big");
            } else if(is_small){
                fprintf(fp_data, "state: %s\t", "small");
            }
            fprintf(fp_data, "fps: %d\t", curr_fps);
            fprintf(fp_data, "fans_cnt: %d\t", fans_cnt);
            fprintf(fp_data, "yaw: %lf , pitch: %lf\t", yaw_rotation, pitch_rotation);
            fprintf(fp_data, "delta_x: %d, delta_y: %d\n", mcu_data.delta_x + manual_delta_x,
                    mcu_data.delta_y + manual_delta_y);
            fclose(fp_data);
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------
// 此函数用于记录操作手手动标定的初始对心角度
// ---------------------------------------------------------------------------------------------------------------------
void Energy::writeDownMark(cv::Mat &src) {
    if (findFans(src) >= 3) {
        FILE *fp = fopen(PROJECT_DIR"/Mark/mark.txt", "w");
        if (fp) {
            fprintf(fp, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp);
        }
        FILE *fp_all = fopen(PROJECT_DIR"/Mark/mark_all.txt", "a");
        if (fp_all) {
            fprintf(fp_all, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp_all);
        }
    }
    if (findFans(src) == 4) {
        FILE *fp_best = fopen(PROJECT_DIR"/Mark/mark_best.txt", "a");
        if (fp_best) {
            fprintf(fp_best, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp_best);
        }
    }
}