
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc

//函数原型:
// void *memcpy(void*dest, const void *src, size_t n);
//功能
//由src指向地址为起始地址的连续n个字节的数据复制到以destin指向地址为起始地址的空间内。

//内存拷贝

void test()
{
    char *str = "abcd";
#if 0
    char dest[20];
#endif
    char *dest = (char *)malloc(sizeof(char) * 4);
    // memset(dest, 0, sizeof(dest));
    printf("memset des:%ld\n", sizeof(dest));
    memcpy(dest, str, strlen(str) + 1);

    printf("dest = %s\n", dest);
    free(dest);
    return;
}

void memcpy_1(void) {

    unsigned char jpg[64 * 64 * 2];
    memset(jpg, 0, sizeof(jpg));
    printf("jpg:%s, sizeof:%ld, address:%p\r\n", jpg, sizeof(jpg), jpg);

    unsigned char src[] = "abc";
    unsigned char *buf = (unsigned char *)malloc(sizeof(src));
    memcpy(buf, src, sizeof(src));

    printf("buf:%s, %p, sizeof:%ld\r\n", buf, buf, sizeof(buf));

    memcpy(jpg, buf, sizeof(buf));
    printf("jpg:%s, address:%p, sizeof:%ld\r\n", jpg, jpg, sizeof(jpg));

    if (buf != NULL) {
        free((buf));        
    }
}

void memcpy_2() {
    typedef struct tmp {
        unsigned char *data;
    } tmp_t;

    tmp_t jpg;
    // memset(jpg.data, 0, sizeof(jpg.data));

    jpg.data = (unsigned char*)malloc(4);
    unsigned char arr[] = "abc";

    memcpy(jpg.data, arr, sizeof(arr));
    printf("tmp_t jpg.data:%s, address:%p, sizeof(jpg.data):%ld\r\n", jpg.data, jpg.data, sizeof(jpg.data));

    unsigned char buf[64 * 64 * 2];
    memcpy(buf, jpg.data, sizeof(jpg.data));
    printf("buf:%s, %p, sizeof:%ld\r\n", buf, buf, sizeof(buf));

    if (jpg.data != NULL) {
        free(jpg.data);
    }

}

int main()
{
    #if 0
    test();
    #endif

    // memcpy_1();

    memcpy_2();
}
