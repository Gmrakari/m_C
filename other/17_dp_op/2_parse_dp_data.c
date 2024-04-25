#include <stdio.h>
#include <stdint.h>

// 解析函数
void parse_data(const uint8_t *data, size_t length) {
    size_t index = 0;
    uint8_t dp_count = 0; // 计数器，用于记录DP数据的数量

    while (index < length) {
        // 检查总数据长度
        uint8_t total_length = data[index++];
        printf("Total Length: %u\n", total_length);

        // DP类型
        uint8_t dp_type = data[index++];
        printf("DP Type: %02x\n", dp_type);

        // DP数据长度
        uint8_t dp_data_length = data[index++];
        printf("DP Data Length: %u\n", dp_data_length);

        // DP数据内容
        printf("DP Data: ");
        for (int i = 0; i < dp_data_length; ++i) {
            printf("%02x ", data[index++]);
        }
        printf("\n");

        // 增加DP数据数量计数器
        dp_count++;
    }

    printf("Total DP Data Count: %u\n", dp_count);
}

int main() {
    // 示例数据
    uint8_t data1[] = {0x00, 0x05, 0x6d, 0x01, 0x00, 0x01, 0x01};
    uint8_t data2[] = {0x00, 0x15, 0x6d, 0x01, 0x00, 0x01, 0x01, 0x66, 0x03, 0x00, 0x0c, 0x32, 0x30, 0x31, 0x38, 0x30, 0x34, 0x31, 0x32, 0x31, 0x35, 0x30, 0x37};
    
    // 解析数据
    // printf("Data 1:\n");
    // parse_data(data1, sizeof(data1));
    
    printf("Data 2:\n");
    parse_data(data2, sizeof(data2));

    return 0;
}
