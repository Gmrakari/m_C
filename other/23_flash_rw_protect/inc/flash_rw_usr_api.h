#ifndef _FLASH_RW_USR_API_H_
#define _FLASH_RW_USR_API_H_

#include <stdint.h>

int flash_rw_usr_api_app(void);

// 获取分区的crc
// addr 分区的地址
// len 分区的大小
// ocrc, output crc的值
// 获取成功 返回 0
// 失败出错 返回-1
int flash_rw_usr_api_get_crc_val(uint8_t *addr, int len, uint32_t *ocrc);

// 计算crc值
// 数据,数据长度
// 成功
int flash_rw_usr_api_check_valid(uint8_t *data, int len);

// 擦除，
// 擦除类型,0 主扇区, 1 备份扇区
// 成功返回0
// 失败出错返回-1
int flash_rw_usr_api_earse(int type);

// 写
// 类型, 写到主数据区,写到备份区
// data 数据
// len 数据长度
// 成功返回0
// 失败出错返回-1
int flash_rw_usr_api_write(int type, uint8_t *data, int len);

// 更新备份区
// 写入数据前,先将主扇区数据备份
// 主数据分区的地址src_addr, 分区大小src_len
// 备份分区的地址bak_addr, 分区大小bak_len
// 成功返回0
// 失败出错返回-1
int flash_rw_usr_api_update_bak(uint8_t *src_addr, int src_len, uint8_t *bak_addr, int bak_len);

// 从备份区恢复数据到主数据分区
// 备份分区的地址bak_addr, 分区大小bak_len
// 待恢复数据的地址dest_addr, 分区大小
// 成功返回0
// 失败出错返回-1
int flash_rw_usr_api_recover_from_bak(uint8_t *bak_addr, int bak_len, uint8_t *dest_addr, int dest_len);

// 数据写入到主分区中 
// 主数据分区的地址,分区大小
// 写入的数据
// 数据长度
// 成功返回0
// 失败出错返回-1
int flash_rw_usr_api_write_to_main_sector(uint8_t *data, int data_len);

#endif // _FLASH_RW_USR_API_H_