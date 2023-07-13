#include <time.h>      // time_t
#include <stdint.h>    // uint8/16/32/64...
#include "com_utils.h"

#define SEC_PER_MINUTE           (60)
#define SEC_PER_HOUR             (3600)
#define SEC_PER_DAY              (86400)
#define SEC_PER_YEAR             (31536000)

static struct tm g_tm = {0};

struct tm *timestamp_2_tm(const time_t *timestamp, timezone_t tz)
{
    // TODO 只处理了TIMEZONE_CN，其它待处理
    time_t seconds = *timestamp;
    switch (tz) {
        case TIMEZONE_UTC:
            break;
        case TIMEZONE_CN:
            seconds += 28800;
            break;
        default:
        break;
    }
    struct tm *cur_tm = &g_tm;
    cur_tm->tm_year = 1970;

    // 计算年份
    if (seconds < 0) {
        while (seconds < 0) {
            if ((cur_tm->tm_year % 4 == 0 && cur_tm->tm_year %100 != 0) || cur_tm->tm_year % 400 == 0) {
                seconds += (SEC_PER_YEAR + SEC_PER_DAY);
            } else {
                seconds += SEC_PER_YEAR;
            }
            cur_tm->tm_year--;
        }
    } else {
        while (seconds >= SEC_PER_YEAR) {
            if ((cur_tm->tm_year % 4 == 0 && cur_tm->tm_year %100 != 0) || cur_tm->tm_year % 400 == 0) {
                seconds -= (SEC_PER_YEAR + SEC_PER_DAY);
            } else {
                seconds -= SEC_PER_YEAR;
            }
            cur_tm->tm_year++;
        }
    }

    if (cur_tm->tm_year > 9999) {
        return NULL;
    }

    // 计算月份
    int8_t month_lengths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((cur_tm->tm_year % 4 == 0 && cur_tm->tm_year %100 != 0) || cur_tm->tm_year % 400 == 0)
        month_lengths[1] = 29;

    cur_tm->tm_mon = 0;
    while (seconds >= month_lengths[cur_tm->tm_mon] * SEC_PER_DAY) {
        seconds -= month_lengths[cur_tm->tm_mon] * SEC_PER_DAY;
        cur_tm->tm_mon++;
    }

    // 计算day
    cur_tm->tm_mday = seconds / SEC_PER_DAY + 1;

    // seconds 
    seconds = seconds % SEC_PER_DAY;

    // 计算小时、分钟、秒钟
    cur_tm->tm_hour = (seconds % SEC_PER_DAY) / SEC_PER_HOUR;
    cur_tm->tm_min = (seconds % SEC_PER_HOUR) / SEC_PER_MINUTE;
    cur_tm->tm_sec = seconds % SEC_PER_MINUTE;

    int8_t weekday = 0;
    weekday = weekday = ((*timestamp) / SEC_PER_DAY + 4) % 7;
    cur_tm->tm_wday = weekday % 7;

    // 计算一年中的日期 [0,365], 其中0表示1月1日
    int16_t year_day = 0;
    for (int i = 0; i < cur_tm->tm_mon; i++) {
        year_day += month_lengths[i];
    }
    year_day += cur_tm->tm_mday - 1;
    cur_tm->tm_yday = year_day;

    // 是否表示夏令时
    cur_tm->tm_isdst = -1;  // 不了解夏令时情况:-1, 不实行:0, 实行:1

    return cur_tm;
}
