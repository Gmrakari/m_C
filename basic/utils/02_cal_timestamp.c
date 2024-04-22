#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t res = 0;

    int arr_dec[4] = {95, 237, 247, 119};
    // int arr_hex[4] = {0x5F, 0xED, 0xF7, 0x77};
    // int arr_hex[4] = {0x2D, 0x66, 0xEE, 0x5F};
    int arr_hex[4] = {0x5F, 0xEE, 0x66, 0x2D};

    // 5f ee 67 01
    int arr[] = {0x5f, 0xee, 0x67, 0x01};

    // res = arr_hex[0] * 256 * 256 * 256 + arr_hex[1] * 256 * 256 + arr_hex[2] * 256 + arr_hex[3];

    res = arr[0] * 256 * 256 * 256 + arr[1] * 256 * 256 + arr[2] * 256 + arr[3];

    printf("res:%d\r\n", res);
}
