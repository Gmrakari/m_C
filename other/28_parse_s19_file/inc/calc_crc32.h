#ifndef _CALC_CRC32_H_
#define _CALC_CRC32_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief CRC32计算上下文结构体
 * @details 用于管理CRC32计算状态，支持连续多块数据计算
 */
typedef struct {
    uint32_t crc;           /**< 当前CRC计算值 */
    const uint32_t* table;  /**< CRC查表数组指针 */
} crc32_context_t;

/**
 * @brief CRC32算法参数定义
 * @note 多项式: 0x04C11DB7 (IEEE 802.3)
 *       初始值: 0xFFFFFFFF
 *       结果异或: 0xFFFFFFFF
 */
#define CRC32_POLY_INIT       0xFFFFFFFFU
#define CRC32_POLY_XOROUT     0xFFFFFFFFU

/**
 * @brief 初始化CRC32计算上下文
 * @param ctx CRC32上下文指针
 */
void crc32_init(crc32_context_t* ctx);

/**
 * @brief 更新CRC32计算（处理一块数据）
 * @param ctx CRC32上下文指针
 * @param data 数据指针
 * @param length 数据长度（字节）
 */
void crc32_update(crc32_context_t* ctx, const uint8_t* data, size_t length);

/**
 * @brief 完成CRC32计算并获取结果
 * @param ctx CRC32上下文指针
 * @return 计算得到的CRC32值
 */
uint32_t crc32_finalize(crc32_context_t* ctx);

/**
 * @brief 一次性计算数据的CRC32
 * @param data 数据指针
 * @param length 数据长度（字节）
 * @return 计算得到的CRC32值
 */
uint32_t calculate_crc32(const uint8_t* data, size_t length);

#ifdef __cplusplus
}
#endif


#endif // _CALC_CRC32_H_