#include <stdio.h>
#include <string.h>
#include "my_memcpy.h"
#include "my_print.h"

void *my_memcpy(void *dest, const void *src, size_t n);
void print(const char *str, const int *arr, const size_t arr_len);

static int arr[10] = {0};

static int *_init_arr(size_t len)
{
    if (len == 0)
        return NULL;

    int *ptr = arr;
    for (size_t i = 0; i < len; i++)
    {
        ptr[i] = i;
    }
    return arr;
}

static void test(void)
{
    size_t src_len = 10;
    int *src = _init_arr(src_len);
    const char src_str[] = "src";
    int dest[10] = {0};
    const char dest_str[] = "dest";
    const char len_str[] = "len";

    printf("%s %s:%zu\r\n", src_str, len_str, src_len);
    size_t dest_len = sizeof(dest) / sizeof(dest[0]);
    printf("%s %s:%zu\r\n", dest_str, len_str, dest_len);

    print(src_str, src, src_len);

    my_memcpy(dest, src, src_len * sizeof(int)); // src_len * sizeof(int) 拷贝的大小是按照(长度 * 类型)计算

    print(dest_str, dest, dest_len);
}

int main(int argc, char const *argv[])
{
    test();
}
