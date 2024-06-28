#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint16_t header;                                 /* 帧头    */
    uint8_t version;                                 /* 数据版本 */
    uint8_t cmd;                                     /* 命令码   */
    uint16_t len;                                    /* 数据长度 */
    uint8_t checksum;                                /* 校验位   */
    uint8_t data[0];                                 /* 数据     */
} __attribute__((packed)) frame_t;

static uint8_t _get_checksum(const uint8_t *data, uint16_t len)
{
    uint8_t csum = 0;
    for (uint16_t i = 0; i < len; i++) 
        csum += data[i];
    return csum & 0xFF;
}

static void _gen_checksum(frame_t )
{
    // uint8_t data[] = {0x55, 0xaa, 0x00, 0x02, 0x00, 0x00};

    uint8_t data[] = {0x55,0xAA,0x00,0x21,0x01,0x63,0x7B,0x5C,0x22,0x6D,0x73,0x67,0x49,0x64,0x5C,0x22,0x3A,0x5C,0x22,0x31,0x37,0x39,0x33,0x32,0x32,0x35,0x37,0x30,0x36,0x35,0x37,0x32,0x34,0x30,0x36,0x37,0x38,0x34,0x5C,0x22,0x2C,0x5C,0x22,0x74,0x73,0x5C,0x22,0x3A,0x31,0x37,0x31,0x36,0x33,0x37,0x33,0x32,0x39,0x39,0x2C,0x5C,0x22,0x76,0x65,0x72,0x73,0x69,0x6F,0x6E,0x5C,0x22,0x3A,0x5C,0x22,0x31,0x2E,0x30,0x5C,0x22,0x2C,0x5C,0x22,0x74,0x6F,0x70,0x69,0x63,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x73,0x79,0x73,0x5C,0x22,0x3A,0x7B,0x5C,0x22,0x61,0x63,0x6B,0x5C,0x22,0x3A,0x31,0x7D,0x2C,0x5C,0x22,0x64,0x61,0x74,0x61,0x5C,0x22,0x3A,0x7B,0x5C,0x22,0x73,0x75,0x62,0x55,0x75,0x69,0x64,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x6F,0x70,0x65,0x72,0x61,0x74,0x6F,0x72,0x54,0x79,0x70,0x65,0x5C,0x22,0x3A,0x31,0x2C,0x5C,0x22,0x70,0x77,0x64,0x44,0x61,0x74,0x61,0x5C,0x22,0x3A,0x7B,0x5C,0x22,0x74,0x79,0x70,0x65,0x5C,0x22,0x3A,0x38,0x2C,0x5C,0x22,0x69,0x6E,0x64,0x65,0x78,0x5C,0x22,0x3A,0x38,0x30,0x31,0x2C,0x5C,0x22,0x64,0x65,0x76,0x69,0x63,0x65,0x55,0x73,0x65,0x72,0x49,0x64,0x5C,0x22,0x3A,0x5C,0x22,0x30,0x5C,0x22,0x2C,0x5C,0x22,0x70,0x77,0x64,0x5C,0x22,0x3A,0x5C,0x22,0x31,0x30,0x33,0x32,0x32,0x37,0x30,0x32,0x5C,0x22,0x2C,0x5C,0x22,0x74,0x69,0x6D,0x65,0x54,0x79,0x70,0x65,0x5C,0x22,0x3A,0x31,0x2C,0x5C,0x22,0x61,0x63,0x74,0x69,0x76,0x65,0x54,0x69,0x6D,0x65,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x65,0x78,0x70,0x69,0x72,0x65,0x54,0x69,0x6D,0x65,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x73,0x74,0x61,0x72,0x74,0x54,0x69,0x6D,0x65,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x65,0x6E,0x64,0x54,0x69,0x6D,0x65,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x2C,0x5C,0x22,0x6C,0x6F,0x6F,0x70,0x73,0x5C,0x22,0x3A,0x6E,0x75,0x6C,0x6C,0x7D,0x7D,0x2C,0x5C,0x22,0x63,0x6F,0x64,0x65,0x5C,0x22,0x3A,0x30,0x7D};

    size_t len = sizeof(data) / sizeof(data[0]);

    uint8_t checksum = _get_checksum(data, len);

    printf("checksum: %02X\r\n", checksum);
}

static int _string_to_hex(const char *str, unsigned char **out, int *olen)
{
    if (!str) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    int str_len = strlen(str);

    // printf("[%s][%d]str_len: %d\r\n", __func__, __LINE__, str_len);

    // *olen = str_len / 2;
    *olen = str_len;
    unsigned char *buf = (unsigned char*)malloc(sizeof(unsigned char) * (*olen));
    if (!buf) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }
    memset(buf, 0x00, (*olen));

    // for (int i = 0; i < *olen; i++) {
    //     sscanf(&str[i * 2], "%2hhx", &buf[i]);
    // }

    for (int i = 0; i < (*olen); i++) {
        buf[i] = (unsigned char)str[i];
    }

    *out = buf;

    return ret;
}

static int _dump_data(unsigned char *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("dump data:\r\n");
    unsigned char *ptr = data;
    for (int i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
        if (i != len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    return 0;
}

static int _fmt_dump_data(unsigned char *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("fmt dump data:\r\n");
    unsigned char *ptr = data;
    for (int i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
        if (i != len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    return 0;
}

static unsigned short _swap_uin16_func(unsigned short val)
{
    return (val << 8) | (val >> 8);
}

static int _gen_checksum_app(unsigned char command, const char *string)
{
    if (!string) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }
    const char *str = string; 

    unsigned char *hex_data = NULL;
    int hex_data_len = 0;
    int ret = 0;
    ret = _string_to_hex(str, (unsigned char**)&hex_data, &hex_data_len);
    if (ret != 0) {
        printf("[%s][%d]_string_to_hex err!\r\n", __func__, __LINE__);
        return -1;
    }

    unsigned short data_len = 0;
    data_len = (unsigned short)hex_data_len;

    unsigned char header_info[] = {0x55, 0xaa, 0x00};
    unsigned char cmd = command;
    unsigned char checksum = 0;

    int buflen = sizeof(header_info) + sizeof(cmd) + sizeof(data_len) + hex_data_len + sizeof(checksum);
    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * buflen);
    if (!buffer) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        if (hex_data) {
            free(hex_data);
            hex_data = NULL;
        }
        return -1;
    }
    memset(buffer, 0x00, buflen);

    unsigned char *ptr = buffer;
    int offset = 0;

    memcpy(ptr + offset, &header_info, sizeof(header_info));
    offset += sizeof(header_info);

    memcpy(ptr + offset, &cmd, sizeof(unsigned char));
    offset += sizeof(unsigned char);

    data_len = _swap_uin16_func(data_len);

    memcpy(ptr + offset, &data_len, sizeof(unsigned short));
    offset += sizeof(unsigned short);

    if (hex_data) {
        // _dump_data(buffer, hex_data_len);

        memcpy(ptr + offset, hex_data, hex_data_len);
        offset += hex_data_len;

        free(hex_data);
    }

    if (buffer) {
        checksum = _get_checksum(buffer, buflen - 1);

        memcpy(ptr + offset, &checksum, sizeof(checksum));
        offset += sizeof(unsigned char);

        _dump_data(buffer, buflen);

        // printf("%02X", checksum);

        free(buffer);
        buffer = NULL;
    }

    return 0;
}

static int _get_null_data_checksum(unsigned char command)
{
    unsigned char header_info[] = {0x55, 0xaa, 0x00};
    unsigned char cmd = command;
    unsigned short data_len = 0;
    unsigned char checksum = 0;

    int buflen = sizeof(header_info) + sizeof(cmd) + sizeof(data_len) + sizeof(checksum);
    unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * buflen);
    if (!buffer) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }
    memset(buffer, 0x00, buflen);

    unsigned char *ptr = buffer;

    for (int i = 0; i < sizeof(header_info); i++) {
        *ptr = header_info[i];
        ptr += sizeof(unsigned char);
    }

    *ptr = cmd;
    ptr += sizeof(unsigned char);

    *(unsigned short *)ptr = data_len;
    ptr += sizeof(unsigned short);

    checksum = _get_checksum(buffer, buflen - 1);

    *ptr = checksum;
    ptr += sizeof(unsigned char);

    _dump_data(buffer, buflen);

    free(buffer);
    buffer = NULL;

    return 0;
}

static int _get_null_data_checksum_test()
{
    unsigned char add_cmd = 0x21;
    unsigned char del_cmd = 0x0D;
    unsigned char query_cmd = 0x0E;

    unsigned char get_pid = 0xb0;
    unsigned char get_uuid = 0xb1;
    unsigned char get_secret = 0xb2;
    unsigned char get_mac = 0xb3;
    unsigned char get_all = 0xb7;

    int ret = 0;
    // printf("add cmd test:\r\n");
    // ret = _get_null_data_checksum(add_cmd);
    // if (ret != 0) {
    //     printf("[%s][%d]gen add checksum err!\r\n", __func__, __LINE__);
    //     return -1;
    // }

    // printf("\r\ndel cmd test:\r\n");
    // ret = _get_null_data_checksum(del_cmd);
    // if (ret != 0) {
    //     printf("[%s][%d]gen del checksum err!\r\n", __func__, __LINE__);
    //     return -1;
    // }

    printf("\r\nquery cmd test:\r\n");
    ret = _get_null_data_checksum(query_cmd);
    if (ret != 0) {
        printf("[%s][%d]gen query checksum err!\r\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}

static int _get_triple_info_checksum()
{
    typedef struct {
        unsigned char *str;
        unsigned char value;
    } __attribute__((packed)) dev_info_t;

    dev_info_t get_info[] = {
        {"pid", 0xb0},
        {"uuid", 0xb1},
        {"secret", 0xb2},
        {"mac", 0xb7},
    };

    int ret = 0;

    int get_info_len = sizeof(get_info) / sizeof(get_info[0]);

    for (int i = 0; i < get_info_len; i++) {
        printf("%s\r\n", get_info[i].str);
        ret = _get_null_data_checksum(get_info[i].value);
        if (ret != 0) {
            printf("[%s][%d]gen %s checksum err!\r\n", __func__, __LINE__, get_info[i].str);
            return -1;
        }
    }

    return 0;
}

static int _add_test()
{
    unsigned char cmd = 0x21;

    #if 0
    const char *str1 = "{\"msgId\":\"1793225706572406784\",\"ts\":1716373299,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":1,\"pwdData\":{\"type\":8,\"index\":801,\"deviceUserId\":\"0\",\"pwd\":\"12312312\",\"timeType\":1,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";
    const char *str2 = "{\"msgId\":\"1793225706572406784\",\"ts\":1716373299,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":1,\"pwdData\":{\"type\":8,\"index\":802,\"deviceUserId\":\"0\",\"pwd\":\"45645645\",\"timeType\":1,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";
    const char *str3 = "{\"msgId\":\"1793225706572406784\",\"ts\":1716373299,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":1,\"pwdData\":{\"type\":8,\"index\":803,\"deviceUserId\":\"0\",\"pwd\":\"32131232\",\"timeType\":1,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";

    const char *str[3] = {str1, str2, str3};
    int arr_len = sizeof(str) / sizeof(str[0]);

    int ret = 0;

    for (int i = 0; i < arr_len; i++) {
        printf("===========start:%d============\r\n", i);
        ret = _gen_checksum_app(cmd, str[i]);
        if (ret != 0) {
            printf("_gen_checksum_app err!\r\n");
            return -1;
        }
        printf("***********end***********\r\n\r\n");
    }

    #endif


    return 0;
}

static int _del_test()
{
    unsigned char cmd = 0x0E;
    const char *str1 = "{\"msgId\":\"1795642337355018241\",\"ts\":1716949461,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":2,\"pwdData\":{\"type\":null,\"index\":801,\"deviceUserId\":null,\"pwd\":null,\"timeType\":null,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";
    const char *str2 = "{\"msgId\":\"1795642337355018242\",\"ts\":1716949462,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":2,\"pwdData\":{\"type\":null,\"index\":802,\"deviceUserId\":null,\"pwd\":null,\"timeType\":null,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";
    const char *str3 = "{\"msgId\":\"1795642337355018243\",\"ts\":1716949463,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":2,\"pwdData\":{\"type\":null,\"index\":803,\"deviceUserId\":null,\"pwd\":null,\"timeType\":null,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";

    const char *str[3] = {str1, str2, str3};
    int arr_len = sizeof(str) / sizeof(str[0]);

    int ret = 0;

    for (int i = 0; i < arr_len; i++) {
        printf("===========start============\r\n");
        ret = _gen_checksum_app(cmd, str[i]);
        if (ret != 0) {
            printf("_gen_checksum_app err!\r\n");
            return -1;
        }
        printf("===========end===============\r\n");
    }

    return 0;
}

static int _modify_str_test()
{
    const char *str1 = "{\"msgId\":\"1795642337355018241\",\"ts\":1716949461,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":2,\"pwdData\":{\"type\":null,\"index\":801,\"deviceUserId\":null,\"pwd\":null,\"timeType\":null,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";
    int str_len = strlen(str1) + 1;

    char *buffer = malloc(str_len);
    if (!buffer) {
        printf("buffer malloc err!\r\n");
        return -1;
    }
    memset(buffer, 0x00, str_len);

    strncpy(buffer, str1, str_len);

    printf("%s\r\n", buffer);

    char dest_val[] = "803";

    const char *target = "index";
    char *pos = strstr(buffer, target);
    if (pos) {
        memcpy(pos + 7, &dest_val, sizeof(dest_val) - 1);
    } else {
        printf("Target substring not found!\r\n");
    }

    printf("Modified buffer: \r\n%s\r\n", buffer);

    if (buffer) {
        free(buffer);
        buffer = NULL;
    }

    return 0;
}

static int _add_with_idx()
{
    // char index[] = "801";
    // char index[] = "802";
    char index[] = "803";
    unsigned char cmd = 0x21;
    int ret = 0;

    printf("===========start============\r\n");
    ret = _gen_checksum_app(cmd, index);
    if (ret != 0) {
        printf("_gen_checksum_app err!\r\n");
        return -1;
    }
    printf("***********end***********\r\n\r\n");
}

static int _del_with_idx()
{
    char index1[] = "801";
    char index2[] = "802";
    char index3[] = "803";
    unsigned char cmd = 0x0D;
    int ret = 0;

    char *index_arr[] = {index1, index2, index3};
    int arr_len = sizeof(index_arr) / sizeof(index_arr[0]);

    for (int i = 0;i < arr_len; i++) {
        printf("===========start:%d============\r\n", i);
        ret = _gen_checksum_app(cmd, index_arr[i]);
        if (ret != 0) {
            printf("_gen_checksum_app err!\r\n");
            return -1;
        }
        printf("***********end***********\r\n\r\n");
    }

    return ret;
}

static int _set_triple_info_test()
{
    unsigned char cmd = 0xB8;
    const char *str = "{\"pid\":\"FNj2Raewe9TrOs\",\"uuid\":\"rn01226bba3ebb82\",\"secret\":\"34a040281b6340d3a30f7f9efa4385ce\",\"mac\":\"444AD700A579\"}";

    int ret = 0;
    ret = _gen_checksum_app(cmd, str);
    if (ret != 0) {
        printf("_gen_checksum_app err!\r\n");
        return -1;
    }

    return ret;
}

int main()
{
    // _get_null_data_checksum_test();

    // _add_test();

    // _add_with_idx();

    // _del_with_idx();

    // _del_test();

    // _modify_str_test();

    // _set_triple_info_test();

    _get_triple_info_checksum();

    return 0;
}
