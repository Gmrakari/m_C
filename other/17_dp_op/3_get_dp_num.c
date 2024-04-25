#include <stdio.h>
#include <stdint.h>

int count_dp_data(uint8_t *data, uint16_t len) {
    if (len < 2) {
        return 0;  // 数据长度不足以存放总长度字段
    }

    uint16_t total_len = (data[0] << 8) | data[1];

    printf("total len:%d\r\n", total_len);

    uint16_t offset = 0;

    offset += sizeof(total_len);
    printf("offset:%d\r\n", offset);

    int dp_count = 0;
    while (offset < total_len) {
        dp_count++;
        if (offset + 4 > total_len)
            break;

        uint8_t dp_id = data[offset];
        uint8_t dp_type = data[offset + 1];
        uint16_t dp_len = data[offset + 2] << 8 | data[offset + 3];

        offset += 4;

        if (offset + dp_len > total_len)
            break;

        offset += dp_len;
    }

    // while (offset < total_len) {
    //     if (offset + 4 > total_len) {
    //         printf("Error: Incomplete DP header at offset %d\n", offset);
    //         break;  // 剩余数据不足以存放完整的DP头部
    //     }

    //     uint16_t dp_id = (data[offset] << 8) | data[offset + 1];
    //     uint16_t dp_len = (data[offset + 2] << 8) | data[offset + 3];

    //     offset += 4;  // 跳过DP头部

    //     if (offset + dp_len > total_len) {
    //         printf("Error: Incomplete DP data at offset %d\n", offset);
    //         break;  // 剩余数据不足以存放完整的DP数据
    //     }

    //     dp_count++;
    //     offset += dp_len;  // 跳过DP数据
    // }

    // return dp_count;

    return dp_count;
}

int get_dp_num(const uint8_t *data, uint16_t len)
{
    if (!data) return 0;

    int dp_count = 0;

    uint16_t offset = 0;
    uint16_t total_len = len;

    while (offset < total_len) {
        if (offset + 4 > total_len)
            break;
        
        uint8_t id = data[offset];
        uint8_t type = data[offset + 1];
        uint16_t dp_len = data[offset + 2] << 8 | data[offset + 3];
        printf("%02X ", id);
        printf("%02X ", type);
        printf("%02X %02X ", data[offset + 2], data[offset + 3]);
        printf("%04X %d\r\n", dp_len, dp_len);

        offset += 4;

        if (dp_len > 1) {
            offset += dp_len - 1;
        } else {
            offset += dp_len;
        }

        dp_count++;
    }

    return dp_count;
}

int main() {
    // uint8_t data1[] = {0x00, 0x05, 0x6D, 0x01, 0x00, 0x01, 0x01};
    // uint8_t data2[] = {0x00, 0x15, 0x6D, 0x01, 0x00, 0x01, 0x01, 0x66, 0x03, 0x00, 0x0C, 0x32, 0x30, 0x31, 0x38, 0x30, 0x34, 0x31, 0x32, 0x31, 0x35, 0x30, 0x37};
    // uint8_t data3[] = {0x00,0x2D,0x6D,0x01,0x00,0x01,0x01,0x6D,0x01,0x00,0x01,0x01,0x6D,0x01,0x00,0x01,0x01,0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30,0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30};

    // int count1 = count_dp_data(data1, sizeof(data1));

    // // printf("sizeof(data2):%ld\r\n", sizeof(data2));
    // int count2 = count_dp_data(data2, sizeof(data2));
    // int count3 = count_dp_data(data3, sizeof(data3));

    // printf("Number of DP data in data1: %d\n", count1);
    // printf("Number of DP data in data2: %d\n", count2);
    // printf("Number of DP data in data3: %d\n", count3);

    printf("\r\n");
    uint8_t data4[] = {0x6D, 0x01, 0x00, 0x01, 0x01};
    uint8_t data5[] = {0x6D, 0x01, 0x00, 0x01, 0x01, 0x66, 0x03, 0x00, 0x0C, 0x32, 0x30, 0x31, 0x38, 0x30, 0x34, 0x31, 0x32, 0x31, 0x35, 0x30, 0x37};
    uint8_t data6[] = {0x6D, 0x01, 0x00, 0x01, 0x01, 0x6D, 0x01, 0x00, 0x01, 0x01, 0x6D, 0x01, 0x00, 0x01, 0x01, 0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30,0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30};
    uint8_t data7[] = {0x6D,0x01,0x00,0x01,0x01,0x6D,0x01,0x00,0x01,0x01,0x6D,0x01,0x00,0x01,0x01,0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30,0x66,0x03,0x00,0x0C,0x32,0x30,0x31,0x38,0x30,0x34,0x31,0x32,0x31,0x35,0x30,0x6D,0x01,0x00,0x01,0x01};
    // int count4 = get_dp_num(data4, sizeof(data4));
    // int count5 = get_dp_num(data5, sizeof(data5));
    // int count6 = get_dp_num(data6, sizeof(data6));
    int count7 = get_dp_num(data7, sizeof(data7));
    // printf("Number of DP data in data4: %d\r\n", count4);
    // printf("Number of DP data in data5: %d\r\n", count5);
    // printf("Number of DP data in data6: %d\r\n", count6);
    printf("Number of DP data in data7: %d\r\n", count7);

    return 0;
}