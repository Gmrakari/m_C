#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void _test_01(const uint8_t *data, uint16_t len) {
    if (!data || !len) return ;

    typedef struct {
        uint8_t len;
        uint8_t data0;
        uint8_t data1;
        uint8_t data2;
        uint8_t data3;
        uint8_t data4;
        // uint8_t id;
        // uint16_t dp_len;
        // uint8_t *value;
    } res_t;

    typedef struct {
        uint8_t id;         // dp id
        uint16_t dp_len;    // dp数据长度
        uint32_t ts;        // ts
        uint8_t *value;     // dp数据
    } dp_data_t;

    res_t res = {0};

    uint16_t offset = 0;
    memcpy((uint8_t *)&res.len, data, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    printf("res.len:%d\r\n", res.len);

    char gmt[5] = {0};
    memcpy(gmt, data + offset, sizeof(gmt));
    offset += sizeof(gmt);

    int gmt_len = sizeof(gmt) / sizeof(gmt[0]);
    for (int i = 0; i < gmt_len; i++) {
        printf("%02X", gmt[i]);
        if (i != gmt_len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    uint16_t dp_data_len = sizeof(dp_data_t) - sizeof(uint8_t *);
    dp_data_t dp_data;
    dp_data.id = data[offset++];
    uint16_t get_dp_len = data[offset++] << 8 | data[offset++];
    dp_data.dp_len = get_dp_len;
    uint32_t dp_ts = data[offset++] << 24 | data[offset++] << 16 | data[offset++] << 8 | data[offset];
    dp_data.ts = dp_ts;
    dp_data.value = (uint8_t *)&data[offset];

    printf("dp_data.dp_len:%d\r\n", dp_data.dp_len);
    printf("dp_ts:%d\r\n", dp_data.ts);

    printf("ts bytes:\r\n");
    uint8_t *ts_ptr = (uint8_t*)&dp_data.ts;
    for (int i = 0; i < sizeof(uint32_t); i++) {
        printf("%02X", ts_ptr[i]);
    }
    printf("\r\n");

    // dp_data.value = NULL;
    // dp_data.value = &data[offset];

    for (int i = 0; i < dp_data.dp_len; i++) {
        printf("%02X", dp_data.value[i]);
        if (i != dp_data.dp_len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");
}

static void _test_() {
    uint8_t data[] = {0x05, 0x01, 0x02, 0x03, 0x04, 0x05, 0x01, 0x00, 0x02, 0x5F, 0xEE, 0x66, 0x2D, 0x01, 0x02};
    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    _test_01(data, data_len);
}

int main() {
    _test_();
    return 0;    
}
