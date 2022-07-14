#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//函数原型:
//int sprintf( char *buffer, const char *format, [ argument] … );

//参数列表

//buffer：char型指针，指向将要写入的字符串的缓冲区。
//format：格式化字符串。
//[argument]...：可选参数，可以是任何类型的数据。

void test() {
    char buffer[50];
    int ret, a = 5, b = 3;
    ret = sprintf(buffer, "%d plus %d is %d", a, b, a + b);
    printf("[%s]is a string ret:%d\n", buffer, ret);
    return ;
}

void testRandomNum() {
    char str[100];
    int offset = 0;
    int i = 0;
    srand(time(0));  //随机种子
    for (i = 0; i < 10; i++) {
        offset += sprintf(str + offset, "%d,", rand() % 100);//格式化的数据写入字符串
    }

    str[offset - 1] = '\n';
    printf(str);
    return ;
}

int main() {
    test();
    testRandomNum();
}