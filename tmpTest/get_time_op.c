#include <stdio.h>
#include <bits/types.h>
#include <time.h>

static char format_time_str[32];

char *get_cur_time()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    time_t cur_time_stamp = time(0);
    printf("cur_time_stamp:%ld\r\n", cur_time_stamp);
    cur_time_stamp += 3600*8;
    struct tm *tm_time = gmtime(&cur_time_stamp);
    strftime(format_time_str, sizeof(format_time_str), "%Y-%m-%d %H:%M:%S", tm_time);
    printf("format_time_str:[%s]\r\n", format_time_str);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return format_time_str;
}

char *get_cur_time_snprintf()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    time_t cur_time_stamp = time(0);
    printf("cur_time_stamp:%ld\r\n", cur_time_stamp);

    cur_time_stamp += 3600*8;

    struct tm *tm_time = gmtime(&cur_time_stamp);

    snprintf(format_time_str, sizeof(format_time_str), "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", 1900 + tm_time->tm_year, 1 + tm_time->tm_mon, tm_time->tm_mday, tm_time->tm_hour, tm_time->tm_min, tm_time->tm_sec);

    printf("format_time_str:[%s]\r\n", format_time_str);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return format_time_str;
}

void get_cur_time_non()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    time_t cur_time_stamp = time(0);
    printf("cur_time_stamp:%ld\r\n", cur_time_stamp);

    cur_time_stamp += 3600*8;

    struct tm *tm_time = gmtime(&cur_time_stamp);

    char format_time[32] = {0};

    strftime(format_time, sizeof(format_time), "%Y-%m-%d %H:%M:%S", tm_time);
    printf("format time:[%s]\r\n", format_time);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return ;

}

int calc_char() {

}

int main(int argc, char const *argv[]) {
    // get_cur_time_non();

    char *str = get_cur_time();
    printf("str:%s\r\n", str);

    printf("\r\n");

    sleep(1);

    char *snstr = get_cur_time_snprintf();
    printf("snstr:%s\r\n", snstr);
    
}
