#include <stdio.h>
#include <stdint.h>

static void test_2()
{
    uint32_t ts = 1708497559;
    uint8_t data[4] = {0};

    data[0] = ts & 0xFF;
    data[1] = (ts >> 8) & 0xFF;
    data[2] = (ts >> 16) & 0xFF;
    data[3] = (ts >> 24) & 0xFF;

    uint32_t timestamp = 0;

    timestamp = ((uint32_t)data[3] << 24) |
                ((uint32_t)data[2] << 16) |
                ((uint32_t)data[1] << 8)  |
                ((uint32_t)data[0]);
        
    printf("%02X %02X %02X %02X\r\n", data[0], data[1], data[2], data[3]);
    printf("%04X\r\n", ts);
    printf("%04X\r\n", timestamp);
}

static void test_03() {
    uint16_t len = 0x0004;
    uint8_t buf[2] = {0};

    buf[0] = (len >> 8) & 0xFF;
    buf[1] = len & 0xFF;

    printf("%02X\r\n", buf[0]);
    printf("%02X\r\n", buf[1]);
}

int main()
{
    // test_2();

    test_03();
}