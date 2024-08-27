#include <stdio.h>
#include <stdint.h>

static int _swap_u16_t(uint16_t val)
{
    return ((val << 8) | (val >> 8));
}

static inline uint32_t _swap_u32_t(uint32_t val) {
    return ((val & 0x000000FF) << 24) | 
            ((val & 0x0000FF00) << 8) |
            ((val & 0x00FF0000) >> 8) |
            ((val & 0xFF000000) >> 24);
}

static int _get_len_test()
{
    uint16_t len = 0x24;

    int ptr_len = sizeof(len);
    uint8_t *ptr = (uint8_t *)&len;
    for (int i = 0;i < ptr_len; i++) {
        printf("%02X", ptr[i]);
    }

    printf("\r\n");

    uint16_t dst = len << 8 | len >> 8;
    ptr = (uint8_t *)&dst;
    for (int i = 0;i < ptr_len; i++) {
        printf("%02X", ptr[i]);
    }

    printf("\r\n");

    uint32_t num = 0x12345678;
    ptr = (uint8_t *)&num;
    ptr_len = sizeof(num);
    for (int i = 0;i < ptr_len; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

    // uint32_t dst_num = _swap_u16_t(((num >> 16) & 0xFFFF))
    uint32_t dst_num = _swap_u32_t(num);
    ptr = (uint8_t *)&dst_num;
    ptr_len = sizeof(dst_num);
    for (int i = 0;i < ptr_len; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

}

int main() {
    // uint32_t data = 0x12345678;
    // uint8_t *ptr = (uint8_t*)&data;

    // if (ptr[0] == 0x78) {
    //     printf("litter ending\r\n");
    //     return 0;
    // } 

    // printf("big ending\r\n");

    _get_len_test();

    return 0;
}