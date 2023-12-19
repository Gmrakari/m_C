#ifndef _FORMAT_PAIRS_TO_JSON_H
#define _FORMAT_PAIRS_TO_JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../third_party/cJSON/include/cJSON.h"
#include "read_file.h"

// 将字符串转换成Json格式
// in:传入需要格式化的字符串 pairs_info_t类型
// 返回值 cJSON *对象
cJSON *format_pairs_to_json(const pairs_info_t *pairs_info, const size_t pairs_num);

#ifdef __cplusplus
}
#endif


#endif // _FORMAT_PAIRS_TO_JSON_H
