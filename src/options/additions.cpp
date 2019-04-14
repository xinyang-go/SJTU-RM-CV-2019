//
// Created by xinyang on 19-4-7.
//

#include <options/additions.h>
#include <options/options.h>
#include <stdio.h>
#include <log.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

#define VIDEO_SAVE_DIR "/home/sjturm/Desktop/video/"

static cv::VideoWriter *create_video_writer(){
    FILE* info = fopen(VIDEO_SAVE_DIR"info.txt", "r");
    int cnt=0;
    fscanf(info, "%d", &cnt);
    fclose(info);
    info = fopen(VIDEO_SAVE_DIR"info.txt", "w");
    fprintf(info, "%d", ++cnt);

    char name[100];
    sprintf(name, VIDEO_SAVE_DIR"%d.avi", cnt);
    return new cv::VideoWriter(name, cv::VideoWriter::fourcc('P','I','M','1'), 80, cv::Size(640,480),false);
}

void save_video_file(cv::Mat &src){
    static cv::VideoWriter *video = create_video_writer();
    video->write(src);
}

#define SAVE_DIR "/home/sjturm/Desktop/labelled/"

int get_labelled_cnt(){
    FILE *fp = fopen(SAVE_DIR"info.txt", "r");
    int cnt=0;
    fscanf(fp, "%d", &cnt);
    fclose(fp);
    return cnt+1;
}

void save_labelled_cnt(int cnt){
    FILE *fp = fopen(SAVE_DIR"info.txt", "w");
    fprintf(fp, "%d", cnt);
    fclose(fp);
}

void save_labelled_image(cv::Mat &src, cv::Rect2d box){
    static int cnt=get_labelled_cnt();
    char name[50];
    sprintf(name, SAVE_DIR"%d.jpg", cnt);
    cv::imwrite(name, src);
    sprintf(name, SAVE_DIR"%d.txt", cnt);
    FILE *fp = fopen(name, "w");
    if(fp == NULL){
        LOGW("Can't create file: %s!\nStop saving!", name);
        save_labelled = false;
        return;
    }
    fprintf(fp, "%lf %lf %lf %lf\n", box.x, box.y, box.width, box.height);
    fclose(fp);
    save_labelled_cnt(cnt);
}
