#include <stdio.h>
#include <stdint.h>

/**
 * 位的操作
** uint16_t a = 0xffffffff;
** 清0
** 11111111 11111101
** 00000000 00000010
** 11111111 11111101
** xxxxxxxx xxxxxx?x
** 置位
** 00000000 00000000
** 00000000 00000010
** &
** |
** a = a & (~0x10);
** a = a | 0x10;

*/

int main() {
    uint16_t op = -1;
                // 10 00 00 00 00;
    printf("op:%hu\r\n", op);

    op &= (~0x1);
    printf("op:%hd\r\n", op);
    printf("op:%hx\r\n", op);
    printf("op:%hu\r\n", op);


    // op &= (~0x10);
    // op &= (~0x100);
    // op &= (~0x1000);
    // op &= (~0x10000);
    // op &= (~0x100000);
    // op &= (~0x1000000);

    printf("op:%x\r\n", op);
    int cnt = 0;
    while (op) {
        if (op & 1 == 1) {
            cnt++;
            // printf("has one\r\n");
        }
        op = op >> 1;
    }
    printf("op:%x cnt:%d\r\n", op, cnt);


}