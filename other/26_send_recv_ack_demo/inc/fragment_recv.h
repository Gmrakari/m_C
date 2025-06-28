#ifndef __FRAGMENT_RECV_H__
#define __FRAGMENT_RECV_H__

#include "common.h"
#include <stdint.h>
#include <string.h>

// 组包消息结构
typedef struct {
    uint8_t     in_used;        // 是否使用中
    uint16_t    total_len;      // 原数据长度
    uint16_t    received_len;   // 已接收数据长度
    uint8_t     *data;          // 数据缓冲区
    uint16_t    last_frag_id;   // 最后接收的分片ID
    uint16_t    frag_count;     // 已接收分片数量
} package_msg_t;

/* 
 * 分片消息组包处理
 * data: 接收到的分片数据
 * len: 数据长度
 * last_frag: 输出参数，是否最后一个分片
 * total_len: 输出参数，消息总长度
 * out: 输出参数，组包完成的数据
 * olen: 输出参数，组包数据长度
 * package_info: 组包状态信息
 * return: 0组包完成, -1错误, -2接收中
 */
int fragment_receive(uint8_t *data, uint32_t len, uint8_t *last_frag, 
                    int *total_len, char **out, int *olen, package_msg_t *package_info);

// 初始化组包状态
void init_package_info(package_msg_t *package_info);

#endif /* __FRAGMENT_RECV_H__ */