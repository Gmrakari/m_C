#include <stdio.h>
#include <stdlib.h>    // malloc
#include <time.h>      // time_t
#include <stdint.h>    // uint8/16/32/64...

#define SEC_PER_MINUTE           (60)
#define SEC_PER_HOUR             (3600)
#define SEC_PER_DAY              (86400)
#define SEC_PER_YEAR             (31536000)

#define LOGI(format, ...) printf(format"\r\n" , ##__VA_ARGS__)

// 优化避免每次都申请一次内存
static struct tm g_tm;

// 时间戳，转换成tm结构体的时间，用完需要释放内存
static struct tm *timestamp_2_tm(const time_t *timestamp)
{
    struct tm *cur_tm = &g_tm;
    if (cur_tm == NULL) return NULL;
    cur_tm->tm_year = 1970;
    time_t seconds = *timestamp;

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

    if (cur_tm->tm_year > 9999)
        return NULL;

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

    #if 0
    // 使用Zellers Kongruenz 公式计算任何一日属一星期中哪一日
    int16_t year_of_century = cur_tm->tm_year % 100;
    int16_t century = cur_tm->tm_year / 100;
    int8_t month = cur_tm->tm_mon + 1;
    int16_t day = cur_tm->tm_mday;
    int8_t weekday = 0x00;
    if (month == 1 || month == 2) {
        year_of_century --;
        month += 12;
    }
    weekday = year_of_century + year_of_century / 4 + century / 4 - 2 * century + 13 * (month + 1) / 5 + day - 1;
    #endif

    int8_t weekday = 0x00;
    weekday = ((*timestamp) / SEC_PER_DAY + 4) % 7;
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

static void print_tm(struct tm *cur_st_time)
{
    LOGI("%04d-%02d-%02d %02d:%02d:%02d", cur_st_time->tm_year, cur_st_time->tm_mon + 1, cur_st_time->tm_mday,
                                                cur_st_time->tm_hour, cur_st_time->tm_min, cur_st_time->tm_sec);
    LOGI("tm_wday:%d", cur_st_time->tm_wday);
    LOGI("tm_yday:%d", cur_st_time->tm_yday);
    LOGI("tm_isdst:%d", cur_st_time->tm_isdst);

    LOGI("tm_wday:%d", cur_st_time->tm_wday);
    LOGI("");
}

static void testcase()
{
    // 1687252396
    // 2023-06-20 17:13:16

    // 1687315372
    // 2023-06-21 10:42:52

    // time_t time_stamp = time(NULL);
    // struct tm *m_cur_time = timestamp_2_tm(time_stamp);

    time_t timestamp_list[] = {1687252396, 1687315372};
    size_t len = sizeof(timestamp_list) / sizeof(timestamp_list[0]);

    struct tm *m_cur_time = NULL;

    for (int i = 0; i < len; i++) {
        m_cur_time = timestamp_2_tm(&timestamp_list[i]);
        if (m_cur_time != NULL) {
            print_tm(m_cur_time);

        }
    }
    return ;
}

int main() {
    testcase();
}