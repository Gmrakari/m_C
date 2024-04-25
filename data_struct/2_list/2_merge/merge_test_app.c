#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

        free(current);

        current = temp;
    }

    list->head = NULL;
    list->tail = NULL;
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

static int _test_03()
{
    int ret = 0;
    uartp_dp_list_t plist, qlist, pp_list, qq_list;
    _init_list(&plist);
    _init_list(&qlist);
    _init_list(&pp_list);
    _init_list(&qq_list);

    uartp_dp_data_t data1 = {0x01, 0x02, 0x0002, 0x65d59a97, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data2 = {0x02, 0x04, 0x0003, 0x65d59a98, (uint8_t[]){0x03, 0x04, 0x05}};
    uartp_dp_data_t data3 = {0x03, 0x01, 0x0005, 0x65d59a99, (uint8_t[]){0x01, 0x02, 0x03, 0x04, 0x05}};
    uartp_dp_data_t data4 = {0x04, 0x02, 0x0004, 0x65d59a9a, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    uartp_dp_data_t data5 = {0x05, 0x02, 0x0002, 0x65d59a9b, (uint8_t[]){0x01, 0x02}};
    uartp_dp_data_t data6 = {0x06, 0x02, 0x0003, 0x65d59a9c, (uint8_t[]){0x01, 0x02, 0x03}};
    uartp_dp_data_t data7 = {0x07, 0x02, 0x0004, 0x65d59a9d, (uint8_t[]){0x01, 0x02, 0x03, 0x04}};

    uartp_dp_data_t data8 = {0x08, 0x02, 0x0001, 0x65d59a9e, (uint8_t[]){0x01}};
    uartp_dp_data_t data9 = {0x09, 0x02, 0x0002, 0x65d59a9f, (uint8_t[]){0x01, 0x02}};

    _list_append(&plist, &data1);
    _list_append(&plist, &data2);
    _list_append(&plist, &data3);
    _list_append(&plist, &data4);

    _list_append(&qlist, &data5);
    _list_append(&qlist, &data6);
    _list_append(&qlist, &data7);

    _list_append(&pp_list, &data8);
    _list_append(&qq_list, &data9);

    // test1
    // ret = _merge_dp_list(&plist, &qlist);
    // if (ret != 0) {
    //     printf("_merge_dp_list err\r\n");
    // }

    // test2
    // ret = _merge_dp_list(&pp_list, &qlist);
    // if (ret != 0) {
    //     printf("_merge_dp_list err\r\n");
    // }

    // test3
    ret = _merge_dp_list(&pp_list, &qq_list);
    if (ret != 0) {
        printf("_merge_dp_list err\r\n");
    }

    printf("query pp_list start==============\r\n");
    ret = _list_query_all(&pp_list);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }
    printf("query pp_list end==============\r\n\r\n");

    // printf("query qlist start**************\r\n");
    // ret = _list_query_all(&qlist);
    // if (ret != 0) {
    //     printf("_list_query_all err\r\n");
    // }
    // printf("query qlist end**************\r\n\r\n");


    printf("$$$$$$$$$$$$$$query qq_list start$$$$$$$$$$$$$$\r\n");
    ret = _list_query_all(&qq_list);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }
    printf("$$$$$$$$$$$$$$query qq_list end$$$$$$$$$$$$$$\r\n\r\n");

    // ret = _list_query_all(&plist);
    // if (ret != 0) {
    //     printf("_list_query_all err\r\n");
    // }

    _destroy_dp_list(&plist);
    _destroy_dp_list(&qlist);
    _destroy_dp_list(&pp_list);
    // _destroy_dp_list(&qq_list);

    printf("==============query pp_list start==============\r\n");
    ret = _list_query_all(&pp_list);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }
    printf("==============query pp_list end==============\r\n\r\n");

    printf("**************query qlist start**************\r\n");
    ret = _list_query_all(&qlist);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }
    printf("**************query qlist end**************\r\n\r\n");

    printf("$$$$$$$$$$$$$$query qq_list start$$$$$$$$$$$$$$\r\n");
    ret = _list_query_all(&qq_list);
    if (ret != 0) {
        printf("_list_query_all err\r\n");
    }
    printf("$$$$$$$$$$$$$$query qq_list end$$$$$$$$$$$$$$\r\n");

    return ret;
}

int main() {
    _test_03();
    return 0;
}
