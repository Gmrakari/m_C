#ifndef _FORMAT_STR_TO_JSON_H
#define _FORMAT_STR_TO_JSON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../third_party/cJSON/include/cJSON.h"

// 将字符串转换成Json格式
// in:传入需要格式化的字符串
// out:传入
int format_str_to_json(const char *str, cJSON *json);

#ifdef __cplusplus
}
#endif


#endif // _FORMAT_STR_TO_JSON_H
