#include <stdio.h>
#include <stdint.h> // uint8
#include <string.h> //strncpy

typedef struct {
    uint8_t data[4];
} in_param_t;

static in_param_t in_param = {0};

static void _print_arr_data(uint8_t arr[4])
{
    for (size_t __i = 0; __i < 4; __i++) {
        printf("arr[%d]:%d\r\n", (int)__i, arr[__i]);
    }
}

static void _uint8_arr()
{
    uint8_t arr[4] = {0xFA, 0xFF, 0xF0, 0x00};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    // strncpy(in_param.data, arr, len);
    memcpy(in_param.data, arr, len);

    _print_arr_data(in_param.data);
}

static void _test_app()
{
    _uint8_arr();
}

int main() {
    _test_app();
    return 0;
}
