#include <stdio.h>
#include <string.h>

// strchr() 用于查找字符串中的一个字符，并返回该字符在字符串中第一次出现的位置

// char *strchr(const char *str, int c)


static strchr_test(void)
{
    char buf_str[] = "hello world";
    char *buf_str_ptr = buf_str;

    int c = 'l';

    char *ret_str = strchr(buf_str, c);
    printf("strchr: %s\n", ret_str);

    int len = ret_str - buf_str_ptr; // 2: ret_str 2个偏移量; buf_str_ptr 0个偏移量

    printf("len: %d\n", len);
}

int main() 
{
    strchr_test();
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}
