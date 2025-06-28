#ifndef __FRAGMENT_SEND_H__
#define __FRAGMENT_SEND_H__

#include "common.h"

// 发送回调函数类型
typedef int (*send_callback_t)(uint8_t *data, uint32_t len);

/* 
 * 消息分片发送函数
 * message: 待发送的数据
 * msg_len: 数据长度
 * cmd: 命令字
 * callback: 发送回调函数
 * return: 0成功, -1失败
 */
int fragment_send(uint8_t *message, uint16_t msg_len, uint8_t cmd, send_callback_t callback);

#endif /* __FRAGMENT_SEND_H__ */