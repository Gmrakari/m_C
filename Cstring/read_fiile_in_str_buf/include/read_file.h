#ifndef _READ_FILE_H
#define _READ_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_INFO_LINE_MAX_LEN         (128)

#define INFO_PID_MAX_LEN                 (32)
#define INFO_UUID_MAX_LEN                (32)
#define INFO_SECRET_MAX_LEN              (64)
#define INFO_TOKEN_MAX_LEN               (8)

typedef struct {
    char pid[INFO_PID_MAX_LEN];
    char uuid[INFO_UUID_MAX_LEN];
    char secret[INFO_SECRET_MAX_LEN];
    char token[INFO_TOKEN_MAX_LEN];
} param_info_t;

#define PARAM_INFO_T_ELEMENT_SIZE sizeof(((param_info_t *)0)->pid)
#define PARAM_INFO_T_NUM_ELEMENTS (sizeof(param_info_t) / PARAM_INFO_T_ELEMENT_SIZE)

#define PARAM_INFO_T_STR_MAX_LEN            (16)

typedef struct {
    char *key;
    char *value;
} pairs_info_t;

// 读取filepath的信息保存到info中
// in:
// filepath 路径
// (*key_str_arr)[PARAM_INFO_T_STR_MAX_LEN] 指针数组
// param_info_t info信息
// 返回值：
// 0  读取成功
// -1 读取失败
int read_file(const char *filepath, char (*key_str_arr)[PARAM_INFO_T_STR_MAX_LEN], param_info_t *info);

// 生成pair_info键值对
// 返回值：
// 0  生成成功
// -1 生成失败
int gen_pairs_info(param_info_t *info, const char (*info_arr)[PARAM_INFO_T_STR_MAX_LEN], size_t pairs_num, pairs_info_t *pairs);

// 释放pair_info内存
int free_pairs_info(pairs_info_t *pairs, size_t pairs_num);

// 获取应用程序的绝对路径
// 返回值：
// 0  获取成功
// -1 获取失败
int get_app_file_path(char *path);

// 获取配置文件的绝对路径
// 返回值：
// 0  获取成功
// -1 获取失败
int get_config_file_path(char *path);

#ifdef __cplusplus
}
#endif


#endif // _READ_FILE_H
