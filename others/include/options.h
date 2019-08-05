//
// Created by xinyang on 19-3-27.
//

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#ifdef PATH
    #define PROJECT_DIR PATH
#else
    #define PROJECT_DIR ""
#endif

extern bool show_armor_box;
extern bool show_armor_boxes;
extern bool show_light_blobs;
extern bool show_origin;
extern bool run_with_camera;
extern bool save_video;
extern bool wait_uart;
extern bool save_labelled_boxes;
extern bool show_process;
extern bool show_energy;
extern bool save_mark;
extern bool show_info;

void processOptions(int argc, char **argv);

#endif /* _OPTIONS_H_ */
