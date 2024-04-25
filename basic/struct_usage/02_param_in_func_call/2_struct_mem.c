#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void test_app(uint8_t *data, uint16_t len);
static void test_2();
static void test_3();

static void test_3()
{
    struct {
        uint8_t result;
        uint32_t timestamp;
        uint8_t get_tz_result;
        uint8_t ew_timezone_flag;
        uint8_t tz;
        uint8_t dst;
        uint32_t dst_start_ts;
        uint32_t dst_end_ts;
    } __attribute__((packed)) rsp;

    // uint32_t times = 1609430903;
    uint32_t times = 1609459245;
    uint8_t buf[4] = {0};

    buf[0] = times >> 24;
    buf[1] = times >> 16;
    buf[2] = times >> 8;
    buf[3] = times;

    // buf[0] = times;
    // buf[1] = times >> 8;
    // buf[2] = times >> 16;
    // buf[3] = times >> 24;

    for (int i = 0;i < 4; i++) {
        printf("buf:%02X\r\n", buf[i]);
    }

    return ;
}

static void test_2() {

    uint8_t data[] = {0x01, 0x02, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};
    uint16_t len = sizeof(data) / sizeof(data[0]);

    test_app(data, len);
}

static void test_app(uint8_t *data, uint16_t len) {
    if (!data || !len) {
        printf("param err\r\n");
        return ;
    }

    typedef struct {
        uint8_t short_keep_alive_time;
        uint8_t lock_deep_sleep;
        uint8_t reserved[8];
    } __attribute__((packed)) res_t;


    res_t res = {0};
    size_t offset = 0;

    res.short_keep_alive_time = *data;
    offset += sizeof(uint8_t);

    memcpy(&res.lock_deep_sleep, data + offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    memcpy(&res.reserved, data + offset, sizeof(res.reserved));
    offset += sizeof(res.reserved);

    printf("res.short_keep_alive_time:%d\r\n", res.short_keep_alive_time);
    printf("res.lock_deep_sleep:%d\r\n", res.lock_deep_sleep);

    for (int i = 0;i < 8; i++) {
        printf("res.reserved[%d]:%d \r\n", i, res.reserved[i]);
    }

}

static void test() {
    struct {
        uint8_t result;
        uint32_t timestamp;
        uint8_t get_tz_result;
        uint8_t ew_timezone_flag;
        uint8_t tz;
        uint8_t dst;
        uint32_t dst_start_ts;
        uint32_t dst_end_ts;
    }__attribute__((packed)) rsp;

    uint8_t res = 0x01;
    uint32_t ts = 0x12345678;
    uint8_t tz_result = 0x01;
    uint8_t tz = 0x01;
    uint8_t dst = 0x01;
    uint8_t ew_timezone_flag = 0x01;

    uint32_t dst_start_ts = 0x12345678;
    uint32_t dst_end_ts = 0x12345678;

    rsp.result = res;
    rsp.timestamp = ts;
    rsp.get_tz_result = tz_result;
    rsp.ew_timezone_flag = ew_timezone_flag;
    rsp.tz = tz;
    rsp.dst = dst;
    rsp.dst_start_ts = dst_start_ts;
    rsp.dst_end_ts = dst_end_ts;

    uint8_t *ptr = (uint8_t *)&rsp;
    for (int i = 0; i < sizeof(rsp); i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\r\n");

    return ;
}

int main() {
    // test();
    // test_2();
    test_3();
}