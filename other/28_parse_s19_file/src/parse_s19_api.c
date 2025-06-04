#include "parse_s19_api.h"

#include "calc_crc32.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

#define TMP_FILE_PATH "../res/1.s19"

int in_main(const char *filepath);
int get_s19_file_data_len(uint32_t *len);
int get_s19_file_data_addr(uint32_t *addr);

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
    crc32_context_t crc_ctx;
} priv_t;

static priv_t priv = {
    .crc_ctx = {.crc = 0, .table = NULL},
    .len = 0,
    .print_num = 0
};

static int parse_s19_get_addr_and_get_len(void);
static int parse_s19_file_info(void);
static int parse_s19_get_data_buff(uint8_t **out, int *olen);

typedef struct {
    uint8_t is_parse;           // 是否已经解析
    uint32_t start_addr;        // s19数据开始地址
    uint32_t data_size;         // s19数据大小
} s19_file_info_t;

static s19_file_info_t s19_file_info = {
    .is_parse = 0,
    .start_addr = UINT32_MAX,
    .data_size = 0
};

static int _fmt_dump_hex_data(const unsigned char *data, unsigned int len)
{
    #define BYTES_PER_LINE              16
    if (!data || !len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    unsigned int i;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);

        if ((i + 1) % BYTES_PER_LINE == 0) {
            printf("\n");
        }
    }

    printf("\r\n");

    return 0;
}

static int test_get_file_addr_and_file_len()
{
    // (void)filepath;
    int rc = 0;
    uint32_t addr = 0;
    uint32_t len = 0;

    rc = get_s19_file_data_addr(&addr);printf("[%s][%d]\r\n", __func__, __LINE__);
    if (rc != 0) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]get_s19_file_data_addr failed, rc: %d\r\n", __func__, __LINE__, rc);
        return rc;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    printf("[%s][%d]addr: %08X\r\n", __func__, __LINE__, addr);

    rc = get_s19_file_data_len(&len);printf("[%s][%d]\r\n", __func__, __LINE__);
    if (rc != 0) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]get_s19_file_data_len failed, rc: %d\r\n", __func__, __LINE__, rc);
        return rc;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    printf("[%s][%d]len: %08X\r\n", __func__, __LINE__, len);


    uint8_t *buff = NULL;
    uint32_t buflen = 0;
    rc = parse_s19_get_data_buff(&buff, &buflen);
    if (rc != 0) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]parse_s19_get_data_buff failed, rc: %d\r\n", __func__, __LINE__, rc);
        return rc;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    _fmt_dump_hex_data(buff, buflen);

    free(buff);
    buff = NULL;

    return rc;
}


static int test_crc32_data()
{
    int rc = 0;

    uint32_t len = 0;

    extern uint8_t crc32_origin_data[];
    extern uint32_t crc32_origin_data_len;
    uint32_t len = 0;
    len = crc32_origin_data_len;


    uint8_t *ptr = NULL;

    ptr = crc32_origin_data;

    crc32_init(&priv.crc_ctx);

    printf("[%s][%d]len: %d (%02X)\r\n", __func__, __LINE__, len, len);

    crc32_update(&priv.crc_ctx, ptr, len);

    // uint32_t crc32 = crc32_finalize(&priv.crc_ctx);

    uint32_t crc32 = calculate_crc32(ptr, len);

    // 2a 53 8a dd
    printf("[%s][%d]crc32: %08X\r\n", __func__, __LINE__, crc32);

    crc32 = calculate_crc32(ptr, len);
    
    printf("[%s][%d]crc32: %08X\r\n", __func__, __LINE__, crc32);

    return rc;
}

int test_parse_s19_file(const char *filepath)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    #if 1
    in_main(filepath);

    // (void)filepath;
    // test_get_file_addr_and_file_len();

    #endif

    #if 1
    test_crc32_data();
    #endif

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

    // printf("\r\n[%s][%d]priv.print_num: %d, priv.len: %d priv.len: %02X\r\n\r\n", __func__, __LINE__, priv.print_num, priv.len, priv.len);

    #if 0
    printf("S%c Record | Addr: 0x%08X | Data[%zu]: ", 
           record->type, record->address, record->data_length);
    print_hex(record->data, record->data_length);

    #endif

    // printf("[%s][%d]len: %d %02X\r\n", __func__, __LINE__, record->data_length, record->data_length);
    crc32_update(&priv.crc_ctx, record->data, record->data_length);

    priv.len += record->data_length;
    priv.print_num ++;
}

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

    crc32_init(&priv.crc_ctx);

    // fgets(line, sizeof(line), fp);

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
    fp = NULL;

    uint8_t tmp_fill_data[] = {
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
    };
    int tmp_fill_data_len = sizeof(tmp_fill_data);
    crc32_update(&priv.crc_ctx, tmp_fill_data, tmp_fill_data_len);
    uint32_t crc32_val = crc32_finalize(&priv.crc_ctx);
    printf("[%s][%d]crc32_val: %08X\r\n", __func__, __LINE__, crc32_val);

    return EXIT_SUCCESS;
}

static int parse_s19_get_addr_and_get_len(void)
{
    int rc = 0;

    rc = parse_s19_file_info();
    if (rc != 0) {
        printf("[%s][%d]parse_s19_file_info failed, rc: %d\r\n", __func__, __LINE__, rc);
        return rc;
    }

    return rc;
}

static int parse_s19_get_data_buff(uint8_t **out, int *olen)
{
    if (!olen) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return -1;
    }

    int rc = 0;

    if (!s19_file_info.is_parse) {
        // printf("[%s][%d]s19 file is not parse finish\r\n", __func__, __LINE__);
        rc = parse_s19_get_addr_and_get_len();
        if (rc != 0) {
            printf("[%s][%d]parse_s19_get_addr_and_get_len failed, rc: %d\r\n", __func__, __LINE__, rc);
            return rc;
        }
    }

    const char filepath[] = TMP_FILE_PATH;
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("[%s][%d]fopen %s failed\r\n", __func__, __LINE__, filepath);
        rc = -1;
        return rc;
    }

    uint32_t buflen = s19_file_info.data_size;
    uint8_t *buff = (uint8_t *)malloc(buflen);
    if (!buff) {
        printf("[%s][%d]oom, malloc buflen: %d failed\r\n", __func__, __LINE__, buflen);
        fclose(fp);
        fp = NULL;
        rc = -1;
        return rc;
    }
    memset(buff, 0x00, buflen);

    char line[512];
    int line_num = 0;
    s_record_t record;
    uint32_t offset = 0;
    s_record_status_t status = S_RECORD_SUCCESS;

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 0 || line[0] != 'S') 
            continue;

        status = parse_s19_line(line, &record);
        if (status != S_RECORD_SUCCESS) 
            continue;

        // 只处理S1、S2、S3数据记录
        if (record.type == '1' || record.type == '2' || record.type == '3') {
            offset = record.address - s19_file_info.start_addr;
            memcpy(buff + offset, record.data, record.data_length);
        }
    }

    fclose(fp);
    fp = NULL;

    *out = buff;
    *olen = buflen;

    return rc;
}

static int parse_s19_file_info(void)
{
    const char filepath[] = TMP_FILE_PATH;

    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("[%s][%d]fopen %s failed\r\n", __func__, __LINE__, TMP_FILE_PATH);
        return -1;
    }

    int rc = 0;

    char line[512];
    s_record_t record;
    int line_num = 0;

    uint32_t max_addr;      // 最大内存地址

    while (fgets(line, sizeof(line), fp)) {
        line_num++;
        line[strcspn(line, "\r\n")] = '\0';

        if (strlen(line) == 0 || line[0] != 'S') 
            continue;

        s_record_status_t status = parse_s19_line(line, &record);
        if (status != S_RECORD_SUCCESS) {
            printf("[%s][%d]parse_s19_line failed, line_num: %d, status: %d\r\n", __func__, __LINE__, line_num, status);            continue;
            // continue;
            rc = -1;
            break;
        }

        // 只处理S1、S2、S3数据记录
        if (record.type == '1' || record.type == '2' || record.type == '3') {
            if (record.address < s19_file_info.start_addr)
                s19_file_info.start_addr = record.address;

            uint32_t end_address = record.address + record.data_length;
            if (end_address > max_addr)
                max_addr = end_address;

            s19_file_info.data_size += record.data_length;
        }
    }

    fclose(fp);
    fp = NULL;
    s19_file_info.is_parse = 1;

    return rc;
}

int get_s19_file_data_addr(uint32_t *addr)
{
    if (!addr) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return -1;
    }

    int rc = 0;

    if (!s19_file_info.is_parse) {
        // printf("[%s][%d]s19 file is not parse finish\r\n", __func__, __LINE__);
        rc = parse_s19_get_addr_and_get_len();
        if (rc != 0) {
            printf("[%s][%d]parse_s19_get_addr_and_get_len failed, rc: %d\r\n", __func__, __LINE__, rc);
            return rc;
        }
    }

    *addr = s19_file_info.start_addr;
    return rc;
}

int get_s19_file_data_len(uint32_t *len)
{
    if (!len) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return -1;
    }

    int rc = 0;

    if (!s19_file_info.is_parse) {
        // printf("[%s][%d]s19 file is not parse finish\r\n", __func__, __LINE__);
        rc = parse_s19_get_addr_and_get_len();
        if (rc != 0) {
            printf("[%s][%d]parse_s19_get_addr_and_get_len failed, rc: %d\r\n", __func__, __LINE__, rc);
            return rc;
        }
    }

    *len = s19_file_info.data_size;
    return rc;
}
