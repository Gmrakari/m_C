#include <stdint.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "tmp_passwd_list_db.h"
#include "db_conf.h"
#include "db_list_api.h"

typedef struct {
    int fd;
    void *ptr;
} private_t;

static private_t priv;

static int _db_list_add_test(int add_count);
static int _db_list_del_test(void);
static int _db_list_query_test(int type);

int get_fd_mem_ptr(uint8_t **mem_ptr)
{
    priv.fd = open("../4k_mem_file", O_RDWR | O_CREAT, 0644);
    if (priv.fd == -1) {
        printf("[%s][%d]open err!\r\n", __func__, __LINE__);
        return -1;
    }

    priv.ptr = mmap(NULL, DEFAULT_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, priv.fd, 0);
    if (priv.ptr == MAP_FAILED) {
        printf("[%s][%d]mmap err!\r\n", __func__, __LINE__);
        close(priv.fd);
        return -1;
    }

    *mem_ptr = priv.ptr;

    return 0;
}

int init_tmp_passwd_db_memory(void)
{
    uint8_t *ptr = NULL;
    if (get_fd_mem_ptr(&ptr) != 0) {
        return -1;
    }

    memset(ptr, 0x00, DEFAULT_MEM_SIZE);
    free_fd_mem();

    return 0;
}

int free_fd_mem()
{
    if (priv.ptr) {
        munmap(priv.ptr, DEFAULT_MEM_SIZE);
    }

    close(priv.fd);

    return 0;
}

static int _init_uartp_tmp_passwd_param(uartp_tmp_passwd_t *passwd, int idx)
{
    if (!passwd) {
        printf("[%s][%d]invalid pararm!\r\n", __func__, __LINE__);
        return -1;
    }

    memset(passwd, 0x00, sizeof(uartp_tmp_passwd_t));
    passwd->passwd_len = sizeof(passwd->passwd) - 1;
    strncpy(passwd->loops, "0000000", sizeof(passwd->loops));
    passwd->time_type = 1;
    passwd->device_id = 1;
    passwd->idx = 800 + idx;
    passwd->active_time = 1617181920 + idx;
    passwd->expired_time = 1718192021 + idx;

    int case_num = idx % 3;

    switch (case_num) {
        case 1:
        {
            strncpy(passwd->passwd, "12345678", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "08:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "09:00", sizeof(passwd->end_time));
            break;
        }
        case 2:
        {
            strncpy(passwd->passwd, "45612378", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "10:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "11:00", sizeof(passwd->end_time));
            break;
        }
        case 3:
        {
            strncpy(passwd->passwd, "78945612", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "12:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "13:00", sizeof(passwd->end_time));
            break;
        }
        default:
        {
            strncpy(passwd->passwd, "12312312", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "14:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "15:00", sizeof(passwd->end_time));
            break;
        }
        break;
    }

    return 0;
}

static void _print_uartp_tmp_passwd(uartp_tmp_passwd_t *passwd_info)
{
    if (!passwd_info) {
        printf("[%s][%d]invalid pararm!\r\n", __func__, __LINE__);
        return ;
    }

    printf("Password Info:\n");
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

    printf("\r\n");

    return ;
}

// 1. 根据增加的add_count创建uartp_tmp_passwd_t array
// 2. 将uartp_tmp_passwd_t信息追加到list中
// 3. list to buffer; 获取个数; 写入到flash中
static int _db_list_add_test(int add_count)
{
    if (add_count == 0)
        return 0;

    int ret = 0;

    uartp_tmp_passwd_t *tmp_passwd_data_arr = malloc(sizeof(uartp_tmp_passwd_t) * add_count);
    if (!tmp_passwd_data_arr) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    for (int i = 0; i < add_count; i++) {
        ret = _init_uartp_tmp_passwd_param(&tmp_passwd_data_arr[i], i + 1);
        if (ret != 0) {
            printf("[%s][%d]_init_uartp_tmp_passwd_param err!\r\n", __func__, __LINE__);
            free(tmp_passwd_data_arr);
            tmp_passwd_data_arr = NULL;
            ret = -1;
            return ret;
        }
    }

    uartp_tmp_passwd_list_t list;

    ret = rlink_uartp_init_tmp_passwd_list(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_init_tmp_passwd_list err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    for (int i = 0; i < add_count; i++) {
        ret = rlink_uartp_tmp_passwd_list_append(&list, &tmp_passwd_data_arr[i]);
        if (ret != 0) {
            printf("[%s][%d]rlink_uartp_tmp_passwd_list_append err!\r\n", __func__, __LINE__);
            free(tmp_passwd_data_arr);
            ret = -1;
            return ret;
        }
    }

    if(tmp_passwd_data_arr) {
        free(tmp_passwd_data_arr);
        tmp_passwd_data_arr = NULL;
    }

    ret = rlink_write_uartp_tmp_passwd_list_to_flash(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink_write_uartp_tmp_passwd_list_to_flash err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    ret = rlink_uartp_destroy_tmp_passwd_list(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_destroy_tmp_passwd_list err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    return ret;
}

// 1. 在flash中读取数据到链表中 buffer to list
// 2. 在链表中查找对应的idx删除，更新链表
// 3. list to buffer 写入到flash中
static int _db_list_del_test(void)
{
    int ret = 0;

    uint8_t *buffer = NULL;
    uint16_t buflen = 0;
    ret = rlink_read_from_flash_get_list_data(&buffer, &buflen);
    if (ret != 0) {
        printf("[%s][%d]rlink read from flash get list data err!\r\n", __func__, __LINE__);
        return ret;
    }

    uartp_tmp_passwd_list_t list;

    ret = rlink_uartp_deserialize_tmp_passwd_list(&list, buffer, buflen);
    if (ret != 0) {
        printf("[%s][%d]rlink uartp deserialize tmp passwd list err!\r\n", __func__, __LINE__);
        if (buffer) {
            free(buffer);
            buffer = NULL;
        }
        return ret;
    }

    if (buffer) {
        free(buffer);
        buffer = NULL;
    }
    
    uint16_t del_idx = 802;
    ret = rlink_uartp_tmp_passwd_list_del(&list, del_idx);
    if (ret != 0) {
        printf("[%s][%d]rlink uartp tmp passwd list del err!\r\n", __func__, __LINE__);
        return ret;
    }

    ret = rlink_write_uartp_tmp_passwd_list_to_flash(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink write uartp tmp passwd list to flash err!\r\n", __func__, __LINE__);
        return ret;
    }

    return 0;
}

// 1. 在flash中读取数据到链表中 buffer to list
// 2. 查找idx
// 3. 存在idx, 返回idx相关信息
static int _db_list_query_test(int type)
{
    int ret = 0;

    uint8_t *buffer = NULL;
    uint16_t buflen = 0;
    ret = rlink_read_from_flash_get_list_data(&buffer, &buflen);
    if (ret != 0) {
        printf("[%s][%d]rlink read from flash get list data err!\r\n", __func__, __LINE__);
        return ret;
    }

    uartp_tmp_passwd_list_t list;

    ret = rlink_uartp_deserialize_tmp_passwd_list(&list, buffer, buflen);
    if (ret != 0) {
        printf("[%s][%d]rlink uartp deserialize tmp passwd list err!\r\n", __func__, __LINE__);
        if (buffer) {
            free(buffer);
            buffer = NULL;
        }
        return ret;
    }

    if (buffer) {
        free(buffer);
        buffer = NULL;
    }

    uint16_t idx = 802;
    ret = rlink_uartp_tmp_passwd_list_query_id(&list, idx);
    if (ret != 1) {
        printf("[%s][%d]not found idx: %d!\r\n", __func__, __LINE__, idx);
        ret = 0;
        rlink_uartp_destroy_tmp_passwd_list(&list);
        return ret;
    }

    uartp_tmp_passwd_t *info = NULL;
    ret = rlink_uartp_tmp_passwd_list_query_id_info(&list, idx, &info);
    if (ret != 0) {
        printf("[%s][%d]rlink uartp tmp passwd list query id info err!\r\n", __func__, __LINE__);
        return ret;
    }

    if (info) {
        _print_uartp_tmp_passwd(info);
        free(info);
    }

    ret = rlink_uartp_destroy_tmp_passwd_list(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink uartp destroy tmp passwd list err!\r\n", __func__, __LINE__);
        return ret;
    }

    return 0;
}

int db_list_app(void)
{
    int ret = 0;

#if USE_INIT_MEMORY_SECTOR
    ret = init_tmp_passwd_db_memory();
    if (ret != 0) {
        printf("[%s][%d]init_tmp_passwd_db_memory err!\r\n", __func__, __LINE__);
        return ret;
    }
    return ret;

#else
    ret = rlink_load_tmp_passwd_info();
    if (ret != 0) {
        printf("[%s][%d]rlink_load_tmp_passwd_info err!\r\n", __func__, __LINE__);
        free_fd_mem();
        return ret;
    }

    int num = 0;
    ret = rlink_read_from_flash_get_tmp_passwd_num(&num);
    if (ret != 0) {
        printf("[%s][%d]rlink_read_from_flash_get_tmp_passwd_num err!\r\n", __func__, __LINE__);
        free_fd_mem();
        return ret;
    }

    printf("[%s][%d]cur num: %d\r\n", __func__, __LINE__, num);

    #if USE_ADD_TEST
    int add_passwd_min_num = USE_TEST_ADD_NUM_MIN;
    int add_passwd_max_num = USE_TEST_ADD_NUM_MAX;
    int add_passwd_num = add_passwd_min_num;
    ret = _db_list_add_test(add_passwd_num);
    if (ret != 0) {
        printf("[%s][%d]db list add failed!\r\n", __func__, __LINE__);
        free_fd_mem();
        return ret;
    }

    free_fd_mem();
    return ret;
    #endif

    #if USE_DEL_TEST
    ret = _db_list_del_test();
    if (ret != 0) {
        printf("[%s][%d]db list del failed!\r\n", __func__, __LINE__);
        free_fd_mem();
        return ret;
    }
    free_fd_mem();
    return ret;
    #endif

    #if USE_SELECT_TEST
    ret = _db_list_query_test(0);
    if (ret != 0) {
        printf("[%s][%d]db list query failed!\r\n", __func__, __LINE__);
        free_fd_mem();
        return ret;
    }
    free_fd_mem();
    #endif

#endif

    return ret;
}
