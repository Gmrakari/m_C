#include "common.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

// 打印数据内容
void print_data(const char *label, const uint8_t *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid data\r\n", __func__, __LINE__);
        return ;
    }

    if (label) {
        printf("[%s][%d] %s \r\n", __func__, __LINE__, label);
    }
    
    printf("dump data:\r\n");

    #define BYTES_PER_LINE 16

    unsigned char buf[BYTES_PER_LINE + 1] = {0};
    unsigned int i;

    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
        buf[i % BYTES_PER_LINE] = isprint(data[i]) ? data[i] : '.';

        if ((i + 1) % BYTES_PER_LINE == 0) {
            buf[BYTES_PER_LINE] = '\0';
            printf("| %s\n", buf);
        }
    }

    if (i % BYTES_PER_LINE != 0) {
        for (unsigned int j = i % BYTES_PER_LINE; j < BYTES_PER_LINE; j++) {
            printf("   ");
        }
        buf[i % BYTES_PER_LINE] = '\0';
        printf("| %s\r\n", buf);
    }

    return ;
}

// 生成随机测试数据
void generate_test_data(uint8_t *data, int len)
{
    for (int i = 0; i < len; i++) {
        data[i] = rand() % 256;
    }
}

// 比较两个数据块是否相同
int compare_data(const uint8_t *data1, const uint8_t *data2, int len)
{
    for (int i = 0; i < len; i++) {
        if (data1[i] != data2[i]) {
            printf("Data mismatch at position %d: %02X vs %02X\n", i, data1[i], data2[i]);
            return 0;
        }
    }
    return 1;
}
