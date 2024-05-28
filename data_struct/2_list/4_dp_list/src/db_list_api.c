#include "db_list_api.h"
#include "tmp_passwd_list_db.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    uint8_t *ptr;
    uint16_t offset;
    uint16_t size;
} dp_list_api_private_t;

static dp_list_api_private_t private;

int rlink_load_tmp_passwd_info(void)
{
    int ret = 0;

    uint16_t header = 0;
    uint16_t offset = 0;
    uint16_t block_size = 0x1000;

    private.ptr = NULL;
    if (get_fd_mem_ptr(&private.ptr) != 0) {
        printf("[%s][%d]get_fd_mem_ptr err!\r\n", __func__, __LINE__);
        return -1;
    }

    memcpy((uint8_t *)&header, private.ptr, sizeof(uint16_t));

    if (header == THING_TMP_PASSWD_MAGIC_HEAD_NUM) {
        printf("[%s][%d]load tmp passwd ok!\r\n", __func__, __LINE__);
        return ret;
    }

    header = THING_TMP_PASSWD_MAGIC_HEAD_NUM;
    memset(private.ptr, 0x00, DEFAULT_TMP_PASSWD_BLOCK_SIZE);
    memcpy(private.ptr, &header, sizeof(uint16_t));

    private.offset = 0;
    private.size = block_size;

    return ret;
}

int rlink_uartp_init_tmp_passwd_list(uartp_tmp_passwd_list_t *list)
{
    if (!list) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    list->head = NULL;
    list->tail = NULL;

    return ret;
}

int rlink_uartp_destroy_tmp_passwd_list(uartp_tmp_passwd_list_t *list)
{
    if (!list) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uartp_tmp_passwd_node_t *cur = list->head;
    uartp_tmp_passwd_node_t *tmp = NULL;
    while (cur != NULL) {
        tmp = cur->next;

        free(cur);
        cur = tmp;
    }

    list->head = NULL;
    list->tail = NULL;

    return ret;
}

int rlink_uartp_tmp_passwd_list_get_num(uartp_tmp_passwd_list_t *list, uint8_t *num)
{
    if (!list || !num) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    (*num) = 0;

    uartp_tmp_passwd_node_t *cur = list->head;
    while (cur != NULL) {
        (*num)++;
        cur = cur->next;
    }

    return ret;
}

// ret:
// -1 错误
// 0 list中没有该idx
// 1 list中找到该idx
int rlink_uartp_tmp_passwd_list_query_id(uartp_tmp_passwd_list_t *list, uint16_t idx)
{
    if (!list) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uartp_tmp_passwd_node_t *cur = list->head;
    while (cur != NULL) {
        if (cur->data.idx == idx) {
            ret = 1;
            return ret;
        }
        cur = cur->next;
    }

    return ret;
}

int rlink_uartp_tmp_passwd_list_query_id_info(uartp_tmp_passwd_list_t *list, uint16_t idx, uartp_tmp_passwd_t **info)
{
    if (!list) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uartp_tmp_passwd_node_t *cur = list->head;
    while (cur != NULL) {
        if (cur->data.idx == idx) {
            uartp_tmp_passwd_t *out = malloc(sizeof(uartp_tmp_passwd_t));
            if (!out) {
                printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
                return -1;
            }
            memset(out, 0x00, sizeof(uartp_tmp_passwd_t));
            memcpy(out, &(cur->data), sizeof(uartp_tmp_passwd_t));
            *info = out;
            return ret;
        }
        cur = cur->next;
    }

    return ret; 
}

int rlink_uartp_tmp_passwd_list_append(uartp_tmp_passwd_list_t *list, uartp_tmp_passwd_t *data)
{
    if (!data) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = rlink_uartp_tmp_passwd_list_query_id(list, data->idx);
    if (ret == -1) {
        printf("[%s][%d]rlink_uartp_tmp_passwd_list_query_id err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    if (ret == 1) {
        printf("[%s][%d]id:%d has exist!\r\n", __func__, __LINE__, data->idx);
        ret = 0;
        return ret;
    }

    uartp_tmp_passwd_node_t *new_node = (uartp_tmp_passwd_node_t*)malloc(sizeof(uartp_tmp_passwd_node_t));
    if (!new_node) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    new_node->data.idx = data->idx;
    new_node->data.device_id = data->device_id;
    new_node->data.passwd_len = data->passwd_len;
    strncpy(new_node->data.passwd, data->passwd, sizeof(new_node->data.passwd));
    new_node->data.time_type = data->time_type;
    new_node->data.active_time = data->active_time;
    new_node->data.expired_time = data->expired_time;
    strncpy(new_node->data.start_time, data->start_time, sizeof(new_node->data.start_time));
    strncpy(new_node->data.end_time, data->end_time, sizeof(new_node->data.end_time));
    strncpy(new_node->data.loops, data->loops, sizeof(new_node->data.loops));
    new_node->next = NULL;

    if (list->tail == NULL) {
        list->head = new_node;
        list->tail = new_node;
        return ret;
    }

    list->tail->next = new_node;
    list->tail = new_node;

    return ret;
}

int rlink_uartp_tmp_passwd_list_del(uartp_tmp_passwd_list_t *list, uint16_t index)
{
    if (!list) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = rlink_uartp_tmp_passwd_list_query_id(list, index);
    if (ret != 1) {
        printf("[%s][%d]not found idx: %d!\r\n", __func__, __LINE__, index);
        ret = 0;
        return ret;
    }

    uartp_tmp_passwd_node_t *cur = list->head;
    uartp_tmp_passwd_node_t *prev = NULL;

    while (cur != NULL) {
        if (cur->data.idx == index) {
            if (prev == NULL) {
                list->head = cur->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            } else {
                prev->next = cur->next;
                if (cur->next == NULL) 
                    list->tail = prev;
            }
            free(cur);
            ret = 0;
            return ret;
        }
        prev = cur;
        cur = cur->next;
    }

    return ret;
}

int rlink_uartp_serialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, uint8_t **out, uint16_t *out_len)
{
    if (!list || !out_len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;
    *out_len = 0;

    uint8_t list_node_num = 0;
    ret = rlink_uartp_tmp_passwd_list_get_num(list, &list_node_num);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_tmp_passwd_list_get_num err!\r\n", __func__, __LINE__);
        return -1;
    }

    uint16_t buflen = list_node_num * sizeof(uartp_tmp_passwd_t);
    uint8_t *buffer = malloc(sizeof(uint8_t) * buflen);
    if (!buffer) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    memset(buffer, 0x00, buflen);

    uint8_t *ptr = buffer;
    uartp_tmp_passwd_node_t *cur = list->head;
    uint16_t offset = 0;
    while (cur != NULL) {
        *(uint16_t *)ptr = cur->data.idx;
        ptr += sizeof(uint16_t);

        *ptr = cur->data.device_id;
        ptr += sizeof(uint8_t);

        *ptr = cur->data.passwd_len;
        ptr += sizeof(uint8_t);

        for (int i = 0; i < sizeof(cur->data.passwd); i++) {
            *ptr = cur->data.passwd[i];
            ptr += sizeof(uint8_t);
        }

        *ptr = cur->data.time_type;
        ptr += sizeof(uint8_t);

        *(uint32_t *)ptr = cur->data.active_time;
        ptr += sizeof(uint32_t);

        *(uint32_t *)ptr = cur->data.expired_time;
        ptr += sizeof(uint32_t);

        for (int i = 0; i < sizeof(cur->data.start_time); i++) {
            *ptr = cur->data.start_time[i];
            ptr += sizeof(uint8_t);
        }

        for (int i = 0; i < sizeof(cur->data.end_time); i++) {
            *ptr = cur->data.end_time[i];
            ptr += sizeof(uint8_t);
        }

        for (int i = 0; i < sizeof(cur->data.loops); i++) {
            *ptr = cur->data.loops[i];
            ptr += sizeof(uint8_t);
        }

        cur = cur->next;
    }

    *out = buffer;
    *out_len = ptr - buffer;

    return ret;
}

int rlink_uartp_deserialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, const uint8_t *buffer, uint16_t len)
{
    if (!list || !buffer || !len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = rlink_uartp_init_tmp_passwd_list(list);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_init_tmp_passwd_list err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    uint16_t offset = 0;

    uartp_tmp_passwd_t data;

    const uint8_t *ptr = buffer;

    while (offset < len) {
        memset(&data, 0x00, sizeof(uartp_tmp_passwd_t));
        data.idx = *(uint16_t *)(ptr + offset);
        offset += sizeof(uint16_t);

        data.device_id = *(ptr + offset);
        offset += sizeof(uint8_t);

        data.passwd_len = *(ptr + offset);
        offset += sizeof(uint8_t);

        memcpy(data.passwd, ptr + offset, sizeof(data.passwd));
        offset += sizeof(data.passwd);

        data.time_type = *(ptr + offset);
        offset += sizeof(uint8_t);

        data.active_time = *(uint32_t *)(ptr + offset);
        offset += sizeof(uint32_t);

        data.expired_time = *(uint32_t *)(ptr + offset);
        offset += sizeof(uint32_t);

        memcpy(data.start_time, ptr + offset, sizeof(data.start_time));
        offset += sizeof(data.start_time);

        memcpy(data.end_time, ptr + offset, sizeof(data.end_time));
        offset += sizeof(data.end_time);

        memcpy(data.loops, ptr + offset, sizeof(data.loops));
        offset += sizeof(data.loops);

        if (rlink_uartp_tmp_passwd_list_append(list, &data) != 0) {
            printf("[%s][%d]\r\n", __func__, __LINE__);
            ret = -1;
            return ret;
        }
    }

    return ret;
}

int rlink_write_uartp_tmp_passwd_list_to_flash(uartp_tmp_passwd_list_t *list)
{
    if (!list) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uint8_t *out = NULL;
    uint16_t olen = 0;

    ret = rlink_uartp_serialize_tmp_passwd_list(list, &out, &olen);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_serialize_tmp_passwd_list err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    uint8_t list_node_num = 0;
    ret = rlink_uartp_tmp_passwd_list_get_num(list, &list_node_num);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_tmp_passwd_list_get_num err!\r\n", __func__, __LINE__);

        if (out) {
            free(out);
            out = NULL;
        }
        ret = -1;
        return ret;
    }

    ret = rlink_uartp_destroy_tmp_passwd_list(list);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_destroy_tmp_passwd_list err!\r\n", __func__, __LINE__);

        if (out) {
            free(out);
            out = NULL;
        }
        ret = -1;
        return ret;
    }

    uint16_t magic_num = THING_TMP_PASSWD_MAGIC_HEAD_NUM;
    uint16_t offset = 0;
    uint8_t *ptr = private.ptr;

    memcpy(ptr + offset, &magic_num, sizeof(uint16_t));
    offset += sizeof(uint16_t);

    memcpy(ptr + offset, &list_node_num, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    memcpy(ptr + offset, out, olen);
    offset += olen;

    if (out) {
        free(out);
        out = NULL;
    }

    return ret;
}

int rlink_read_from_flash_get_tmp_passwd_num(int *num)
{
    if (!num) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uint16_t header_magic = 0;
    uint16_t offset = 0;
    uint8_t list_node_num = 0;

    uint8_t *ptr = private.ptr;

    header_magic = *(uint16_t *)(ptr + offset);
    offset += sizeof(uint16_t);

    if (header_magic != THING_TMP_PASSWD_MAGIC_HEAD_NUM) {
        printf("[%s][%d]get header failed!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    list_node_num = *(ptr + offset);
    offset += sizeof(uint8_t);

    *num = list_node_num;

    return ret;
}

int rlink_read_from_flash_get_list_data(uint8_t **out, uint16_t *out_len)
{
    int ret = 0;

    uint16_t header_magic = 0;
    uint16_t offset = 0;

    uint8_t *ptr = private.ptr;

    header_magic = *(uint16_t *)(ptr + offset);
    offset += sizeof(uint16_t);

    if (header_magic != THING_TMP_PASSWD_MAGIC_HEAD_NUM) {
        printf("[%s][%d]get header failed!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    uint8_t list_node_num = 0;
    uint16_t buffer_len = 0;
    
    list_node_num = *(ptr + offset);
    offset += sizeof(uint8_t);

    if (list_node_num == 0)
        return ret;

    buffer_len = list_node_num * sizeof(uartp_tmp_passwd_t);
    uint8_t *buffer = malloc(sizeof(uint8_t) * buffer_len);
    if (!buffer) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }
    memset(buffer, 0x00, buffer_len);

    memcpy(buffer, ptr + offset, buffer_len);
    offset += buffer_len;

    *out = buffer;
    *out_len = buffer_len;

    return ret;
}

static void print_tmp_passwd_info(uartp_tmp_passwd_t *passwd_info)
{
    if (!passwd_info) {
        printf("[%s][%d]invalid pararm!\r\n", __func__, __LINE__);
        return ;
    }

    printf("=====Password Info======\r\n");
    printf("idx: %u\n", passwd_info->idx);
    printf("device_id: %u\n", passwd_info->device_id);
    printf("passwd_len: %u\n", passwd_info->passwd_len);
    printf("passwd: %.*s\n", passwd_info->passwd_len, passwd_info->passwd);
    printf("time_type: %u\n", passwd_info->time_type);
    printf("active_time: %u\n", passwd_info->active_time);
    printf("expired_time: %u\n", passwd_info->expired_time);
    printf("active_time: %s\n",passwd_info->start_time);
    printf("end_time: %s\n", passwd_info->end_time);
    printf("loops: %s\n",passwd_info->loops);
    printf("=========end=========\r\n");

    return ;
}

int debug_print_list_info(uartp_tmp_passwd_list_t *list)
{
    if (!list) {
        printf("[%s][%d]debug_print_list_info err!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    uartp_tmp_passwd_node_t *cur = list->head;

    while (cur != NULL) {
        print_tmp_passwd_info(&(cur->data));
        cur = cur->next;
    }

    return ret;
}
