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

#define USE_INIT_MEMORY_SECTOR       (0)
#define USE_WRITE_TO_FLASH           (1)
#define USE_READ_FROM_FLASH          (1)

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

int free_fd_mem()
{
    if (priv.ptr) {
        munmap(priv.ptr, DEFAULT_MEM_SIZE);
    }

    close(priv.fd);

    return 0;
}

static int init_tmp_passwd_info(uint8_t *ptr)
{
    uint32_t magic_header = 0;
    uint32_t default_magic_header = THING_TMP_PASSWD_MAGIC_HEAD_NUM;
    memcpy(&magic_header, ptr, sizeof(uint32_t));

    if (magic_header != THING_TMP_PASSWD_MAGIC_HEAD_NUM) {
        printf("[%s][%d]init\r\n", __func__, __LINE__);
        memset(ptr, 0x00, DEFAULT_MEM_SIZE);
        memcpy(ptr, &default_magic_header, sizeof(uint32_t));
    }

    return 0;
}

int write_tmp_passwd_node_info_from_flash(uint8_t *ptr, uartp_tmp_passwd_t *data)
{
    if (!ptr || !data) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    uint32_t offset = 0;
    uint8_t cur_num = 0;
    uint8_t old_num = 0;

    memcpy(&old_num, ptr + offset, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    cur_num = old_num + 1;
    memcpy(ptr + offset, &cur_num, sizeof(uint8_t));
    offset += sizeof(uint8_t);

    offset += (old_num * sizeof(uartp_tmp_passwd_t));

    memcpy(ptr + offset, data, sizeof(uartp_tmp_passwd_t));

    return 0;
}

int read_tmp_passwd_node_info_from_flash(uint8_t *ptr, uint8_t *passwd_num, uint8_t **passwd_list)
{
    if (!ptr || !passwd_num) {
        printf("[%s][%d]param invalid!\r\n", __func__, __LINE__);
        return -1;
    }

    uint16_t offset = 0;
    offset += sizeof(uint16_t); // header
    uint8_t num = 0;

    memcpy(&num, ptr + offset, sizeof(uint16_t));
    *passwd_num = num;

    if (num == 0) {
        return 0;
    }

    offset += sizeof(uint8_t);
    uint32_t buffer_len = num * sizeof(uartp_tmp_passwd_t);

    *passwd_list = malloc(buffer_len);
    if (!*passwd_list) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    memcpy(*passwd_list, ptr + offset, buffer_len);

    return 0;
}

static int _init_uartp_tmp_passwd_param(uartp_tmp_passwd_t *passwd, int idx)
{
    if (!passwd || !idx) {
        printf("[%s][%d]invalid pararm!\r\n", __func__, __LINE__);
        return -1;
    }

    memset(passwd, 0x00, sizeof(uartp_tmp_passwd_t));
    passwd->passwd_len = sizeof(passwd->passwd) - 1;
    strncpy(passwd->loops, "0000000", sizeof(passwd->loops));
    passwd->time_type = 1;
    passwd->device_id = 1;

    switch (idx) {
        case 1:
        {
            passwd->idx = 801;
            strncpy(passwd->passwd, "12345678", sizeof(passwd->passwd));
            passwd->active_time = 1617181920;
            passwd->expired_time = 1718192021;
            strncpy(passwd->start_time, "08:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "09:00", sizeof(passwd->end_time));
            break;
        }
        case 2:
        {
            passwd->idx = 802;
            passwd->passwd_len = sizeof(passwd->passwd) - 1;
            strncpy(passwd->passwd, "45612378", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "10:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "11:00", sizeof(passwd->end_time));
            break;
        }
        case 3:
        {
            passwd->idx = 803;
            passwd->passwd_len = sizeof(passwd->passwd) - 1;
            strncpy(passwd->passwd, "78945612", sizeof(passwd->passwd));
            strncpy(passwd->start_time, "12:00", sizeof(passwd->start_time));
            strncpy(passwd->end_time, "13:00", sizeof(passwd->end_time));
            break;
        }
        default:
        break;
    }

    return 0;

#if 0
    uartp_tmp_passwd_t passwd2;
    memset(&passwd2, 0x00, sizeof(uartp_tmp_passwd_t));
    passwd2.idx = 802;
    passwd2.device_id = 1;
    passwd2.passwd_len = sizeof(passwd2.passwd) - 1;
    strncpy(passwd2.passwd, "45612378", sizeof(passwd2.passwd));
    passwd2.time_type = 2;
    passwd2.active_time = 1617181922;
    passwd2.expired_time = 1718192023;
    strncpy(passwd2.start_time, "12:00", sizeof(passwd2.start_time));
    strncpy(passwd2.end_time, "13:00", sizeof(passwd2.end_time));
    strncpy(passwd2.loops, "0000000", sizeof(passwd2.loops));
#endif

}

static void print_uartp_tmp_passwd(const uartp_tmp_passwd_t *passwd_info)
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

int tmp_passwd_db_list_app(void)
{
    uint8_t *ptr = NULL;
    if (get_fd_mem_ptr(&ptr) != 0) {
        return -1;
    }

#if USE_INIT_MEMORY_SECTOR
    memset(ptr, 0x00, DEFAULT_MEM_SIZE);
#endif

#if USE_READ_FROM_FLASH
    init_tmp_passwd_info(ptr);

    int ret = 0;
    uint8_t passwd_num = 0;
    uint8_t *pass_list = NULL;

    uartp_tmp_passwd_t tmp;

    uartp_tmp_passwd_t passwd;
    uartp_tmp_passwd_t passwd2;
    uartp_tmp_passwd_t passwd3;
    _init_uartp_tmp_passwd_param(&passwd, 1);
    _init_uartp_tmp_passwd_param(&passwd2, 2);
    _init_uartp_tmp_passwd_param(&passwd3, 3);

    uint16_t find_idx = 802;

    uint32_t print_offset = sizeof(uartp_tmp_passwd_t);
    if (read_tmp_passwd_node_info_from_flash(ptr, &passwd_num, &pass_list) == 0) {
        printf("[%s][%d]passwd_num: %d\r\n", __func__, __LINE__, passwd_num);

        for (int i = 0; i < passwd_num; i++) {
            memset(&tmp, 0x00, sizeof(uartp_tmp_passwd_t));
            memcpy(&tmp, pass_list + (print_offset * i), sizeof(uartp_tmp_passwd_t));
            if (tmp.idx == find_idx) {
                print_uartp_tmp_passwd(&tmp);
            }
        }
        free(pass_list);
    }
#endif

#if USE_WRITE_TO_FLASH
    ret = write_tmp_passwd_node_info_from_flash(ptr, &passwd);

    ret = write_tmp_passwd_node_info_from_flash(ptr, &passwd2);

    ret = write_tmp_passwd_node_info_from_flash(ptr, &passwd3);

    if (read_tmp_passwd_node_info_from_flash(ptr, &passwd_num, &pass_list) == 0) {
        printf("[%s][%d]passwd_num: %d\r\n", __func__, __LINE__, passwd_num);
        free(pass_list);
    }

#endif

    free_fd_mem();

    return 0;
}

int db_list_app(void)
{
    int ret = 0;

    printf("[%s][%d]\r\n", __func__, __LINE__);

    ret = rlink_load_tmp_passwd_info();
    if (ret != 0) {
        printf("[%s][%d]rlink_load_tmp_passwd_info err!\r\n", __func__, __LINE__);
        return ret;
    }

    int num = 0;
    ret = rlink_read_from_flash_get_tmp_passwd_num(&num);
    if (ret != 0) {
        printf("[%s][%d]rlink_read_from_flash_get_tmp_passwd_num err!\r\n", __func__, __LINE__);
        return ret;
    }

    printf("[%s][%d]cur num: %d\r\n", __func__, __LINE__, num);

    uartp_tmp_passwd_t passwd;
    // uartp_tmp_passwd_t passwd2;
    // uartp_tmp_passwd_t passwd3;
    _init_uartp_tmp_passwd_param(&passwd, 1);

    uartp_tmp_passwd_list_t list;

    ret = rlink_uartp_init_tmp_passwd_list(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_init_tmp_passwd_list err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    ret = rlink_uartp_tmp_passwd_list_append(&list, &passwd);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_tmp_passwd_list_append err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    ret = rlink_write_uartp_tmp_passwd_list_to_flash(&list);
    if (ret != 0) {
        printf("[%s][%d]rlink_write_uartp_tmp_passwd_list_to_flash err!\r\n", __func__, __LINE__);
        ret = -1;
        return ret;
    }

    ret = rlink_read_from_flash_get_tmp_passwd_num(&num);
    if (ret != 0) {
        printf("[%s][%d]rlink_read_from_flash_get_tmp_passwd_num err!\r\n", __func__, __LINE__);
        return ret;
    }

    printf("[%s][%d]cur num: %d\r\n", __func__, __LINE__, num);

    uint8_t *out_list = NULL;
    uint16_t out_list_len = 0;
    ret = rlink_read_from_flash_get_list_data(&out_list, &out_list_len);
    if (ret != 0) {
        printf("[%s][%d]rlink_read_from_flash_get_list_data err!\r\n", __func__, __LINE__);
        return ret;
    }

    // rlink_uartp_serialize_tmp_passwd_list()

    ret = rlink_uartp_deserialize_tmp_passwd_list(&list, out_list, out_list_len);
    if (ret != 0) {
        printf("[%s][%d]rlink_uartp_deserialize_tmp_passwd_list err!\r\n", __func__, __LINE__);
        return ret;
    }

    if (out_list) {
        free(out_list);
        out_list = NULL;
    }

    // _init_uartp_tmp_passwd_param(&passwd2, 2);
    // _init_uartp_tmp_passwd_param(&passwd3, 3);

    free_fd_mem();

    return ret;
}
