#include <stdio.h>
#include <string.h> // strncpy
#include <stdlib.h> // malloc

void dec2bin(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        unsigned int mask = 1 << i;
        printf("%d", (num & mask) ? 1 : 0);
    }
    printf("\n");
}

void bin2hex(const char *binary) {
    size_t len = strlen(binary);
    if (len % 4 != 0) {
        printf("Invalid binary input!\n");
        return;
    }

    size_t hex_len = len / 4;
    char *hex = (char *)malloc(hex_len + 1);
    if (hex == NULL) {
        printf("Memory allocation error!\n");
        return;
    }

    for (size_t i = 0; i < hex_len; i++) {
        char binary_group[5];
        // 1.按照0000 (4bits) 进行分组
        strncpy(binary_group, &binary[i * 4], 4);
        binary_group[4] = '\0';
        printf("binary_group %ld: %s\r\n", i * 4, binary_group);  

        // 2.将每一个分组(0000), 进行2进制转10进制
        int decimal = strtol(binary_group, NULL, 2);

        // 3.通过调用string sprintf打印Hex的方式，将分组(0000)的按照16进制的格式写入到hex中
        sprintf(&hex[i], "%X", decimal);
        printf("hex[%ld]:%s\r\n", i, hex);
    }

    hex[hex_len] = '\0';
    printf("Hex: %s\n", hex);
    free(hex);
}

void _data_len()
{
    char data1[] = {0x24, 0x24, 0x71, 0x00, 0x81, 0x01, 0x68, 0x65, 0x6C, 
    0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xFF};

    char data[128] = {"helloworld"};

    // for (int i = 0; i < 128; i++) {
    //     printf("0x%02X", data[i]);
    //     if (i != 127) {
    //         printf(", ");
    //     }
    // }
    // printf("\r\n");

    for (int i = 0; i < 128; i++) {
        printf("%02X ", data[i]);
        // if (i != 127) {
        //     printf(", ");
        // }
    }
    printf("\r\n");

}

int main(int argc, char const *argv[]) {
    int cmd = 0x61;
    printf("cmd | 0x60:0x%02X\r\n", cmd | 0x60);
// 0x61: 01100001
// 0x60: 01100000
//     |
//   -------------
//       01100001
// => 0x61

    printf("cmd | 0x80:0x%02X\r\n", cmd | 0x80);
// 0x61: 01100001
// 0x80: 10000000
//     |
//   -------------
//       11100001
// => E1

    printf("cmd | 0x81:0x%02X\r\n", cmd | 0x81);
// 0x61: 01100001
// 0x81: 10000001
//     |
//   -------------
//       11100001
// => E1

    printf("cmd | 0x82:0x%02X\r\n", cmd | 0x82);
// 0x61: 01100001
// 0x82: 10000010
//     |
//   -------------
//       11100011
// => E3

    // dec2bin(cmd);
    // dec2bin(0x60);
    // dec2bin(0x80);

    // const char binary[] = "11100011";
    // bin2hex(binary);

    // const char binary1[] = "01100100100101111101111111000011";
    // dec2bin(1687674819);
    // bin2hex(binary1);

    // _data_len();

    char path[] = "/romfs/uartp_pic100.jpg";
    for (int i = 0; i < sizeof(path)/ sizeof(path[0]); i++) {
        printf("%c", path[i]);
    }
    printf("\r\n");

}
