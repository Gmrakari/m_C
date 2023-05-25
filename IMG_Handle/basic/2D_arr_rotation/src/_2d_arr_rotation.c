/*
 * Date:23 May 2023 22:09
 * Filename:_2d_arr_rotation.c
*/

/*
*
* Readme
*
* 源数据:
* src[0][0]:1     src[0][1]:2     src[0][2]:3
* src[1][0]:4     src[1][1]:5     src[1][2]:6
* src[2][0]:7     src[2][1]:8     src[2][2]:9
*
* 顺时针旋转90度:
* src[2][0]:7     src[1][0]:4     src[0][0]:1
* src[2][1]:8     src[1][1]:5     src[0][1]:2
* src[2][2]:9     src[1][2]:6     src[0][2]:3
*
* 最后结果:
* src[0][0]:7     src[0][1]:4     src[0][2]:1
* src[1][0]:8     src[1][1]:5     src[1][2]:2
* src[2][0]:9     src[2][1]:6     src[2][2]:3
*
* 变化过程:
* src[0][0]:1, i = 0, j = 0 --> src[0][2]:1, i = 0, j = 2
* src[0][1]:2, i = 0, j = 1 --> src[1][2]:2, i = 1, j = 2
* src[0][2]:3, i = 0, j = 2 --> src[2][2]:3, i = 2, j = 2
* 
* src[1][0]:4, i = 1, j = 0 --> src[0][1]:4, i = 0, j = 1
* src[1][1]:5, i = 1, j = 1 --> src[1][1]:5, i = 1, j = 1
* src[1][2]:6, i = 1, j = 2 --> src[2][1]:6, i = 2, j = 1
* 
* src[2][0]:7, i = 2, j = 0 --> src[0][0]:7, i = 0, j = 0
* src[2][1]:8, i = 2, j = 1 --> src[1][0]:8, i = 1, j = 0
* src[2][2]:9, i = 2, j = 2 --> src[2][0]:9, i = 2, j = 0
* 
* 分析规律
* 123, i从0,0,0变成为0,1,2;j从0,1,2变为2,2,2   ==> 
* 
* 456, i从1,1,1改变为0,1,2;j从0,1,2改变为1,1,1 ==> 
* 
* 789, i从2,2,2改变为0,1,2;j从0,1,2改变为0,0,0 ==>
* 
* for (int i = 0; i < row; i++) {
* 	for (int j = 0; j < col; j++) {
* 	    dest[j][row - i - i] = arr[i][j]; 
* 	}
* }
*
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
