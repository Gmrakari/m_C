#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LOGD(format, ...)   printf("[%s](%d): " format, __func__, __LINE__, ##__VA_ARGS__)

typedef struct {
    uint8_t gmt[6];      /* 年(去掉世纪2B) 月(2B) 日(2B) 时(2B) 分(2B) 秒(2B) */
    uint8_t passwd_len;  /* 密码长度 */
    uint8_t *passwd;     /* 密码 */
} __attribute__((packed)) res_t;

void printStructMembers(res_t *res) {
    printf("res->gmt: ");
    for (int i = 0; i < sizeof(res->gmt); ++i) {
        printf("%02X ", res->gmt[i]);
    }

    printf("\nres->passwd_len: %02X\n", res->passwd_len);

    LOGD("res->passwd:%p\r\n", res->passwd);
    LOGD("res->passwd:%02X\r\n", res->passwd[0]);

    printf("res->passwd: ");
    for (int i = 0; i < res->passwd_len; ++i) {
        printf("%02X ", res->passwd[i]);
    }

    printf("\n");
}

static int _test_1()
{
    // 假设有一块内存数据
    uint8_t data[] = {0x14,0x09,0x16,0x03,0x2D,0x07,0x0A,0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};

    // 创建一个结构体指针
    res_t *res = malloc(sizeof(res_t));
    LOGD("res->gmt:%p\r\n", res->gmt);
    LOGD("res->passwd_len:%p\r\n", res->passwd_len);
    LOGD("res->passwd:%p\r\n", res->passwd);

    // 检查内存分配是否成功
    if (res == NULL) {
        fprintf(stderr, "内存分配失败\n");
        return 1;
    }

    printf("res->passwd_len:%d\r\n", res->passwd_len);
    printf("res->passwd:%p\r\n", res->passwd);

    LOGD("res->passwd:%p\r\n", res->passwd);
    // 为 res->passwd 分配内存
    res->passwd = malloc(res->passwd_len);
    if (res->passwd == NULL) {
        fprintf(stderr, "内存分配失败\n");
        free(res);
        return 1;
    }
    LOGD("res->passwd:%p\r\n", res->passwd);
    printf("res->passwd:%p\r\n", res->passwd);

    // 将内存数据拷贝到结构体中
    memcpy(res->gmt, data, sizeof(res->gmt));
    memcpy(&res->passwd_len, data + sizeof(res->gmt), sizeof(res->passwd_len));
    memcpy(res->passwd, data + sizeof(res->gmt) + sizeof(res->passwd_len), res->passwd_len);

    // 打印结构体成员的16进制值
    printStructMembers(res);

    // 释放分配的内存
    free(res->passwd);
    free(res);
}

static int test_2()
{
    uint8_t data[] = {0x14,0x09,0x16,0x03,0x2D,0x07,0x0A,0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};
    size_t data_arr_len = sizeof(data) / sizeof(data[0]);

    uint8_t *in_data = malloc(sizeof(uint8_t) * data_arr_len);
    if (!in_data) return -1;

    memset(in_data, 0x00, data_arr_len);

    memcpy(in_data, data, data_arr_len);

    res_t *res = malloc(sizeof(res_t));
    if (!res) return -1;

    memcpy(res->gmt, in_data, sizeof(res->gmt));
    memcpy(&(res->passwd_len), in_data + sizeof(res->gmt), sizeof(res->passwd_len));

    // res = (res_t *)in_data;
    LOGD("res->passwd:%p\r\n", res->passwd);
    // LOGD("res->passwd:%02X\r\n", res->passwd[0]);

    LOGD("res->passwd_len:%d\r\n", res->passwd_len);
    res->passwd = malloc(res->passwd_len);
    if (!res->passwd) {
        free(in_data);
        in_data = NULL;
    }
    memset(res->passwd, 0x00, res->passwd_len);
    LOGD("res->passwd_len:%d\r\n", res->passwd_len);

    printf("start print res->passwd:\r\n");
    for (int i = 0;i < res->passwd_len; i++) {
        printf("%02X", res->passwd[i]);
    }
    printf("\r\nend print res->passwd\r\n");

    printf("ptr:\r\n");

    memcpy(res->passwd, (uint8_t *)(in_data + sizeof(res->gmt) + sizeof(res->passwd_len)), res->passwd_len);
    LOGD("res->passwd:%p\r\n", res->passwd);

    printf("res->passwd:%02X\r\n", res->passwd[0]);

    printf("ptr:\r\n");
    uint8_t *ptr = (uint8_t *)res->passwd;
    for (int i = 0; i < res->passwd_len; i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\r\n");

    if (res->passwd) {
        free(res->passwd);
        res->passwd = NULL;
    }

    if (res) {
        free(res);
        res = NULL;
    }

    if (in_data) {
        free(in_data);
        in_data = NULL;
    }
}

int main() {
    // _test_1();
    test_2();
    return 0;
}
