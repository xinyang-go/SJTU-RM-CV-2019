#ifndef _SETCONFIG_H_
#define _SETCONFIG_H_


#ifdef WITH_CONFIG
    #include <config/config.h>
#else
    #warning "Without config.h"
#endif

#ifndef CAMERA_EXPOSURE
    #define CAMERA_EXPOSURE     (10)
#endif

#ifndef CAMERA_BLUE_GAIN
    #define CAMERA_BLUE_GAIN        (100)
#endif

#ifndef CAMERA_GREEN_GAIN
    #define CAMERA_GREEN_GAIN       (100)
#endif

#ifndef CAMERA_RED_GAIN
    #define CAMERA_RED_GAIN         (100)
#endif

#ifndef ARMOR_CAMERA_GAIN
    #define ARMOR_CAMERA_GAIN   (30)
#endif
#ifndef ENERGY_CAMERA_GAIN
    #define ENERGY_CAMERA_GAIN  (20)
#endif

//#define GIMBAL_FLIP_MODE    (-1)
//#define CHASSIS_FLIP_MODE   (-1)


#endif /* SETCONFIG_H */
