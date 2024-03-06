#ifndef _CAL_SHA_VALUE_H_
#define _CAL_SHA_VALUE_H_

#include <openssl/sha.h>

// 获取文件的sha256
// in:文件路径
// out:生成的哈希值是32 字节（256 位），output数组的大小应该是32 * 2 + 1
int get_file_sha256(const char *filepath, char *output);

// 比较两个哈希值是否一致
// src 32字节字符串，dest 32字节字符串
// 返回值:
// 0 比较相同
// -1 比较不同
int compare_sha256_value(const char *src, const char *dest);

#endif // _CAL_SHA_VALUE_H_