#include "parse_s19_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

#define MAX_LINE_LENGTH 512
#define MAX_DATA_LENGTH 256

typedef enum {
    S_RECORD_SUCCESS = 0,
    S_RECORD_INVALID_PARAM,
    S_RECORD_INVALID_FORMAT,
    S_RECORD_INVALID_TYPE,
    S_RECORD_LENGTH_MISMATCH,
    S_RECORD_CHECKSUM_ERROR,
    S_RECORD_BUFFER_TOO_SMALL,
    S_RECORD_INVALID_HEX
} s_record_status_t;

typedef struct {
    char type;
    uint32_t address;
    uint8_t data[MAX_DATA_LENGTH];
    size_t data_length;
} s_record_t;

typedef struct {
    uint32_t len;
    uint32_t print_num;
} priv_t;

static priv_t priv = {
    .len = 0,
    .print_num = 0
};

int test_parse_s19_file(const char *filepath)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    in_main(filepath);

    return ret;
}

uint8_t hex_to_val(char c) {
    c = toupper(c);
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

void print_hex(const uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

s_record_status_t parse_s19_line(const char *line, s_record_t *record) {
    // 参数检查
    if (line == NULL || record == NULL) {
        return S_RECORD_INVALID_PARAM;
    }

    size_t line_len = strlen(line);
    if (line_len < 4 || line[0] != 'S') {
        return S_RECORD_INVALID_FORMAT;
    }

    // 提取记录类型
    record->type = line[1];
    if (record->type < '0' || record->type > '9') {
        return S_RECORD_INVALID_TYPE;
    }

    // 跳过终止记录
    if (record->type == '7' || record->type == '8' || record->type == '9') {
        return S_RECORD_SUCCESS;
    }

    // 计算十六进制数据长度
    if ((line_len - 2) % 2 != 0) {
        return S_RECORD_INVALID_FORMAT;
    }
    size_t byte_count = (line_len - 2) / 2;

    // 解析十六进制数据
    uint8_t bytes[MAX_LINE_LENGTH/2];
    for (size_t i = 0; i < byte_count; i++) {
        if (!isxdigit(line[2+i*2]) || !isxdigit(line[3+i*2])) {
            return S_RECORD_INVALID_HEX;
        }
        bytes[i] = (hex_to_val(line[2+i*2]) << 4) | hex_to_val(line[3+i*2]);
    }

    // 检查记录长度
    uint8_t rec_len = bytes[0];
    if (rec_len + 1 != byte_count) {
        return S_RECORD_LENGTH_MISMATCH;
    }

    // 计算校验和
    uint8_t checksum = bytes[byte_count - 1];
    uint8_t sum = 0;
    for (size_t i = 0; i < byte_count - 1; i++) {
        sum += bytes[i];
    }
    if ((~sum & 0xFF) != checksum) {
        return S_RECORD_CHECKSUM_ERROR;
    }

    // 解析地址（根据记录类型确定地址长度）
    int addr_len = 0;
    switch (record->type) {
        case '1': addr_len = 2; break;  // S1: 2字节地址
        case '2': addr_len = 3; break;  // S2: 3字节地址
        case '3': addr_len = 4; break;  // S3: 4字节地址
        case '0': addr_len = 2; break;  // S0: 2字节地址（通常为0000）
        default:  addr_len = 0; break;
    }

    record->address = 0;
    for (int i = 0; i < addr_len; i++) {
        record->address = (record->address << 8) | bytes[1 + i];
    }

    // 提取数据
    record->data_length = rec_len - 1 - addr_len;  // 长度 - 类型 - 地址
    if (record->data_length > MAX_DATA_LENGTH) {
        return S_RECORD_BUFFER_TOO_SMALL;
    }
    memcpy(record->data, bytes + 1 + addr_len, record->data_length);

    return S_RECORD_SUCCESS;
}

void print_s_record(const s_record_t *record) {
    if (record == NULL) return;

    printf("\r\n[%s][%d]priv.print_num: %d, priv.len: %d priv.len: %02X\r\n\r\n", __func__, __LINE__, priv.print_num, priv.len, priv.len);

    printf("S%c Record | Addr: 0x%08X | Data[%zu]: ", 
           record->type, record->address, record->data_length);
    print_hex(record->data, record->data_length);

    priv.len += record->data_length;
    priv.print_num ++;
}

// int main(int argc, char *argv[]) {

int in_main(const char *filepath) {
    // if (argc != 2) {
    //     fprintf(stderr, "Usage: %s <s19_file>\n", argv[0]);
    //     return EXIT_FAILURE;
    // }

    // FILE *fp = fopen(argv[1], "r");
    // if (!fp) {
    //     perror("Error opening file");
    //     return EXIT_FAILURE;
    // }

    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];
    s_record_t record;
    int line_num = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        line[strcspn(line, "\r\n")] = '\0';
        
        // 跳过空行和注释
        if (strlen(line) == 0 || line[0] == '#') {
            continue;
        }

        s_record_status_t status = parse_s19_line(line, &record);
        if (status != S_RECORD_SUCCESS) {
            fprintf(stderr, "Error on line %d: ", line_num);
            switch (status) {
                case S_RECORD_INVALID_FORMAT: 
                    fprintf(stderr, "Invalid S-record format\n");
                    break;
                case S_RECORD_INVALID_TYPE:
                    fprintf(stderr, "Invalid S-record type\n");
                    break;
                case S_RECORD_LENGTH_MISMATCH:
                    fprintf(stderr, "Length mismatch\n");
                    break;
                case S_RECORD_CHECKSUM_ERROR:
                    fprintf(stderr, "Checksum error\n");
                    break;
                case S_RECORD_BUFFER_TOO_SMALL:
                    fprintf(stderr, "Data too large for buffer\n");
                    break;
                case S_RECORD_INVALID_HEX:
                    fprintf(stderr, "Invalid hex data\n");
                    break;
                default:
                    fprintf(stderr, "Unknown error\n");
            }
            fclose(fp);
            return EXIT_FAILURE;
        }

        // 处理S0记录的特殊情况
        if (record.type == '0' && record.data_length >= 46) {
            printf("--- Header Information ---\n");
            printf("Software Version: ");
            print_hex(record.data, 10);
            printf("ECU Name: ");
            print_hex(record.data + 10, 6);
            printf("Supplier: ");
            print_hex(record.data + 16, 10);
            printf("Part Number: ");
            print_hex(record.data + 26, 20);
        } else if (record.type != '7' && record.type != '8' && record.type != '9') {
            print_s_record(&record);
        }
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
