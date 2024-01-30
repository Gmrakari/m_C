#include <stdio.h>
#include <stdint.h>

static uint8_t _get_checksum(const uint8_t *data, uint16_t len)
{
    uint8_t csum = 0;
    for (uint16_t i = 0; i < len; i++) 
        csum += data[i];
    return csum & 0xFF;
}

static void _test(void)
{
    uint8_t data[] = {0x55, 0xaa, 0x00, 0x02, 0x00, 0x00};

    size_t len = sizeof(data) / sizeof(data[0]);

    uint8_t checksum = _get_checksum(data, len);

    printf("checksum: %02X\r\n", checksum);
}

int main()
{
    _test();
}
