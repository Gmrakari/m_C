#include <stdio.h>
#include "my_print.h"

void print(const char *str, const int *arr, const size_t arr_len)
{
    if (arr == NULL || arr_len == 0)
        return ;

    printf("\r\n");
    for (size_t i = 0; i < arr_len; i++) {
        printf("%s[%ld]:%d\r\n", str, i, arr[i]);
    }
}
