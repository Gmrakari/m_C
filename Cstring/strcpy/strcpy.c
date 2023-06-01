#include <stdio.h>
#include <string.h>

// err
// char a 只占用一个字节，hello占用6个字节(5 + '\0')
// strcpy(dst, str); dst长度不足，导致缓存区溢出
// printf 打印到str为NULL,由于str没有定义，str没有NULL，输出err
int main() {
    char a;
    char *str = &a;
    strcpy(str, "hello");
    printf(str);
    return 0;
}

int main() {
    char a[2];
    char *str = a;
    size_t len = sizeof(a);
    strncpy(str, "hello", 2);
    str[2] = '\0';
    printf("%s\r\n", str);
    return 0;
}


int main() {
    char a;
    char *str = &a;
    strcpy(str, "hs");
    // str = "\0";
    printf(str);
    return 0;
}