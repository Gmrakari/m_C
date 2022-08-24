
/*
** Func:struct timeval data use
** Date:2022-08-24 09:55
** filename:struct_timeval_usage.c
*/

#include <stdio.h>
#include <sys/time.h>

// #include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz);

// @ret  : 成功时候返回0,失败的时候返回-1
// @parm :
// struct timeval
// {
// __time_t tv_sec;        /* Seconds. */
// __suseconds_t tv_usec;  /* Microseconds. */
// };

// struct timezone {
//     int tz_minuteswest;     /* 和Greenwich时间差了多少分钟 */
//     int tz_dsttime;         /* 日光节约时间的状态 */
// };

//

void _struct_timeval_func_member_use_func()
{
    int ret = -2;
    printf("使用struct timeval结构体，获取秒和微妙时间\r\n");
    struct timeval t_now;

    ret = gettimeofday(&t_now, NULL);
    if (ret == -1)
    {
        printf("gettimeofday failed!\r\n");
        return;
    }
    printf("second(t_now.tv_sec):%ld\r\n", t_now.tv_sec);
    printf("millisecond(t_now.tv_usec * 1000 + t_now.tv_usec / 1000):%ld\r\n", t_now.tv_usec * 1000 + t_now.tv_usec / 1000);
    printf("microsecond:(t_now.tv_sec * 1000 * 1000 + t_now.tv_usec):%ld\r\n", t_now.tv_sec * 1000 * 1000 + t_now.tv_usec);

    return;
}

void _struct_timeval_cal_different_time_func()
{
    int ret = -2;
    printf("使用两个struct timeval结构体,通过结束时间和开始时间,计算前后时间持续时长\r\n");
    struct timeval time_start;
    struct timeval time_end;

    unsigned long int t_differ_last;

    ret = gettimeofday(&time_start, NULL);
    if (ret == -1)
    {
        printf("gettimeofday failed!\r\n");
        return;
    }

    printf("time_start :%ld\r\n", time_start);

    sleep_func();

    ret = gettimeofday(&time_end, NULL);
    if (ret == -1)
    {
        printf("gettimeofday failed!\r\n");
        return;
    }
    printf("time_end :%ld\r\n", time_end);

    t_differ_last = (time_end.tv_sec - time_start.tv_sec) * 1000 + (time_end.tv_usec - time_start.tv_usec) / 1000;

    printf("t_differ_last(毫秒):%ld\r\n", t_differ_last);

    return;
}

void sleep_func()
{
    printf("start to sleep 2 seconds\r\n");
    sleep(2);
    return;
}

int main()
{
    printf("-------------------------------------------------------------\r\n");
    _struct_timeval_func_member_use_func();
    printf("-------------------------------------------------------------\r\n");
    _struct_timeval_cal_different_time_func();
    printf("-------------------------------------------------------------\r\n");
}