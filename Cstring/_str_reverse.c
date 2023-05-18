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

    // memcpy(*str, dest, len + 1); // str是一个字符常量 无法修改
    // strcpy(*str, dest);

    // free(*str);
    *str = dest;

    // printf("dest:%s\r\n", dest);
    // printf("str:%s\r\n", *str);
}

void print(char *str) {
    if (str == NULL) return ;
    while (*str != '\0') {
        printf("%c", *str++);
    }
    printf("\r\n");
}

int main() {
    char str[] = "abcdefg";
    size_t len = 7;

    printf("len:%ld\r\n", len);

    // print(str);
    
    // func(str, len);

    p2p_func(&str, len);

    print(str);

    return 0;
}

// size_t len = _get_str_len(str);

size_t _get_str_len(char *str) {
    if (str == NULL) return -1;
    size_t len = 0;
     while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}