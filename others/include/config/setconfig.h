// 本文件定义了在不同步兵车辆上运行时需要根据车辆情况而发生变化的参数
// 以下所有参数都给定了默认值，如果想要修改，推荐在该文件目录下新建文件config.h，并在config.h中写定自定义参数

#ifndef _SETCONFIG_H_
#define _SETCONFIG_H_


#ifdef WITH_CONFIG
    #include <config/config.h>
#else
    #warning "Without config.h"
#endif

#ifndef ARMOR_CAMERA_EXPOSURE
    #define ARMOR_CAMERA_EXPOSURE     (10)
#endif

#ifndef ENERGY_CAMERA_EXPOSURE
    #define ENERGY_CAMERA_EXPOSURE         (10)
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
    #define ARMOR_CAMERA_GAIN   (64)
#endif
#ifndef ENERGY_CAMERA_GAIN
    #define ENERGY_CAMERA_GAIN  (30)
#endif

#ifndef YAW_AIM_KD
    #define YAW_AIM_KD (0.4)
#endif
#ifndef YAW_AIM_KP
    #define YAW_AIM_KP (0.75)
#endif
#ifndef YAW_AIM_KI
    #define YAW_AIM_KI (0.01)
#endif
#ifndef PITCH_AIM_KD
    #define PITCH_AIM_KD (0.4)
#endif
#ifndef PITCH_AIM_KP
    #define PITCH_AIM_KP (0.75)
#endif
#ifndef PITCH_AIM_KI
    #define PITCH_AIM_KI (0.01)
#endif

#ifndef RED_COMPENSATE_YAW
    #define RED_COMPENSATE_YAW (5)
#endif
#ifndef RED_COMPENSATE_PITCH
    #define RED_COMPENSATE_PITCH (74)
#endif

#ifndef BLUE_COMPENSATE_YAW
    #define BLUE_COMPENSATE_YAW (5)
#endif
#ifndef BLUE_COMPENSATE_PITCH
    #define BLUE_COMPENSATE_PITCH (74)
#endif

#ifndef EXTRA_DELTA_X
    #define EXTRA_DELTA_X (0)
#endif
#ifndef EXTRA_DELTA_Y
    #define EXTRA_DELTA_Y (10)
#endif

//#define GIMBAL_FLIP_MODE    (-1)
//#define CHASSIS_FLIP_MODE   (-1)
//#define WITH_TIME_BASED_CAMERA_GAIN
#define WITH_COUNT_FPS

#endif /* SETCONFIG_H */
