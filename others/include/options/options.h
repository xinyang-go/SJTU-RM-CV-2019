//
// Created by xinyang on 19-3-27.
//

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#ifdef FIX_OPTIONS
    #ifdef SHOW_ARMOR_BOX
        #define show_armor_box true
    #else
        #define show_armor_box false
    #endif

    #ifdef SHOW_ARMOR_BOXES
        #define show_armor_boxes true
    #else
        #define show_armor_boxes false
    #endif

    #ifdef SHOW_LIGHT_BLOBS
        #define show_light_blobs true
    #else
        #define show_light_blobs false
    #endif

    #ifdef SHOW_ORIGIN
        #define show_origin true
    #else
        #define show_origin false
    #endif

    #ifdef SAVE_LABELLED
        #define save_labelled true
    #else
        #define save_labelled false
    #endif

    #ifdef RUN_WITH_CAMERA
        #define run_with_camera true
    #else
        #define run_with_camera false
    #endif

    #ifdef SAVE_VIDEO
        #define save_video true
    #else
        #define save_video false
    #endif

    #ifdef COLLECT_DATA
        #define collect_data true
    #else
        #define collect_data false
    #endif
#else /* FIX_OPTIONS */
    extern bool show_armor_box;
    extern bool show_armor_boxes;
    extern bool show_light_blobs;
    extern bool show_origin;
    extern bool save_labelled;
    extern bool run_with_camera;
    extern bool save_video;
    extern bool collect_data;
#endif /* FIX_OPTIONS */

void process_options(int argc, char *argv[]);

#endif /* _OPTIONS_H_ */
