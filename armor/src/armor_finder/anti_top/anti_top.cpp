//
// Created by xinyang on 19-7-15.
//

#include <armor_finder/armor_finder.h>

#define         B1 1
#define         B2 2
#define         B3 3
#define         B4 4
#define         B5 5
#define         B7 6
#define         B8 7
#define         R1 8
#define         R2 9
#define         R3 10
#define         R4 11
#define         R5 12
#define         R7 13
#define         R8 14


void ArmorFinder::anti_top() {
//    switch (armor_box.id) {
//        case R1:
//        case R7:
//        case B1:
//        case B7:
//            if (armor_box.rect != cv::Rect2d()) {
//                sendBoxPosition();
//            }
//        case R2:
//        case R3:
//        case R4:
//        case R5:
//        case B2:
//        case B3:
//        case B4:
//        case B5:
//            if (armor_box.rect != cv::Rect2d()) {
//                sendBoxPosition();
//            }
//        default:
//            if (armor_box.rect != cv::Rect2d()) {
//                sendBoxPosition();
//            }
//    }
    if (armor_box.rect != cv::Rect2d()) {
        sendBoxPosition();
    }
}

