#include <stdio.h>
#include <stdint.h> // uint8

static void _print_hex(uint8_t *data, size_t len)
{
    for (size_t i = len; i > 0; i--)
    {
        printf("%02x ",data[i - 1]);
    }
    printf("\r\n");
}

int main()
{
    uint16_t x_data = 320;
    uint16_t y_data = 240;
    uint32_t data = 65535;
    size_t len = sizeof(uint16_t);

    uint8_t *ptr = &x_data;

    printf("x_data:%d ", x_data);
    _print_hex(ptr, len);

    ptr = &y_data;
    printf("y_data:%d ",y_data);
    _print_hex(ptr, len);

    ptr = &data;
    len = sizeof(data);
    _print_hex(ptr, len);
}