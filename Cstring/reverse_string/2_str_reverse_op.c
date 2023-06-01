#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void func(char *str, size_t len)
{
    int j = 0;
    char *dest = NULL;
    dest = (char*)malloc(sizeof(char) * (len + 1));
    memset(dest, 0, len + 1);

    for (int i = len - 1; i >= 0; i--) {
        dest[j] = str[i];
        // printf("str[%d]:%c\r\n", i, str[i]);
        // printf("dest[%d]:%c\r\n", j, dest[j]);
        j++;
    }
    printf("str:%s\r\n", str);
    
    printf("[%s][%d]\r\n", __func__, __LINE__);
    dest[len] = '\0';printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("dest:%s\r\n", dest);
    str = dest; 

    printf("2str:%s\r\n", str);
    printf("2dest:%s\r\n", dest);
    free(dest);printf("[%s][%d]\r\n", __func__, __LINE__);
    dest = NULL;printf("[%s][%d]\r\n", __func__, __LINE__);
}

void p2p_func(char **str, size_t len)
{
    if (str == NULL || len < 0) return ;
    int j = 0;
    char *dest = NULL;
    dest = (char *)malloc(sizeof(char) * (len + 1));
    if (dest == NULL) return ;

    for (int i = len - 1; i >= 0; i--) {
        dest[j] = (*str)[i];
        j++;
    }
    dest[len] = '\0';

    // strcpy(*str, dest);          // err 无法对一个char *进行变量修改,只能修改它的指针指向(地址)
    *str = dest;

    // memcpy(*str, dest, len + 1); // str是一个字符常量 无法修改
}

void print(char *str) {
    if (str == NULL) return ;
    while (*str != '\0') {
        printf("%c", *str++);
    }
    printf("\r\n");
}

size_t _get_str_len(char *str) {
    if (str == NULL) return -1;
    size_t len = 0;
     while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

int main() {
    char *str = "abcdefg";
    size_t len = _get_str_len(str);

    printf("len:%ld\r\n", len);

    print(str);
    
    // func(str, len);

    p2p_func(&str, len);

    print(str);

    // 在p2c_func中申请内存,需要释放
    free(str);
    str = NULL;

    return 0;
}
