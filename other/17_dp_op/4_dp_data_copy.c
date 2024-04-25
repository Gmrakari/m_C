#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void _test_01(const uint8_t *data, uint16_t len) {
    uint16_t offset = 0;
    uint16_t data_len = ((data[offset++] << 8) & 0xFF00) | (data[offset++] & 0xFF);
    printf("data_len:%04X\r\n", data_len);

    typedef struct {
        uint8_t dp_num;
    } res_t;

    res_t res = {0};

    memcpy((uint8_t *)&res, &data[offset++], sizeof(res_t));

    printf("res.dp_num:%d\r\n", res.dp_num);

    uint16_t id_list_len = sizeof(uint8_t) * res.dp_num;
    uint8_t *id_list = malloc(id_list_len);
    if (!id_list) {
        return ;
    }
    memset(id_list, 0x00, id_list_len);

    memcpy(id_list, &data[offset], len - offset);

    for (int i = 0; i < res.dp_num; i++) {
        printf("%02X", id_list[i]);
        if (i != res.dp_num - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    if (id_list) {
        free(id_list);
        id_list = NULL;
    }
}

static void _test_() {
    uint8_t data[] = {0x00,0x03,0x02,0x01,0x05};
    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    _test_01(data, data_len);
}

int main() {
    _test_();
    return 0;    
}
