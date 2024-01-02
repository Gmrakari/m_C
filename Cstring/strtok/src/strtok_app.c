#include <string.h>

#include "strtok_app.h"

static void func() {
    char str[] = "This is a sample string";
    const char delimiters[] = " ";  // 分隔符可以是空格、逗号等

    printf("origin str:%s\r\n", str);

    // 使用strtok函数分解字符串
    char *token = strtok(str, delimiters);

    // 循环获取所有标记
    while (token != NULL) {
        printf("Token: %s\n", token);

        // 通过传入NULL获取下一个标记
        token = strtok(NULL, delimiters);
    }

    return ;

}

static void tmp_func() {
    char str[] = "str1/str2/str3/str4/str5";
    printf("origin str:%s\r\n", str);

    char *tmp = strtok(str, "/");
    int cnt = 0;

    while (tmp) {
        tmp = strtok(NULL, "/");
        if (tmp) {
            printf("%d tmp:%s\r\n", cnt++, tmp);
        }
    }
}

void strtok_func(void) {
    // func();
    tmp_func();
    return ;
}