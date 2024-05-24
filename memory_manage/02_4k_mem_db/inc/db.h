#ifndef _DB_H_
#define _DB_H_

/**
 *  Global View
 * 
 *  Sector size         = BLOCK_SIZE
 *  Head size           = sizeof(db_header_t)
 *  None size           = BLOCK_SIZE - sizeof(db_header_t)
 *  All face info size  = DB_NUM * DB_ITEM_SIZE    (Valid size is sizeof(db_item_t))
 *  ___________________________________________________________________________
 * |      Sector0      |      Sector1      |      ...      |      SectorN      |
 * |___________________|___________________|_______________|___________________|
 * | Head |    None    |                      All face info                    |
 * |______|____________|_______________________________________________________|
*/


// #define DB_HEAD_SIGN    (0xAB5555AB)
// #define DB_HEAD_VERSION (0x00000001)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint16_t idx;           // 密码id
    uint8_t device_id;      // 用户id
    uint8_t passwd_len;     // 密码长度
    uint8_t passwd[9];      // 8位有效数字密码
    uint8_t time_type;      // 时效类型:1:永久;2:单次;3:限时
    uint32_t active_time;   // 生效时间戳(秒级)
    uint32_t expired_time;  // 失效时间戳(秒级)
    uint8_t start_time[6];  // 开始时间
    uint8_t end_time[6];    // 结束时间
    uint8_t loops[8];       // 周期(0000000,7位数从星期一开始)
} __attribute__((packed)) uartp_tmp_passwd_t;

typedef struct uartp_tmp_passwd_node_t {
    uartp_tmp_passwd_t data;
    struct uartp_tmp_passwd_node_t *next;
} uartp_tmp_passwd_node_t;

#define THING_TMP_PASSWD_MAGIC_HEAD_NUM    (0x9531)

int get_fd_mem(uint8_t **mem_ptr);

int free_fd_mem(void);

int tmp_passwd_db_app(void);

#endif // _DB_H_