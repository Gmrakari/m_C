#include <stdio.h>

void print_char_type_hex_byte()
{
    printf("%d\r\n", 0xFFFF);

    int x = 11;
    if (x == 0xFFFF) {
        printf("0XFFFF\r\n");
        printf("%02x\r\n", x);
    } else if (x == 0xB) {
        printf("2_0x000B\r\n");
        printf("%02x\r\n", x);
    } else {
        printf("%02x\r\n", x);
    }

    // char a = 0xFF;
    unsigned char a = 255;
    printf("%02x\r\n", a);

    char a1 = -128;
    char a2 = 127;

    printf("a1, a2 output:\r\n");
    printf("%hhx\r\n", a1);      // hh表示将char类型作为无符号字符处理
    printf("%hhx\r\n", a2);
}

int main()
{
    print_char_type_hex_byte();
}