#ifndef _SETCONFIG_H_
#define _SETCONFIG_H_


#ifdef WITH_CONFIG
    #include <config/config.h>
#else
    #warning "Without config.h"
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
