/*
 * Date:16 April 2023 3:50 PM
 * Filename:strstr.c
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h> // va_list va_start va_end

static char *strstr_usage(char *txt, ...)
{
    va_list ap;
    char *str1, *str2;
    char *result = NULL;

    va_start(ap, txt);
    str1 = va_arg(ap, char*);
    str2 = va_arg(ap, char*);
    va_end(ap);

    result = strstr(str1, str2);

    return result;
}

void strstr_test() {
    char str1[] = "hello world";
    char str2[] = "world";

    char *result = NULL;
    result = strstr_usage("test strstr", str1, str2);
    printf("result:%s\r\n", result);

    return ;
}

// result:world

int main() {
    strstr_test();
    return 0;
}
