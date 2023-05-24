/*
 * Date:23 May 2023 22:09
 * Filename:_2d_arr_rotation.c
*/

#include "_2d_arr_rotation.h"
#include "_2d_arr_print.h"

static int arr[4][4] = {0};
static int dest[4][4] = {0};

void print(const char *str, const int (*arr)[], const size_t row, const size_t col);

static int _2d_arr_init(size_t row, size_t col)
{
    int ret = 0;
    if (col == 0) {
        ret = -1;
        return ret;
    }

    // int **ptr = &arr;                   // 问题1:
                                           // 1.int **ptr 时，它是一个指向指针的指针，表示一个指针数组。
                                           // 2.在这种情况下，内存中的存储布局是不同的。它需要在内存中为每个指针分配单独的内存空间，并且这些指针可以指向不同的内存区域。
                                           // 3.将 int **ptr 指向 arr 的地址会导致类型不匹配和不正确的内存访问，可能会引发段错误或其他未定义行为。

    int (*ptr)[col] = (int (*)[col])arr;;  // 解决1:
                                           // 1.使用指向二维数组 arr 的指针，即 int (*ptr)[col]，其中 col 是二维数组的列数。
                                           // 2.这样，指针 ptr 将正确地指向二维数组 arr 的起始位置，并且可以通过指针算术运算访问元素。
                                           // 3.将 arr 强制转换为 int (*)[col] 类型，使其与 ptr 的指针类型匹配,消除警告信息
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            ptr[i][j] = i * col + j + 1;
        }
    }

    return ret;
}

static void _2d_arr_rotation(const int (*src)[], int (*dest)[], const size_t row, const size_t col)
{
    if (src == NULL || dest == NULL|| col == 0)
        return ;

    int (*src_ptr)[col] = (int (*)[])src; 
    int (*dest_ptr)[col] = (int (*)[])dest; 

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            dest_ptr[j][row - i - 1] = src_ptr[i][j];
        }
    }
}

void app_test()
{
    size_t row = 4, col = 4;

    int ret = 0;

    if (0 != (ret = _2d_arr_init(row, col)))
        return ;

    int (*arr_2d)[4] = (int (*)[])arr;
    int (*dest_2d)[4] = (int (*)[])dest;
    const char arr_str[] = "src";
    const char dest_str[] = "dest";

    print(arr_str, arr_2d, row, col);

    _2d_arr_rotation(arr_2d, dest_2d, row, col);

    print(dest_str, dest_2d, row, col);
}
