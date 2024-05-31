#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static void _hex_to_str(const unsigned char *data, unsigned int len)
{
    if (!data || !len) {
        printf("invaild param!\r\n");
        return ;
    }

    char output[len / 2 + 1];
    char *out_ptr = output;

    for (unsigned int i = 0;i < len; i++) {
        while (isspace(data[i])) i++;

        if (i + 1 < len) {
            unsigned int value;
            sscanf((const char *)&data[i], "%02X", &value);
            *out_ptr++ = (char)value;
        }
    }

    *out_ptr = '\0';

    printf("%s\r\n", output);

    return ;
}

static void _hex_string_arr_to_str(const unsigned char *data, unsigned int len)
{
    if (!data || !len) {
        printf("invaild param!\r\n");
        return ;
    }

    // char output = 
    int out_len = len / 2 + 1;
    unsigned char *out = malloc(sizeof(unsigned char) * out_len);
    if (!out) {
        printf("malloc err!\r\n");
        return ;
    }
    memset(out, 0x00, out_len);

    unsigned char *out_ptr = out;

    for (unsigned int i = 0; i < len; i++) {
        if (isspace(data[i])) i++;

        if (i + 1 < len) {
            unsigned int value;
            sscanf((const char*)&data[i], "%02X", &value);

            printf("%c", value);
            printf("\r\n");
            *out_ptr++ = (char)value;
        }
    }

    *out_ptr = '\0';

    printf("%s\r\n", out);

    if (out) {
        free(out);
        out = NULL;
    }
 
    return ;
}

void _hex() {
    char hex_input[1024]; // 假设最大输入长度为1024字符
    printf("请输入十六进制字符串: ");
    scanf("%1023s", hex_input); // 读取输入，最多1023字符（预留一个位置给终止符）

    unsigned int len = strlen(hex_input); // 输入的十六进制字符串长度

    // 动态分配内存，len/2用于存储转换后的字符，加1用于存储终止符
    char *output = (char *)malloc(len / 2 + 1);
    if (output == NULL) {
        printf("内存分配失败\n");
        return;
    }
    char *out_ptr = output; // 指向输出缓冲区的指针

    // 遍历输入数据，将每两个字符转换为一个字符
    for (unsigned int i = 0; i < len; i += 2) {
        // 跳过空格
        while (isspace(hex_input[i])) i++;
        if (i + 1 < len) {
            unsigned int value;
            sscanf(&hex_input[i], "%2x", &value);
            *out_ptr++ = (char)value;
        }
    }
    *out_ptr = '\0'; // 添加字符串结束符

    // 打印结果
    printf("转换后的字符串: %s\n", output);

    // 释放动态分配的内存
    free(output);

    return;
}
int main()
{
    const unsigned char data[] ="7B 22 6D 73 67 30 7D";
    unsigned int len = sizeof(data) - 1;

    // _hex_string_arr_to_str(data, len);

    _hex();

    return 0;
}