
#include <stdio.h>

static void _print_path(char (*path)[64], int len)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    for (int i = 0;i < len; i++) {
        printf("%s\r\n", path[i]);
    }
}

int main()
{
    char path[2][64] = {"/home/path1/file_a.txt",
                                "/home/path2/file_b.txt"};
    int arr_len = sizeof(path) / sizeof(path[0]);
    printf("arr_len:%d\r\n", arr_len);
    _print_path(path, arr_len);
}