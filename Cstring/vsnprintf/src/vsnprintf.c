#include <stdarg.h>

#include "vsnprintf.h"

static int printFormatStr(const char *format, ...) {
    if (!format) return -1;

    char buff[512];
    int ret = 0;

    va_list args;

    // 初始化参数列表
    va_start(args, format);

    size_t res = vsnprintf(buff, sizeof(buff), format, args);

    // 清理可变参数列表
    va_end(args);


    // out:
    // get str len:37
    // Formatted String: hello and world! the string len is 37!
    if (res > 0) {
        printf("Formatted String: %s\n", buff);
    } else {
        ret = -1;
        printf("Error occurred during formatting.\n");
    }
    return ret;
}

void vsnprint_app(void) {
    const char str[] = "hello and %s! the string len is %d!";
    const char str_value[] = "world";
    vsnprint_test(str, str_value);
}

void vsnprint_test(const char *src, const char *pstr) {
    if (!src || !pstr) return ;

    int ret = 0;

    const char *str = src;
    const char *ppstr = pstr;

    size_t len = 0;
    size_t get_str_len = snprintf(NULL, 0, str, ppstr, len);
    if (get_str_len <= 0) return ;

    printf("get str len:%ld\r\n", get_str_len);

    ret = printFormatStr(str, ppstr, get_str_len);

    if (ret != 0) {
        printf("printFormatStr err\r\n");
    }

    return ;
}