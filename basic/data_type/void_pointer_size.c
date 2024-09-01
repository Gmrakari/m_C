#include <stdio.h>
#include <stdint.h>

int main() {
    void *p = NULL;
    printf("sizeof(void *p):%d\r\n", sizeof(void*));
    printf("sizeof(p):%d\r\n", sizeof(p));

    uint32_t arr[] = {1, 2, 3, 4, 5};
    size_t arr_len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_len; i++) {
        if ((arr[i] & 0x01) == 0) {
            printf("%d %d\r\n", i, arr[i] & 1);
        }
    }
}