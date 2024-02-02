#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_PASSWORD_LEN (10)

typedef struct {
    uint8_t passwordLength;    // Length of the password
    uint16_t passwordIndex;    // Index of the password
    uint8_t effectiveTime[6];  // Effective start time of the password
    uint8_t expiryTime[6];     // Expiry time of the password
    char password[MAX_PASSWORD_LEN]; // Temporary password
    uint8_t scheduleCount;     // Number of schedule rules
    uint8_t weekLoop;          // Week loop rule for recurrence
} TemporaryPassword_t;

static int test_2() {
    struct data_header_msg_t {
        uint8_t status;            
        uint8_t passwd_group_size;
        uint8_t *package_seq_num; 
    } __attribute__((packed));

    TemporaryPassword_t passwd_data_list[4];
    int passwd_data_list_len = sizeof(passwd_data_list) / sizeof(passwd_data_list[0]);

    uint8_t *seq_num = malloc(sizeof(uint8_t) * passwd_data_list_len);
    if (!seq_num) return -1;

    uint8_t seq_num_list[] = {0x00, 0x01, 0x02, 0x03};

    TemporaryPassword_t tmp = {
        .passwordLength = 6,
        .passwordIndex = 0,
        .scheduleCount = 0,
        .weekLoop = 1,
    };

    int passwd_str_cnt = 0;
    char passwd_str[] = {"20241010"};
    uint8_t effect_time[] = {0x14, 0x0A, 0x09, 0x09, 0x31, 0x19};
    uint8_t expiry_time[] = {0x14, 0x0A, 0x09, 0x0A, 0x30, 0x19};
    strncpy(tmp.password, passwd_str, sizeof(passwd_str));
    strncpy(tmp.effectiveTime, effect_time, sizeof(tmp.effectiveTime));
    strncpy(tmp.expiryTime, expiry_time, sizeof(tmp.expiryTime));

    for (int i = 0; i < passwd_data_list_len; i++) {
        passwd_data_list[i].passwordLength = tmp.passwordLength;
        passwd_data_list[i].passwordIndex = i;
        strncpy(passwd_data_list[i].effectiveTime, tmp.effectiveTime, sizeof(tmp.effectiveTime));
        snprintf(passwd_data_list[i].password, sizeof(passwd_data_list[i].password), "%s%d", passwd_str, i);
        passwd_data_list[i].scheduleCount = 1;
        passwd_data_list[i].weekLoop = 0;
    }

    struct rsp_msg_t {
        struct data_header_msg_t header_msg;
        TemporaryPassword_t *passwd_data_ptr;
    } __attribute__((packed)) rsp = {.header_msg = {0}, .passwd_data_ptr = NULL};


    rsp.header_msg.status = 0x01;
    rsp.header_msg.passwd_group_size = passwd_data_list_len;
    rsp.header_msg.package_seq_num = seq_num_list;
    rsp.passwd_data_ptr = passwd_data_list;

    uint8_t *ptr = NULL;

    ptr = (uint8_t *)&rsp;
    int len = sizeof(struct rsp_msg_t);

    printf("ptr:\r\n");
    for (int i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

    return 0;
}

int main() {
    test_2();
    return 0;
}
