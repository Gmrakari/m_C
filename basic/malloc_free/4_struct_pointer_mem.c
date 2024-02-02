#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_PASSWORD_LEN (7)

typedef struct {
    uint8_t passwordLength;
    uint8_t passwordIndex;
    uint8_t times;
    uint8_t status;
    uint8_t effectiveTime[6];
    uint8_t expiryTime[6];
    char password[MAX_PASSWORD_LEN];
    uint8_t scheduleCount;
    uint8_t allDayValid;
    uint8_t startTimeHour;
    uint8_t startTimeMinute;
    uint8_t endTimeHour;
    uint8_t endTimeMinute;
    uint8_t weekLoop;
} __attribute__((packed)) TemporaryPassword_t;

static int test_2() {
    struct data_header_msg_t {
        uint8_t status;            
        uint8_t passwd_group_size;
        uint8_t package_seq_id;
    } __attribute__((packed));

    struct rsp_msg_t {
        struct data_header_msg_t header_msg;
        TemporaryPassword_t *passwd_ptr;
    } __attribute__((packed));

    TemporaryPassword_t passwd_data_list[4];
    int passwd_data_list_len = sizeof(passwd_data_list) / sizeof(passwd_data_list[0]);

    int passwd_str_cnt = 0;

    TemporaryPassword_t tmp = {
        // .passwordLength  = 0,
        // .passwordIndex   = 0,
        .times           = 0x00,
        .status          = 0x00,
        .scheduleCount   = 0x01,
        .allDayValid     = 0x01,
        .startTimeHour   = 0x0A,
        .startTimeMinute = 0x0B,
        .endTimeHour     = 0x0C,
        .endTimeMinute   = 0x0E,
        .weekLoop        = 0xFF,
    };

    uint8_t effect_time[] = {0x14, 0x0A, 0x09, 0x09, 0x31, 0x19};
    uint8_t expiry_time[] = {0x14, 0x0A, 0x09, 0x0A, 0x30, 0x19};
    // char passwd_str[] = {"2024001"};
    uint8_t passwd_str[] = {0x32, 0x30, 0x32, 0x34, 0x30, 0x30, 0x31};
    // strncpy(tmp.password, passwd_str, sizeof(passwd_str));
    memcpy(tmp.password, passwd_str, sizeof(tmp.password));
    memcpy(tmp.effectiveTime, effect_time, sizeof(effect_time));
    memcpy(tmp.expiryTime, expiry_time, sizeof(expiry_time));

    for (int i = 0; i < passwd_data_list_len; i++) {
        passwd_data_list[i].passwordIndex = i + 1;
        strncpy(passwd_data_list[i].effectiveTime, tmp.effectiveTime, sizeof(passwd_data_list[i].effectiveTime));
        strncpy(passwd_data_list[i].expiryTime, tmp.expiryTime, sizeof(passwd_data_list[i].expiryTime));

        if (i % 2 == 0) {
            snprintf(passwd_data_list[i].password, sizeof(passwd_data_list[i].password), "%s%d", passwd_str, i);
        } else {
            snprintf(passwd_data_list[i].password, sizeof(passwd_data_list[i].password), "%s", passwd_str);
        }

        passwd_data_list[i].passwordLength  = strlen(passwd_data_list[i].password);

        passwd_data_list[i].times           = tmp.times;
        passwd_data_list[i].status          = tmp.status;
        passwd_data_list[i].scheduleCount   = tmp.scheduleCount;
        passwd_data_list[i].allDayValid     = tmp.allDayValid;

        passwd_data_list[i].startTimeHour   = tmp.startTimeHour;
        passwd_data_list[i].startTimeMinute = tmp.startTimeMinute;
        passwd_data_list[i].endTimeHour     = tmp.endTimeHour;
        passwd_data_list[i].endTimeMinute   = tmp.endTimeMinute;
        passwd_data_list[i].weekLoop        = tmp.weekLoop;
    }

    struct rsp_msg_t rsp = {
        .header_msg = {.status = 0x01, .passwd_group_size = passwd_data_list_len, .package_seq_id = 0x00},
        .passwd_ptr = passwd_data_list,
    };

    uint8_t *ptr = (uint8_t *)&rsp;
    int len = sizeof(rsp.header_msg) + sizeof(TemporaryPassword_t) * passwd_data_list_len;

    int data_len_size = sizeof(TemporaryPassword_t) * passwd_data_list_len;

    ptr = ptr + 2 + 8;

    // printf("ptr:\r\n");
    // for (int i = 0; i < data_len_size; i++) {
    //     printf("%02X", ptr[i]);
    // }
    // printf("\r\n");

    int out_ptr_len = sizeof(struct data_header_msg_t) + sizeof(TemporaryPassword_t) * passwd_data_list_len;

    uint8_t *out_ptr = malloc(sizeof(uint8_t) * out_ptr_len);
    if (!out_ptr) return -1;

    memset(out_ptr, 0x00, out_ptr_len);

    size_t offset = 0;

    memcpy(out_ptr + offset, &rsp.header_msg, sizeof(struct data_header_msg_t));
    offset += sizeof(struct data_header_msg_t);

    memcpy(out_ptr + offset, passwd_data_list, sizeof(TemporaryPassword_t) * passwd_data_list_len);
    offset += sizeof(TemporaryPassword_t) * passwd_data_list_len;

    printf("\r\n");
    uint8_t *pptr = out_ptr;
    for (int i = 0; i < offset; i++) {
        printf("%02X", pptr[i]);
    }
    printf("\r\n");

    if (out_ptr) {
        free(out_ptr);
        out_ptr = NULL;
    }

    return 0;
}

int main() {
    test_2();
    return 0;
}
