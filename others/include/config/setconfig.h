#ifndef _SETCONFIG_H_
#define _SETCONFIG_H_

#ifdef WITH_CONFIG
    #include <config/config.h>
#else
    #warning "Without config.h"
    #define ARMOR_CAMERA_GAIN   (30)
    #define ENERGY_CAMERA_GAIN  (20)
//    #define GIMBAL_FLIP_MODE    (-1)
//    #define CHASSIS_FLIP_MODE   (-1)
#endif

#endif /* SETCONFIG_H */
