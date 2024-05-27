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

int rlink_load_tmp_passwd_info();

int rlink_uartp_init_tmp_passwd_list(uartp_tmp_passwd_list_t *list);

int rlink_uartp_destroy_tmp_passwd_list(uartp_tmp_passwd_list_t *list);

int rlink_uartp_tmp_passwd_list_get_num(uartp_tmp_passwd_list_t *list, uint8_t *num);

int rlink_uartp_tmp_passwd_list_query_id(uartp_tmp_passwd_list_t *list, uint16_t idx);

int rlink_uartp_tmp_passwd_list_append(uartp_tmp_passwd_list_t *list, uartp_tmp_passwd_t *data);

int rlink_uartp_tmp_passwd_list_del(uartp_tmp_passwd_list_t *list, uint16_t index);

int rlink_uartp_serialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, uint8_t **out, uint16_t *out_len);

int rlink_uartp_deserialize_tmp_passwd_list(uartp_tmp_passwd_list_t *list, const uint8_t *buffer, uint16_t len);

int rlink_write_uartp_tmp_passwd_list_to_flash(uartp_tmp_passwd_list_t *list);

int rlink_read_from_flash_get_tmp_passwd_num(int *num);

int rlink_read_from_flash_get_list_data(uint8_t **out, uint16_t *out_len);


#endif // _DB_LIST_API_H_