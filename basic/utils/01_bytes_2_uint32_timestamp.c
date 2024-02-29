#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <bits/types.h>
#include <math.h>

// compile:
// gcc -Wall -Wextra -std=c99 -o app 01_bytes_2_uint32_timestamp.c -lm

double pow(double x, double y);

static int _hex_to_timestamp(unsigned char *data, size_t len, uint32_t *ts)
{
    if (!data || !len)
        return 0;

    int ret = 0;
    uint32_t res = 0;
    for (int i = 0; i < (int)len; i++)
        res += data[i] * pow(256, (int)len - i - 1);

    *ts = res;
    return ret;
}

static int _timestamp_to_str(uint32_t timestamp, char *str, size_t str_len)
{
    if (!str)
        return -1;

    int ret = 0;
    time_t ts = (time_t)timestamp;
    struct tm *tm_time = gmtime(&ts);
    strftime(str, str_len, "%Y-%m-%d %H:%M:%S", tm_time);

    return ret;
}

static int _test_01()
{
    int ret = 0;

    unsigned char hex_data[] = {0x5f, 0xee, 0x67, 0x01};
    size_t hex_data_len = sizeof(hex_data) / sizeof(hex_data[0]);

    uint32_t timestamp = 0;

    ret = _hex_to_timestamp(hex_data, hex_data_len, &timestamp);
    if (ret == 0)
        printf("timestamp:%d\r\n", timestamp);

    char format_time_str[32] = {0};
    ret = _timestamp_to_str(timestamp, format_time_str, sizeof(format_time_str) / sizeof(format_time_str[0]));
    if (ret == 0)
        printf("%s\r\n", format_time_str);

    return ret;
}

int main() {
    _test_01();

    return 0;
}
