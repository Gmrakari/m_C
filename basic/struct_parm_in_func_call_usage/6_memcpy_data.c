#include <stdio.h>
#include <string.h>
#include <stdint.h>

static void test01()
{

    typedef struct {
        uint8_t time_type;
        uint8_t year;
        uint8_t month;
        uint8_t day;
        uint8_t hour;
        uint8_t minutes;
        uint8_t seconds;
    } __attribute__((packed)) res_t;

    typedef struct {
        uint8_t id;
        uint8_t type;
        uint8_t len;
        uint8_t *value;
    } __attribute__((packed)) res_dp_t;

    res_t res = {0};
    res_dp_t dp = {0};

    // uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x01, 0x00, 0x01, 0x01};
    uint8_t data1[] = {0x01,0x12,0x04,0x13,0x0D,0x03,0x1D,0x6D,0x01,0x00,0x01,0x01};
    uint8_t data2[] = {0x02,0x12,0x04,0x13,0x05,0x03,0x1D,0x6D,0x01,0x00,0x01,0x01};

    // memcpy(&res, data1, sizeof(res));
    memcpy(&res, data2, sizeof(res));

    printf("res_time_type:%d\r\n", res.time_type);
    printf("res year: 20%d\r\n", res.year);
    printf("res month: %d\r\n", res.month);
    printf("res day: %d\r\n", res.day);    
    printf("res hour: %d\r\n", res.hour);
    printf("res minutes: %d\r\n", res.minutes);
    printf("res seconds: %d\r\n", res.seconds);
}

int main()
{
    test01();
}