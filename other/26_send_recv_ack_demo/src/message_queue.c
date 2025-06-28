#include "message_queue.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void message_queue_init(message_queue_t *q) {
    q->head = q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
    q->count = 0;
}

void message_queue_destroy(message_queue_t *q) {printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_mutex_lock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    
    message_node_t *node = q->head;printf("[%s][%d]\r\n", __func__, __LINE__);
    while (node) {printf("[%s][%d]\r\n", __func__, __LINE__);
        message_node_t *next = node->next;
        free(node->data);
        free(node);
        node = next;
    }printf("[%s][%d]\r\n", __func__, __LINE__);
    
    pthread_mutex_unlock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_mutex_destroy(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_cond_destroy(&q->cond);printf("[%s][%d]\r\n", __func__, __LINE__);
}

void message_queue_enqueue(message_queue_t *q, uint8_t *data, uint32_t len) {printf("[%s][%d]\r\n", __func__, __LINE__);
    message_node_t *node = malloc(sizeof(message_node_t));
    node->data = malloc(len);
    memcpy(node->data, data, len);
    node->len = len;
    node->next = NULL;

    pthread_mutex_lock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    
    if (q->tail) {
        q->tail->next = node;
    } else {
        q->head = node;
    }
    q->tail = node;
    q->count++;
    
    pthread_cond_signal(&q->cond);printf("[%s][%d]\r\n", __func__, __LINE__);
    pthread_mutex_unlock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
}

int message_queue_dequeue(message_queue_t *q, uint8_t **data, uint32_t *len) {
    pthread_mutex_lock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    
    while (q->head == NULL) {printf("[%s][%d]\r\n", __func__, __LINE__);
        pthread_cond_wait(&q->cond, &q->lock);
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    message_node_t *node = q->head;
    *data = malloc(node->len);
    memcpy(*data, node->data, node->len);
    *len = node->len;

    q->head = node->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    q->count--;
    
    free(node->data);
    free(node);
    pthread_mutex_unlock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}

int message_queue_size(message_queue_t *q) {
    pthread_mutex_lock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    int count = q->count;
    pthread_mutex_unlock(&q->lock);printf("[%s][%d]\r\n", __func__, __LINE__);
    return count;
}
