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

double ArmorBox::getDistance() const{
    if(light_blobs.size() == 2 ){
        return DISTANCE_HEIGHT / 2 / max(light_blobs[0].length, light_blobs[1].length);
    } else {
        return DISTANCE_HEIGHT / rect.height;
    }
}

ArmorBox::BoxOrientation ArmorBox::getOrientation() const{
//    cout << lengthDistanceRatio() << endl;
    if(light_blobs.size() != 2){
        return UNKNOWN;
    }
    switch (id) {
        case R1:
        case R7:
        case B1:
        case B7:
            if(lengthDistanceRatio() < 0.3){
                return FRONT;
            }else{
                return SIDE;
            }
        case R2:
        case R3:
        case R4:
        case R5:
        case B2:
        case B3:
        case B4:
        case B5:
            if (lengthDistanceRatio() < 0.43) {
                return FRONT;
            }else{
                return SIDE;
            }
        default:
            return UNKNOWN;
    }
}
