#include <stdio.h>

// 函数用于转换大端字节序为小端字节序
unsigned short swapEndian(unsigned short value) {
    return ((value >> 8) & 0xFF) | ((value << 8) & 0xFF00);
}

int checkEndian() {
    int value = 1;
    char *ptr = (char *)&value;

    // 如果最低地址存储的是最低有效字节，表示为小端存储
    if (*ptr == 1) {
        return 1;
    } 

    return 0;
}

int main() {
    // unsigned short bigEndianValue = 0x1234; // 大端字节序的值
    // unsigned short littleEndianValue = swapEndian(bigEndianValue); // 转换为小端字节序

    // printf("Big Endian Value: 0x%X\n", bigEndianValue);
    // printf("Little Endian Value: 0x%X\n", littleEndianValue);

    if (checkEndian()) {
        printf("Little Endian\n");
    } else {
        printf("Big Endian\n");
    }

    unsigned short hexValue = 0x1234;

    printf("0x%x\r\n", hexValue);

    char *buf = (char*)&hexValue;
    for (int i = 0; i < 2; i++) {
        printf("buf:0x%X\r\n", buf[i] & 0xFF);
    }

    return 0;
}
