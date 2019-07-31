//
// Created by xinyang on 19-7-31.
//
#include <systime.h>

#if defined(Linux)

void getsystime(systime &t){
    timeval tv;
    gettimeofday(&tv, nullptr);
    t.second = tv.tv_sec;
    t.millisecond = tv.tv_usec/1000;
}

#elif defined(Windows)

void getsystime(systime &t){
    SYSTEMTIME tv;
    GetLocalTime(&tv);
    t.second = tv.wSecond;
    t.millisecond = tv.wMilliseconds;
}

#else
    #error "nonsupport platform."
#endif
