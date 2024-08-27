#include <stdio.h>
#include <bits/types.h>
#include <time.h>
#include <string.h>
#include <stdint.h>

static void _test_1()
{
    time_t rawtime;
    struct tm *info;
    char buffer[32] = {0};
    printf("%d rawtime:%ld\r\n", __LINE__, rawtime);
    time(&rawtime);
    printf("%d rawtime:%ld\r\n", __LINE__, rawtime);
    info = localtime(&rawtime);
    if (info) {
        strftime(buffer, sizeof(buffer), "%b %d %H:%M:%S", info);
        printf("[%s][%d]buffer:%s\r\n", __func__, __LINE__, buffer);
    }

    int offset_hours = info->tm_gmtoff / 3600;

    if (offset_hours > 0) {
        printf("东%d时区\n", offset_hours);
    } else if (offset_hours < 0) {
        printf("西%d时区\n", -offset_hours);
    } else {
        printf("未知时区\n");
    }

    printf("info->tm_zone:%s\r\n", info->tm_zone);
    printf("info->tm_gmtoff:%ld\r\n", info->tm_gmtoff);
    printf("info->tm_isdst:%d\r\n", info->tm_isdst);
    printf("%s\r\n", buffer);
}

static int _localtime_usage(void)
{
    int ret = 0;

    time_t rawtime;

    struct tm *info;

    time( &rawtime );

    info = localtime(&rawtime);

    char buffer[32] = {0};

    if (info) {
        strftime(buffer, sizeof(buffer), "%b %d %H:%M:%S", info);
        printf("[%s][%d]buffer:%s\r\n", __func__, __LINE__, buffer);
    
        printf("current local time :\r\n %s", asctime(info));
    }

    return ret;
}

int main()
{
    _localtime_usage();
    // _test_1();
}