#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// 密码结构体
typedef struct {
    uint16_t idx;           // 密码id
    uint8_t device_id;      // 用户id
    uint8_t passwd[9];      // 8位有效数字密码
    uint8_t time_type;      // 时效类型:1:永久;2:单次;3:限时
    uint32_t active_time;   // 生效时间戳(秒级)
    uint32_t expired_time;  // 失效时间戳(秒级)
    uint8_t start_time[6];  // 开始时间
    uint8_t end_time[6];    // 结束时间
    uint8_t loops[8];       // 周期(0000000,7位数从星期一开始)
} __attribute__((packed)) uartp_tmp_passwd_t;

// 链表节点结构体
typedef struct uartp_tmp_passwd_node_t {
    uartp_tmp_passwd_t data;
    struct uartp_tmp_passwd_node_t *next;
} uartp_tmp_passwd_node_t;

// 创建新节点
uartp_tmp_passwd_node_t* create_node(uartp_tmp_passwd_t data) {
    uartp_tmp_passwd_node_t* new_node = (uartp_tmp_passwd_node_t*)malloc(sizeof(uartp_tmp_passwd_node_t));
    if (new_node == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// 添加节点到链表末尾
void append_node(uartp_tmp_passwd_node_t** head, uartp_tmp_passwd_t data) {
    uartp_tmp_passwd_node_t* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    uartp_tmp_passwd_node_t* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

// 删除链表中的节点
void delete_node(uartp_tmp_passwd_node_t** head, uint16_t idx) {
    if (*head == NULL) {
        return;
    }
    uartp_tmp_passwd_node_t* temp = *head;
    uartp_tmp_passwd_node_t* prev = NULL;

    // 如果头节点是需要删除的节点
    if (temp != NULL && temp->data.idx == idx) {
        *head = temp->next;
        free(temp);
        return;
    }

    // 搜索要删除的节点
    while (temp != NULL && temp->data.idx != idx) {
        prev = temp;
        temp = temp->next;
    }

    // 如果没有找到节点
    if (temp == NULL) return;

    // 从链表中移除节点
    prev->next = temp->next;
    free(temp);
}

// 查找链表中的节点
uartp_tmp_passwd_node_t* find_node(uartp_tmp_passwd_node_t* head, uint16_t idx) {
    uartp_tmp_passwd_node_t* current = head;
    while (current != NULL) {
        if (current->data.idx == idx) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// 更新链表中的节点
void update_node(uartp_tmp_passwd_node_t* head, uartp_tmp_passwd_t data) {
    uartp_tmp_passwd_node_t* node_to_update = find_node(head, data.idx);
    if (node_to_update != NULL) {
        node_to_update->data = data;
    }
}

// 打印链表中的所有节点
void print_list(uartp_tmp_passwd_node_t* head) {
    uartp_tmp_passwd_node_t* current = head;
    while (current != NULL) {
        printf("idx: %u, device_id: %u, passwd: %s, time_type: %u, active_time: %u, expired_time: %u\n",
               current->data.idx, current->data.device_id, current->data.passwd,
               current->data.time_type, current->data.active_time, current->data.expired_time);
        current = current->next;
    }
}

// 释放链表内存
void free_list(uartp_tmp_passwd_node_t* head) {
    uartp_tmp_passwd_node_t* current = head;
    uartp_tmp_passwd_node_t* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

#if 0

int main() {
    uartp_tmp_passwd_node_t* head = NULL;

/*
typedef struct {
    uint16_t idx;           // 密码id
    uint8_t device_id;      // 用户id
    uint8_t passwd[9];      // 8位有效数字密码
    uint8_t time_type;      // 时效类型:1:永久;2:单次;3:限时
    uint32_t active_time;   // 生效时间戳(秒级)
    uint32_t expired_time;  // 失效时间戳(秒级)
    uint8_t start_time[6];  // 开始时间
    uint8_t end_time[6];    // 结束时间
    uint8_t loops[8];       // 周期(0000000,7位数从星期一开始)
} __attribute__((packed)) uartp_tmp_passwd_t;
*/
    // 创建一些测试数据
    uartp_tmp_passwd_t passwd1 = {1, 1, "12345678", 1, 1617181920, 1718192021, {0}, {0}, "0000000"};
    uartp_tmp_passwd_t passwd2 = {2, 2, "23456789", 2, 1617181921, 1718192022, {0}, {0}, "0000000"};
    uartp_tmp_passwd_t passwd3 = {3, 3, "34567890", 3, 1617181922, 1718192023, {0}, {0}, "0000000"};

    // 添加节点
    append_node(&head, passwd1);
    append_node(&head, passwd2);
    append_node(&head, passwd3);

    // 打印链表
    printf("初始链表:\n");
    print_list(head);

    // 更新节点
    uartp_tmp_passwd_t updated_passwd = {2, 2, "87654321", 2, 1617181921, 1718192022, {0}, {0}, "0000000"};
    update_node(head, updated_passwd);
    printf("\n更新后的链表:\n");
    print_list(head);

    // 删除节点
    delete_node(&head, 1);
    printf("\n删除节点后的链表:\n");
    print_list(head);

    // 查找节点
    uartp_tmp_passwd_node_t* found_node = find_node(head, 3);
    if (found_node) {
        printf("\n找到节点 idx=3: idx: %u, device_id: %u, passwd: %s, time_type: %u, active_time: %u, expired_time: %u\n",
               found_node->data.idx, found_node->data.device_id, found_node->data.passwd,
               found_node->data.time_type, found_node->data.active_time, found_node->data.expired_time);
    } else {
        printf("\n未找到节点 idx=3\n");
    }

    // 释放链表内存
    free_list(head);

    return 0;
}

#endif