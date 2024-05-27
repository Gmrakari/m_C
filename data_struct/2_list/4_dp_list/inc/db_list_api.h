#ifndef _DB_LIST_API_H_
#define _DB_LIST_API_H_

#include "tmp_passwd_list_db.h"
#include <stdio.h>
#include <stdint.h>

/**
 *  Global View
 * 
 *  Sector size                = 4096
 *  ____________________________________________
 * |                Sector0 (4096)             |
 * |___________________________________________|
 * | Head |  tmp passwd num  | total data size |
 * |-------------------------------------------|
 * |__2B__|________1B________|___(N * 42)B_____|
 * |___________________________________________|
*/

// 加载临时密码
int rlink_load_tmp_passwd_info();

// 初始化链表
int rlink_uartp_init_tmp_passwd_list(uartp_tmp_passwd_list_t *list);

// 销毁链表
int rlink_uartp_destroy_tmp_passwd_list(uartp_tmp_passwd_list_t *list);

// 获取链表中num个节点数量
int rlink_uartp_tmp_passwd_list_get_num(uartp_tmp_passwd_list_t *list, uint8_t *num);

// 查询链表中的idx
int rlink_uartp_tmp_passwd_list_query_id(uartp_tmp_passwd_list_t *list, uint16_t idx);

// 往链表中增加data
int rlink_uartp_tmp_passwd_list_append(uartp_tmp_passwd_list_t *list, uartp_tmp_passwd_t *data);

// 从链表中删除index数据
int rlink_uartp_tmp_passwd_list_del(uartp_tmp_passwd_list_t *list, uint16_t index);

// 序列化临时密码链表 (list to buffer)
int rlink_uartp_serialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, uint8_t **out, uint16_t *out_len);

// 逆序列化临时密码链表(buffer to list)
int rlink_uartp_deserialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, const uint8_t *buffer, uint16_t len);

// 将链表数据写入到flash中
int rlink_write_uartp_tmp_passwd_list_to_flash(uartp_tmp_passwd_list_t *list);

// 获取flash中的临时密码数量
int rlink_read_from_flash_get_tmp_passwd_num(int *num);

// 获取flash中的序列化数据
int rlink_read_from_flash_get_list_data(uint8_t **out, uint16_t *out_len);

int debug_print_list_info(uartp_tmp_passwd_list_t *list);


#endif // _DB_LIST_API_H_