#include <stdio.h>

int main()
{
    int val = 0;

    for (int i = 0; i < 10; i++) {
        if (!val) {
            val = 1;
        } else {
            val ^= val;
        }
        // printf("val:%d i:%d\r\n", val, i);
        printf("val:%d\r\n", val);
    }
}
