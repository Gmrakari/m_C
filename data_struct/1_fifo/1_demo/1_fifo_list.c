#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// 数据结构
typedef struct Node {
    uint8_t id;
    uint8_t type;
    uint16_t len;
    uint8_t *value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} FIFO;

// 初始化FIFO队列
void init_fifo(FIFO *fifo) {
    fifo->head = NULL;
    fifo->tail = NULL;
}

// 新增数据到FIFO队列
void push_fifo(FIFO *fifo, uint8_t id, uint8_t type, uint16_t len, uint8_t *value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    new_node->id = id;
    new_node->type = type;
    new_node->len = len;
    new_node->value = (uint8_t*)malloc(len * sizeof(uint8_t));
    if (new_node->value == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    memcpy(new_node->value, value, new_node->len);
    new_node->next = NULL;

    if (fifo->tail == NULL) {
        fifo->head = new_node;
        fifo->tail = new_node;
    } else {
        fifo->tail->next = new_node;
        fifo->tail = new_node;
    }
}

// 从FIFO队列中弹出数据
void pop_fifo(FIFO *fifo) {
    if (fifo->head == NULL) {
        printf("FIFO is empty.\n");
        return;
    }
    Node *temp = fifo->head;
    fifo->head = fifo->head->next;
    if (fifo->head == NULL) {
        fifo->tail = NULL;
    }
    free(temp->value);
    free(temp);
}

// 查询FIFO队列的头部数据
Node* peek_fifo(FIFO *fifo) {
    return fifo->head;
}

// 打印FIFO队列
void print_fifo(FIFO *fifo) {
    Node *current = fifo->head;
    while (current != NULL) {
        printf("id=%02x, type=%02x, len=%d, value=", current->id, current->type, current->len);
        for (int i = 0; i < current->len; i++) {
            printf("%02x ", current->value[i]);
        }
        printf("\n");
        current = current->next;
    }
}

// 清空FIFO队列
void clear_fifo(FIFO *fifo) {
    while (fifo->head != NULL) {
        pop_fifo(fifo);
    }
}

int main() {
    // 初始化FIFO队列
    FIFO fifo;
    init_fifo(&fifo);

    // 添加数据到FIFO队列
    uint8_t data1[] = {0x01, 0x02, 0x00, 0x02, 0x01, 0x02};
    push_fifo(&fifo, 0x01, 0x02, 0x0002, data1);

    uint8_t data2[] = {0x03, 0x04, 0x00, 0x03, 0x03, 0x04, 0x05};
    push_fifo(&fifo, 0x03, 0x04, 0x0003, data2);

    // 查询并打印FIFO队列头部数据
    Node *head = peek_fifo(&fifo);
    if (head != NULL) {
        printf("Head of FIFO Queue: id=%02x, type=%02x, len=%d, value=", head->id, head->type, head->len);
        for (int i = 0; i < head->len; i++) {
            printf("%02x ", head->value[i]);
        }
        printf("\n");
    } else {
        printf("FIFO is empty.\n");
    }

    // 打印FIFO队列
    printf("FIFO Queue Contents:\n");
    print_fifo(&fifo);

    // 弹出头部数据并打印FIFO队列
    pop_fifo(&fifo);
    printf("FIFO Queue after popping:\n");
    print_fifo(&fifo);

    // 清空FIFO队列
    clear_fifo(&fifo);

    return 0;
}
