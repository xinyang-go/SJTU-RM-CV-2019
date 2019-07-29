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

#ifndef CAMERA_RED_GAIN
    #define CAMERA_RED_GAIN     (100)
#endif

#ifndef CAMERA_GREEN_GAIN
    #define CAMERA_GREEN_GAIN   (100)
#endif

#ifndef CAMERA_BLUE_GAIN
    #define CAMERA_BLUE_GAIN    (100)
#endif


#ifndef ARMOR_CAMERA_GAIN
    #define ARMOR_CAMERA_GAIN   (30)
#endif
#ifndef ENERGY_CAMERA_GAIN
    #define ENERGY_CAMERA_GAIN  (30)
#endif
#ifndef AIM_KP
    #define AIM_KP (6)
#endif
#ifndef AIM_KI
    #define AIM_KI (0.1)
#endif
#ifndef COMPENSATE_YAW
    #define COMPENSATE_YAW (5)
#endif
#ifndef COMPENSATE_PITCH
    #define COMPENSATE_PITCH (74)
#endif
#ifndef EXTRA_DELTA_X
    #define EXTRA_DELTA_X (10)
#endif
#ifndef EXTRA_DELTA_Y
    #define EXTRA_DELTA_Y (10)
#endif

//#define GIMBAL_FLIP_MODE    (-1)
//#define CHASSIS_FLIP_MODE   (-1)
//#define WITH_TIME_BASED_CAMERA_GAIN
#define WITH_COUNT_FPS

#endif /* SETCONFIG_H */
