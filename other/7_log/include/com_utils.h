#ifndef __COM_UTILS_H
#define __COM_UTILS_H

#include <time.h>      // time_t

typedef enum {
    TIMEZONE_UTC = 0,
    TIMEZONE_LOCAL, 
    TIMEZONE_CN,
    // TODO ADD...其他时区
} timezone_t;

/* 
** @ref :时间戳转换成tm结构体时间
** @in  :time_t timestamp
** @out :struct tm *
*/
struct tm *timestamp_2_tm(const time_t *timestamp, timezone_t tz);

#endif // __COM_UTILS_H
