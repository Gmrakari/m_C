#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define LOGD(format, ...)   printf("[%s](%d): " format, __func__, __LINE__, ##__VA_ARGS__)

static void test_1()
{
    typedef struct
    {
        uint8_t gmt[6];              /* 年(去掉世纪2B) 月(2B) 日(2B) 时(2B) 分(2B) 秒(2B) */
        uint8_t passwd_len;          /* 密码长度 */
        uint8_t *passwd;             /* 密码 */
    } __attribute__((packed)) res_t;

    res_t *res = NULL;

    // passwd:4183383233
    uint8_t src_data[] = {0x14,0x09,0x16,0x03,0x2D,0x07,0x0A,0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};
    size_t src_data_len = sizeof(src_data) / sizeof(src_data[0]);
    uint16_t passwd_len = 0x0A;
    uint16_t data_len = sizeof(res->gmt) + sizeof(res->passwd_len) + passwd_len;
    uint8_t* in_data = malloc(data_len);
    if (!in_data) 
        return ;

    memset(in_data, 0x00, data_len);
    memcpy(in_data, src_data, src_data_len);

    printf("sizeof(res_t):%zu\r\n", sizeof(res_t));
    printf("\r\n");

    res = (res_t *)in_data;

    printf("1 res->passwd:%p\r\n", res->passwd);

    res->passwd = malloc(0);
    if (!res->passwd) return ;
    printf("2 res->passwd:%p\r\n", res->passwd);

    LOGD("res->gmt:%02X%02X%02X%02X%02X%02X\r\n", res->gmt[0],res->gmt[1],res->gmt[2],res->gmt[3],res->gmt[4],res->gmt[5]);
    LOGD("res->passwd_len: %02X\r\n", res->passwd_len);
    
    size_t passwd_offset = sizeof(res->gmt) + sizeof(res->passwd_len);

    // res->passwd = (uint8_t *)in_data + passwd_offset;
    memcpy(res->passwd, (uint8_t *)in_data + passwd_offset, res->passwd_len);

    printf("\r\n");
    uint8_t *ptr = res->passwd;
    for (int i = 0; i < res->passwd_len; i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\r\n");

    if (in_data) {
        free(in_data);
        in_data = NULL;
    }

    if (res->passwd) {
        free(res->passwd);
        res->passwd = NULL;
    }

    // printf("\r\n");
    // uint8_t *pptr = (uint8_t *)(in_data + sizeof(res->gmt) + sizeof(res->passwd_len));
    // uint16_t pptr_len = passwd_len;
    // for (int i = 0; i < pptr_len; i++) {
    //     printf("%02X ", pptr[i]);
    // }
    // printf("\r\n");
}

int main()
{
    test_1();
    return 0;
}
