#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    uint16_t header;                                 /* 帧头    */
    uint16_t len;                                    /* 数据长度 */
    uint8_t data[0];                                 /* 数据     */
    uint8_t checksum;                                /* 校验位   */
} __attribute__((packed)) frame_t;

static uint8_t _get_checksum(const uint8_t *buffer, uint16_t buffer_length)
{
    uint16_t sum = 0;
    for (uint16_t i = 0; i < buffer_length; i++) {
        sum += buffer[i];
    }
    return sum & 0xFF;
}

static void _test_01()
{
    printf("test_01:\r\n");
    frame_t *frame = (frame_t*)malloc(sizeof(frame_t));
    if (!frame) return ;

    char data[] = {0x41,0x30,0x42,0x31,0x43,0x32,0x44,0x33,0x45};

    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    uint16_t header = 0x55aa;
    frame->header = (header << 8) | (header >> 8);
    frame->len = (data_len << 8) | (data_len >> 8);
    
    memcpy(frame->data, data, data_len);

    // 帧包的长度 + 数据的长度 - (帧包中的checksum的长度 1)
    uint16_t cal_checksum_len = sizeof(frame) + data_len - 1;
    frame->checksum = _get_checksum((uint8_t *)frame, cal_checksum_len);

    uint8_t *err_ptr = (uint8_t *)frame;
    size_t total_len = cal_checksum_len + 1;
    printf("err print:\r\n");
    for (int i = 0; i < total_len; i++) {
        printf("%02X ", err_ptr[i]);
    }
    printf("\r\n\r\n");

    return ;
}

static void _test_02()
{
    printf("test_02:\r\n");
    frame_t *frame = (frame_t*)malloc(sizeof(frame_t));
    if (!frame) return ;

    char data[] = {0x41,0x30,0x42,0x31,0x43,0x32,0x44,0x33,0x45};

    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    uint16_t header = 0x55aa;
    frame->header = (header << 8) | (header >> 8);
    frame->len = (data_len << 8) | (data_len >> 8);
    
    // 数据长度 + 帧包长度
    uint16_t ptr_len = data_len + sizeof(frame_t);

    uint8_t *ptr = malloc(sizeof(uint8_t) * ptr_len);
    if (!ptr) 
        goto exit;

    memset(ptr, 0, ptr_len);

    uint16_t offset = 0;

    memcpy(ptr + offset, &frame->header, sizeof(frame->header));
    offset += sizeof(frame->header);

    memcpy(ptr + offset, &frame->len, sizeof(frame->len));
    offset += sizeof(frame->len);

    memcpy(ptr + offset, data, sizeof(data));
    offset += sizeof(data);

    // header + len + data
    uint16_t cal_checksum_len = offset;
    uint8_t get_checksum = _get_checksum((uint8_t *)ptr, cal_checksum_len);

    memcpy(ptr + offset, &get_checksum, sizeof(get_checksum));
    offset += sizeof(get_checksum);

    printf("corret_ptr:\r\n");
    uint8_t *corret_ptr = ptr;
    size_t len = offset;
    for (int i = 0; i < len; i++) {
        printf("%02X ", corret_ptr[i]);
    }
    printf("\r\n");

exit:

    if (frame) { free(frame); frame = NULL; } 

    return ;
}

int main() 
{
    _test_01();
    
    _test_02();
}