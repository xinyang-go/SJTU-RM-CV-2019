//
// Created by xinyang on 19-7-13.
//

#include <armor_finder/armor_finder.h>
#include <log.h>

ArmorBox::ArmorBox(const cv::Rect &pos, const LightBlobs &blobs, uint8_t color, int i) :
rect(pos), light_blobs(blobs), box_color(color), id(i){};

double ArmorBox::blobsDistance() const{
    if(light_blobs.size() == 2){
        auto &x = light_blobs[0].rect.center;
        auto &y = light_blobs[1].rect.center;
        return sqrt((x.x-y.x)*(x.x-y.x) + (x.y-y.y)*(x.y-y.y));
    }else{
        return 0;
    }
}

double ArmorBox::lengthRatio() const{
    if(light_blobs.size() == 2){
        return light_blobs[0].length / light_blobs[1].length < 1 ?
               (light_blobs[0].length / light_blobs[1].length) :
               (light_blobs[1].length / light_blobs[0].length);
    }else{
        return 0;
    }
}

double ArmorBox::lengthDistanceRatio() const {
    if(light_blobs.size() == 2){
        return max(light_blobs[0].length, light_blobs[1].length)
               / blobsDistance();
    }else{
        return 100;
    }
}
