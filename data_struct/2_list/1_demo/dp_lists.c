#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint8_t id;
    uint8_t type;
    uint16_t len;
    uint32_t timestamp;
    uint8_t *value;
} uartp_dp_data_t;

typedef struct uartp_dp_node_t {
    uartp_dp_data_t dp_info;
    struct uartp_dp_node_t *next;
} uartp_dp_node_t;

typedef struct {
    uartp_dp_node_t *head;
    uartp_dp_node_t *tail;
} uartp_dp_list_t;

static void _print_dp_data(uartp_dp_data_t *data);

static void _init_list(uartp_dp_list_t *list) {
    list->head = NULL;
    list->tail = NULL;
}

static int _list_append(uartp_dp_list_t *list, uartp_dp_data_t *data)
{
    uartp_dp_node_t *new_node = (uartp_dp_node_t*)malloc(sizeof(uartp_dp_node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    }
    new_node->dp_info.id = data->id;
    new_node->dp_info.type = data->type;
    new_node->dp_info.len = data->len;
    new_node->dp_info.timestamp = data->timestamp;
    new_node->dp_info.value = (uint8_t*)malloc(data->len * sizeof(uint8_t));
    if (new_node->dp_info.value == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(new_node);
        return -1;
    }
    memcpy(new_node->dp_info.value, data->value, data->len);
    new_node->next = NULL;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    return 0;
}

static int _list_remove(uartp_dp_list_t *list)
{
    if (list->head == NULL) {
        printf("List is empty.\n");
        return -1;
    }

    uartp_dp_node_t *temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    }
    free(temp->dp_info.value);
    free(temp);

    return 0;
}

static int _list_remove_with_id(uartp_dp_list_t *list, uint8_t id) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return -1;
    }

    uartp_dp_node_t *current = list->head;
    uartp_dp_node_t *prev = NULL;

    while (current != NULL) {
        if (current->dp_info.id == id) {
            if (prev == NULL) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) {
                    list->tail = prev;
                }
            }
            free(current->dp_info.value);
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }

    printf("Data packet with ID %02x not found.\n", id);
    return -1; // 没有找到指定ID的数据包
}

static int _list_query(uartp_dp_list_t *list, int *dp_id_lists)
{
    if (!list) return -1;
    uartp_dp_node_t *current = list->head;
    int count = 0;
    while (current != NULL) {
        dp_id_lists[count++] = current->dp_info.id;
        current = current->next;
    }

    return count;
}

static int _list_get_dp_data(uartp_dp_list_t *list, uint8_t id, uartp_dp_data_t *out)
{
    if (!list) return -1;

    uartp_dp_node_t *current = list->head;
    while (current != NULL) {
        if (current->dp_info.id == id) {
            memcpy(out, &current->dp_info, sizeof(current->dp_info));
            return 0;
        }
        current = current->next;
    }

    return -1;
}

static int _list_query_all(uartp_dp_list_t *list)
{
    if (!list) return -1;

    uartp_dp_node_t *current = list->head;
    while (current != NULL) {
        _print_dp_data(&current->dp_info);
        current = current->next;
    }

    return 0;
}

static void _print_dp_data(uartp_dp_data_t *data)
{
    if (!data) return;

    printf("\r\n_print_dp_data:\r\n");
    printf("id: %02X\r\n", data->id);
    printf("type: %02X\r\n", data->type);
    printf("len: %04X\r\n", data->len);
    printf("timestamp: %04X, %d\r\n", data->timestamp, data->timestamp);
    printf("value:");
    for (int i = 0;i < data->len; i++) {
        printf("%02X", data->value[i]);
        if (i != data->len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");
}

static void _destroy_dp_list(uartp_dp_list_t *list)
{
    if (list == NULL)
        return;

    uartp_dp_node_t *current = list->head;
    uartp_dp_node_t *temp;

    while (current != NULL) {
        temp = current->next;

        if (current->dp_info.value != NULL) {
            free(current->dp_info.value);
            current->dp_info.value = NULL;
        }

        // 释放当前节点
        free(current);

        // 移动到下一个节点
        current = temp;
    }

    list->head = NULL;
    list->tail = NULL;
}

uint8_t* serialize_list(const uartp_dp_list_t *list, uint32_t *total_size) {
    *total_size = 0;
    uartp_dp_node_t *current = list->head;
    while (current != NULL) {
        *total_size += 1 + 1 + 2 + 4 + current->dp_info.len; // id, type, len, timestamp, value
        current = current->next;
    }

    if (*total_size == 0) return NULL;

    uint8_t *buffer = malloc(*total_size);
    if (!buffer) {
        return NULL;
    }

    uint32_t offset = 0;
    current = list->head;
    while (current != NULL) {
        buffer[offset++] = current->dp_info.id;
        buffer[offset++] = current->dp_info.type;
        buffer[offset++] = current->dp_info.len & 0xFF;
        buffer[offset++] = (current->dp_info.len >> 8) & 0xFF;
        buffer[offset++] = current->dp_info.timestamp & 0xFF;
        buffer[offset++] = (current->dp_info.timestamp >> 8) & 0xFF;
        buffer[offset++] = (current->dp_info.timestamp >> 16) & 0xFF;
        buffer[offset++] = (current->dp_info.timestamp >> 24) & 0xFF;
        memcpy(buffer + offset, current->dp_info.value, current->dp_info.len);
        offset += current->dp_info.len;

        current = current->next;
    }

    return buffer;
}

int deserialize_list(uartp_dp_list_t *list, const uint8_t *buffer, uint32_t total_size) {
    _init_list(list);
    uint32_t offset = 0;

    while (offset < total_size) {
        uartp_dp_data_t data;
        data.id = buffer[offset++];
        data.type = buffer[offset++];
        data.len = buffer[offset++] | (buffer[offset++] << 8);
        data.timestamp = buffer[offset++] | (buffer[offset++] << 8) | (buffer[offset++] << 16) | (buffer[offset++] << 24);
        
        data.value = malloc(data.len);
        if (!data.value) {
            printf("malloc err\r\n");
            return -1;
        }
        memcpy(data.value, buffer + offset, data.len);
        offset += data.len;

        if (_list_append(list, &data) != 0) {
            printf("append err\r\n");
            return -1;
        }

        free(data.value);
        data.value = NULL;
    }

    return 0; // Success
}

static int _merge_dp_list(uartp_dp_list_t *plist, uartp_dp_list_t *qlist)
{
    if (!plist || !qlist)
        return -1;

    int ret = 0;

    if (plist->tail == NULL) {
        plist->head = qlist->head;
        plist->tail = qlist->tail;
    } else {
        plist->tail->next = qlist->head;
        plist->tail = qlist->tail;
    }

    qlist->head = NULL;
    qlist->tail = NULL;

    return ret;
}

static void _test_01()
{
    uartp_dp_list_t list;
    _init_list(&list);

    uartp_dp_data_t data1 = {0x01, 0x02, 0x0002, 0x65d59a97, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data2 = {0x02, 0x04, 0x0003, 0x65d59a98, (uint8_t[]){0x03, 0x04, 0x05}};
    uartp_dp_data_t data3 = {0x03, 0x01, 0x0005, 0x65d59a99, (uint8_t[]){0x01, 0x02, 0x03, 0x04, 0x05}};
    uartp_dp_data_t data4 = {0x04, 0x02, 0x0004, 0x65d59a9a, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    _list_append(&list, &data1);
    _list_append(&list, &data2);
    _list_append(&list, &data3);
    _list_append(&list, &data4);

    printf("query all:========\r\n");
    _list_query_all(&list);
    printf("query end========\r\n\r\n");

    int dp_id_lists[10];
    int count = _list_query(&list, dp_id_lists);
    printf("Number of DP IDs: %d\n", count);
    printf("DP IDs: ");
    for (int i = 0; i < count; i++) {
        printf("%02x ", dp_id_lists[i]);
    }
    printf("\n");

    // _list_remove(&list);
    // _list_remove(&list);
    // _list_remove_with_id(&list, 1);
    int remove_node = 3;
    int ret = _list_remove_with_id(&list, remove_node);
    if (ret != -1) {
        printf("_list_remove %d succeeful\r\n", remove_node);
    }

    count = _list_query(&list, dp_id_lists);
    printf("Number of DP IDs: %d\n", count);
    if (count == 0) {
        printf("list is empty\r\n");
        return ;
    }

    if (count > 0) {
        printf("DP IDs: ");
        for (int i = 0; i < count; i++) {
            printf("%02x ", dp_id_lists[i]);
        }
        printf("\n");
    }

    uartp_dp_data_t out_data = {0};

    int find_id = 4;
    ret = _list_get_dp_data(&list, find_id, &out_data);
    if (ret == 0) {
        _print_dp_data(&out_data);
    }
}

static void _test_02()
{
    uartp_dp_list_t list;
    _init_list(&list);

    uartp_dp_data_t data1 = {0x01, 0x02, 0x0002, 0x65d59a97, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data2 = {0x02, 0x04, 0x0003, 0x65d59a98, (uint8_t[]){0x03, 0x04, 0x05}};
    uartp_dp_data_t data3 = {0x03, 0x01, 0x0005, 0x65d59a99, (uint8_t[]){0x01, 0x02, 0x03, 0x04, 0x05}};
    uartp_dp_data_t data4 = {0x04, 0x02, 0x0004, 0x65d59a9a, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    _list_append(&list, &data1);
    _list_append(&list, &data2);
    _list_append(&list, &data3);
    _list_append(&list, &data4);

    uint32_t total_size;
    uint8_t *serialized_list = serialize_list(&list, &total_size);
    if (serialized_list) {
        
    }

    printf("total size:%d\r\n", total_size);

    uartp_dp_list_t deserialized_list;
    if (deserialize_list(&deserialized_list, serialized_list, total_size) == 0) {
        _list_query_all(&deserialized_list);
    }

    if (serialized_list) {
        free(serialized_list);
        serialized_list = NULL;
    }
}

static int _test_03()
{
    int ret = 0;
    uartp_dp_list_t plist, qlist;
    _init_list(&plist);
    _init_list(&qlist);

    uartp_dp_data_t data1 = {0x01, 0x02, 0x0002, 0x65d59a97, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data2 = {0x02, 0x04, 0x0003, 0x65d59a98, (uint8_t[]){0x03, 0x04, 0x05}};
    uartp_dp_data_t data3 = {0x03, 0x01, 0x0005, 0x65d59a99, (uint8_t[]){0x01, 0x02, 0x03, 0x04, 0x05}};
    uartp_dp_data_t data4 = {0x04, 0x02, 0x0004, 0x65d59a9a, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    uartp_dp_data_t data5 = {0x05, 0x02, 0x0002, 0x65d59a9b, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data6 = {0x06, 0x02, 0x0003, 0x65d59a9c, (uint8_t[]){0x01, 0x02, 0x03}};
    uartp_dp_data_t data7 = {0x07, 0x02, 0x0004, 0x65d59a9d, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    _list_append(&plist, &data1);
    _list_append(&plist, &data2);
    _list_append(&plist, &data3);
    _list_append(&plist, &data4);

    _list_append(&qlist, &data5);
    _list_append(&qlist, &data6);
    _list_append(&qlist, &data7);

    ret = _merge_dp_list(&plist, &qlist);
    if (ret != 0) {
        printf("_merge_dp_list err\r\n");
    }

    ret = _list_query_all(&plist);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }

    _destroy_dp_list(&plist);
    _destroy_dp_list(&qlist);

    return ret;
}

int main() {
    // _test_01();
    // _test_02();
    _test_03();
    return 0;
}
