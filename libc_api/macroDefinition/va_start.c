
/*
** Date:2022-11-09 11:30
** C 库宏 void va_start(va_list ap, last_arg) 初始化 ap 变量，它与 va_arg 和 va_end 宏是一起使用的。
** last_arg 是最后一个传递给函数的已知的固定参数，即省略号之前的参数。
** 
*/

#include <stdarg.h>
#include <stdio.h>

int sum(int, ...);

int main(void) {
    printf("10, 20, 30 total sum is:%d\r\n", sum(3, 10, 20, 30));
    printf("4, 20, 25, 30 total sum is:%d\r\n", sum(4, 4, 20, 25, 30));

    return 0;
}

int sum(int numArgs, ...) {
    int val = 0;
    va_list ap;
    int i;

    va_start(ap, numArgs);
    for (i = 0;i < numArgs; i++) {
        val += va_arg(ap, int);
    }
    va_end(ap);
    return val;
}