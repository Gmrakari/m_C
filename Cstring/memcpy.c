
#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc

//函数原型:
//void *memcpy(void*dest, const void *src, size_t n);
//功能
//由src指向地址为起始地址的连续n个字节的数据复制到以destin指向地址为起始地址的空间内。

//内存拷贝

void test() {
    char* str = "abcd";
#if 0
    char dest[20];
#endif
    char* dest = (char*)malloc(sizeof(char)*4);
    //memset(dest, 0, sizeof(dest));
    printf("memset des:%ld\n", sizeof(dest));
    memcpy(dest, str, strlen(str) + 1);
    
    
    printf("dest = %s\n", dest);
    free(dest);
    return ;
}

int main() {
    test();
}