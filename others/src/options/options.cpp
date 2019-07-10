//
// Created by xinyang on 19-3-27.
//

#include <options/options.h>
#include <log.h>
#include <cstring>

bool show_armor_box = false;
bool show_armor_boxes = false;
bool show_light_blobs = false;
bool show_origin = false;
bool run_with_camera = false;
bool save_video = false;
bool wait_uart = false;
bool save_labelled_boxes = false;
bool show_bin = false;
bool show_split = false;
bool show_single = false;
bool show_both = false;
bool show_center = false;
bool show_strip = false;
bool write_down = false;

void process_options(int argc, char *argv[]) {
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "--help") == 0) {
                LOGM("--show-armor-box: show the aim box.");
                LOGM("--show-armor-boxes: show the candidate aim boxes.");
                LOGM("--show-light-blobs: show the candidate light blobs.");
                LOGM("--show-origin: show the origin image.");
                LOGM("--run-with-camera: start the program with camera directly without asking.");
                LOGM("--save-video: save the video.");
                LOGM("--save-labelled-boxes: save labelled armor boxes.");
            } else if (strcmp(argv[i], "--show-armor-box") == 0) {
                show_armor_box = true;
                LOGM("Enable show armor box");
            } else if (strcmp(argv[i], "--show-armor-boxes") == 0) {
                show_armor_boxes = true;
                LOGM("Enable show armor boxes");
            } else if (strcmp(argv[i], "--show-light-blobs") == 0) {
                show_light_blobs = true;
                LOGM("Enable show light blobs");
            } else if (strcmp(argv[i], "--show-origin") == 0) {
                show_origin = true;
                LOGM("Enable show origin");
            } else if (strcmp(argv[i], "--show-all") == 0) {
                show_armor_box = true;
                LOGM("Enable show armor box");
                show_armor_boxes = true;
                LOGM("Enable show armor boxes");
                show_light_blobs = true;
                LOGM("Enable show light blobs");
                show_origin = true;
                LOGM("Enable show origin");
                show_bin = true;
                LOGM("Enable show binary image");
                show_split = true;
                LOGM("Enable show split image");
                show_single = true;
                LOGM("Enable show single image");
                show_both = true;
                LOGM("Enable show both image");
                show_center = true;
                LOGM("Enable show circle center");
                show_strip = true;
                LOGM("Enable show strip");
            } else if (strcmp(argv[i], "--run-with-camera") == 0) {
                run_with_camera = true;
                LOGM("Run with camera!");
            } else if (strcmp(argv[i], "--save-video") == 0) {
                save_video = true;
                LOGM("Save video!");
            } else if (strcmp(argv[i], "--wait-uart") == 0) {
                wait_uart = true;
                LOGM("Wait uart until available!");
            } else if (strcmp(argv[i], "--save-labelled-boxes") == 0) {
                save_labelled_boxes = true;
                LOGM("labelled armor boxes will be saved!");
            } else if (strcmp(argv[i], "--show-bin") == 0) {
                show_bin = true;
                LOGM("Enable show binary image");
            } else if (strcmp(argv[i], "--show-split") == 0) {
                show_split = true;
                LOGM("Enable show split image");
            } else if (strcmp(argv[i], "--show-single") == 0) {
                show_single = true;
                LOGM("Enable show single image");
            } else if (strcmp(argv[i], "--show-both") == 0) {
                show_both = true;
                LOGM("Enable show both image");
            } else if (strcmp(argv[i], "--show-center") == 0) {
                show_center = true;
                LOGM("Enable show circle center");
            } else if (strcmp(argv[i], "--show-strip") == 0) {
                show_strip = true;
                LOGM("Enable show strip");
            } else if (strcmp(argv[i], "--save-mark") == 0) {
                write_down = true;
                LOGM("Write down mark");
            } else {
                LOGW("Unknown option: %s. Use --help to see options.", argv[i]);
            }
        }
    }
}
