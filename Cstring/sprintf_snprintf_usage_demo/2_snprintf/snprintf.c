#include <stdio.h>

//函数原型:
//int snprintf ( char * str, size_t size, const char * format, ... );

//Args:
//str -- 目标字符串。
//size -- 拷贝字节数(Bytes)。
//format -- 格式化成字符串。
//... -- 可变参数。

//return
//1、如果格式化后的字符串长度小于 size，则会把字符串全部复制到 str 中，并给其后添加一个字符串结束符 \0；
//2、如果格式化后的字符串长度大于等于 size，超过 size 的部分会被截断，
//只将其中的 (size-1) 个字符复制到 str 中，并给其后添加一个字符串结束符 \0，返回值为欲写入的字符串长度。

void test() {
    char buffer[50];
    char* s = "runoobcom";

    int j = snprintf(buffer, 6, "%s\n", s);

    printf("string:\n%s\ncharacter count = %d\n", buffer, j);
    
    return ;
}

int main() {
    test();
}

