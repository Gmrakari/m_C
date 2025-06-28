#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_FRAGMENT_SIZE        (480)
#define FRAGMENT_HDR_SIZE        (8)
#define FRAGMENT_CHKSUM_SIZE     (2)

// 分片数据结构
typedef struct {
    uint8_t     msg_type;       /* 0xFF 为分片报文 */
    uint8_t     last_frag;      /* 1: 最后一个分片；0: 还有其他分片 */
    uint16_t    msg_len;        /* message 的总长度 */
    uint16_t    frag_len;       /* 当前分片的长度, <480 */
    uint16_t    frag_seq_id;    /* 分片的编号，从1开始递增 */
    uint8_t     frag_data[491]; /* 分片数据+2字节校验和 */
} fragment_t;

// 打印数据内容
void print_data(const char *label, const uint8_t *data, int len);

// 生成随机测试数据
void generate_test_data(uint8_t *data, int len);

// 比较两个数据块是否相同
int compare_data(const uint8_t *data1, const uint8_t *data2, int len);

#endif /* __COMMON_H__ */