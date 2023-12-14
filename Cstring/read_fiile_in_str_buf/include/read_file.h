#ifndef _READ_FILE_H
#define _READ_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

int read_file(const char *filepath);

// 获取应用程序的绝对路径
// 返回值：
// -1 获取失败
// 0  获取成功
int get_app_file_path(char *path);

// 获取配置文件的绝对路径
// 返回值：
// -1 获取失败
// 0  获取成功
int get_config_file_path(char *path);

#ifdef __cplusplus
}
#endif


#endif // _READ_FILE_H
