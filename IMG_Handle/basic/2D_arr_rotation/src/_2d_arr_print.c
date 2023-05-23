#include <stdio.h>
#include <stddef.h>
#include "_2d_arr_print.h"

void print(const char *str, const int (*arr)[], const size_t row, const size_t col)
{
    if (arr == NULL || col == 0)
        return ;

    int (*ptr)[col] = (int (*)[col])arr;

    printf("\r\n");
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            printf("%s[%zu][%zu]:%d\t", str, i, j, ptr[i][j]);
            if (j + 1 == col) printf("\r\n");
        }
    }
}
