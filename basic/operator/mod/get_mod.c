#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

static int _test_02() {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    int num = 12;
    int arr[12] = {0};

    for (int i = 0; i < num; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < num; i++) {
        // if ((i & 0x07) == 0) {
        //     printf("\r\n");
        // }
        if (!(i & 0x01)) {
            printf("\r\n");
        }
        if (i % 2 == 0) {
            printf("\r\n");
        }
        printf("%.4x\t", i);
    }
    printf("\r\n");
}

int main() {
    _test_02();

    return 0;
}
