#ifndef __MESSAGE_QUEUE_H__
#define __MESSAGE_QUEUE_H__

#include <pthread.h>
#include <stdint.h>

typedef struct message_node {
    uint8_t             *data;
    uint32_t            len;
    struct message_node *next;
} message_node_t;

typedef struct {
    message_node_t  *head;
    message_node_t  *tail;
    pthread_mutex_t lock;
    pthread_cond_t  cond;
    int             count;
} message_queue_t;

// 初始化消息队列
void message_queue_init(message_queue_t *q);

// 销毁消息队列
void message_queue_destroy(message_queue_t *q);

// 向队列添加消息
void message_queue_enqueue(message_queue_t *q, uint8_t *data, uint32_t len);

// 从队列获取消息
int message_queue_dequeue(message_queue_t *q, uint8_t **data, uint32_t *len);

// 获取队列大小
int message_queue_size(message_queue_t *q);

#endif /* __MESSAGE_QUEUE_H__ */