//
// Created by xinyang on 19-7-31.
//

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

typedef struct{
    int second;
    int millisecond;
} systime;

void getsystime(systime &t);

#if defined(Linux) || defined(Darwin)
    #include <sys/time.h>
#elif defined(Windows)
    #include <Windows.h>
#else
    #error "nonsupport platform."
#endif

#endif /* _PLATFORM_H_ */
