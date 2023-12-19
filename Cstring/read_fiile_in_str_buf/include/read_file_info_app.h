#ifndef _READ_FILE_INFO_APP_H
#define _READ_FILE_INFO_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#define FILE_PATH_MAX_LEN (256)
#define CONFIG_PATH "/res/info"

#define USE_DEBUG  1

#if USE_DEBUG
#define DEBUG(format, ...) printf("[%s][%d]"format"\r\n", __func__, __LINE__, ##__VA_ARGS__)
#endif

int read_file_info_app();

#ifdef __cplusplus
}
#endif


#endif // _READ_FILE_INFO_APP_H
