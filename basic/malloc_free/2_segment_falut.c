#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int test_2() {
    struct data_header_msg_t {
        uint8_t status;            /* 获取密码结果标识, 0x00失败, 0x01成功 */
        uint8_t passwd_group_size; /* 密码组数量 */
        uint8_t *package_seq_num;  /* 包序列号 */
    } __attribute__((packed));

    struct passwd_data_list_t {
        struct data_header_msg_t header_msg;
    } __attribute__((packed));

    uint8_t *ptr = NULL;

    uint8_t data[] = {0xA0, 0xB0, 0xC0, 0xD0};
    uint8_t data_len = sizeof(data) / sizeof(data[0]);

    printf("data_len: %d\r\n", data_len);
    printf("sizeof(struct data_header_msg_t): %zu\r\n", sizeof(struct data_header_msg_t));

    struct data_header_msg_t msg = {0};

    msg.status = 0x01;
    msg.passwd_group_size = data_len;

    msg.package_seq_num = NULL;
    msg.package_seq_num = malloc(sizeof(uint8_t) * data_len);
    if (!msg.package_seq_num)
        return -1;

    memset(msg.package_seq_num, 0x00, sizeof(uint8_t) * data_len);
    memcpy(msg.package_seq_num, data, data_len);

    // printf("package_seq_num:%d")

    for (int i = 0; i < data_len; i++) {
        printf("package_seq_num:%02X\r\n", msg.package_seq_num[i]);
    }

    ptr = (uint8_t *)&msg;
    int len = sizeof(struct data_header_msg_t) + data_len;

    size_t buf_len = sizeof(uint8_t) * 2 + data_len;
    uint8_t *buf = malloc(buf_len);

    memcpy(buf, ptr, 2);
    memcpy(buf + 2, ptr + 2 + sizeof(uint8_t *), data_len);

    printf("buf:\r\n");
    for (int i = 0;i < buf_len; i++) {
        printf("%02X", buf[i]);
    }
    printf("\r\n");

    if (buf) {
        free(buf);
        buf = NULL;
    }

    printf("ptr:\r\n");
    for (int i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

    if (msg.package_seq_num) {
        free(msg.package_seq_num);
        msg.package_seq_num = NULL;
    }

    return 0;
}

int test_1() {
    struct data_header_msg_t {
        uint8_t status;            /* 获取密码结果标识, 0x00失败, 0x01成功 */
        uint8_t passwd_group_size; /* 密码组数量 */
        uint8_t *package_seq_num;  /* 包序列号 */
    } __attribute__((packed));

    uint8_t *ptr = NULL;

    uint8_t data[] = {0xA0, 0xB0, 0xC0, 0xD0};
    uint8_t data_len = sizeof(data) / sizeof(data[0]);

    printf("data_len: %d\r\n", data_len);
    printf("sizeof(struct data_header_msg_t): %zu\r\n", sizeof(struct data_header_msg_t));

    struct data_header_msg_t *msg = malloc(sizeof(struct data_header_msg_t));
    if (!msg) return -1;

    msg->status = 0x01;
    msg->passwd_group_size = data_len;

    msg->package_seq_num = malloc(sizeof(uint8_t) * data_len);
    if (!msg->package_seq_num) {
        free(msg);
        msg = NULL;
        return -1;
    }

    memset(msg->package_seq_num, 0x00, sizeof(uint8_t) * data_len);

    ptr = (uint8_t *)msg;

    memcpy(ptr + sizeof(struct data_header_msg_t), data, data_len);

    int len = sizeof(struct data_header_msg_t) + data_len;

    printf("ptr:\r\n");
    for (int i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

    if (msg->package_seq_num) {
        free(msg->package_seq_num);
        msg->package_seq_num = NULL;
    }

    if (msg) {
        free(msg);
        msg = NULL;
    }

    return 0;
}

int main() {
    // test_1();
    test_2();

    return 0;
}
