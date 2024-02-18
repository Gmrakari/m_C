#include <stdio.h>
#include <bits/types.h>
#include <time.h>
#include <string.h>

#include <stdint.h>

// time返回自纪元 Epoch（1970-01-01 00:00:00 UTC）起经过的时间，以秒为单位
static void test()
{
    struct {
        uint8_t result;             /* 获取时间结果标识 0x00：失败; 0x01：成功; */
        uint32_t timestamp;         /* unix 时间戳(大端）*/
        uint8_t tz_result;          /* 获取时区信息结果标识 0x00：失败; 0x01：成功; */
        uint8_t ew_tz;              /* 表示东/西时区 0x00: 东区; 0x01: 西区 */
        uint8_t tz;                 /* 具体时区信息 */
        uint8_t dst;                /* 是否有夏令时标识;  0x00：无夏令时; 0x01：有夏令时 */
        uint32_t dst_start_ts;      /* 进入夏令时时间戳（大端）*/
        uint32_t dst_end_ts;        /* 退出夏令时时间戳（大端）*/
    } __attribute__((packed)) rsp;  /* 17 Bytes */

    printf("rsp:%ld\r\n", sizeof(rsp));

    time_t t = time(NULL);
    printf("t1:%ld\r\n", t);

    t = time(NULL) + 8 * 60;

    printf("t2:%ld\r\n", t);
}

int main()
{
    test();
    return 0;
}
