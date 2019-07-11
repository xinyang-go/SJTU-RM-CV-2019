//
// Created by sun on 19-7-5.
//

#include "energy/energy.h"

using namespace std;
using namespace cv;

void Energy::writeDownMark() {
    if(fans.size()>=3) {
        FILE *fp = fopen(PROJECT_DIR"/Mark/mark.txt", "w");
        if (fp) {
            fprintf(fp, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp);
            save_new_mark = true;
        }
        FILE *fp_all = fopen(PROJECT_DIR"/Mark/mark_all.txt", "a");
        if (fp_all) {
            fprintf(fp_all, "yaw: %f, pitch: %f\n", origin_yaw, origin_pitch);
            fclose(fp_all);
        }
    }
    if(fans.size()==4){
        FILE *fp_best = fopen(PROJECT_DIR"/Mark/mark_best.txt", "a");
        if(fp_best){
            fprintf(fp_best, "yaw: %f, pitch: %f\n",origin_yaw, origin_pitch);
            fclose(fp_best);
        }
    }
}