#ifndef _IMG_UTILS_H_
#define _IMG_UTILS_H_

#include <stdio.h>

#define DEBUG_MODE 1
#if DEBUG_MODE
    #define LOGD(format, ...)   printf("[%s](%d) " format, __func__, __LINE__, ##__VA_ARGS__)
#endif

int read_jpg_from_file(const char *filename, unsigned char **buf, size_t *buf_len);

int app_test();

#endif // _IMG_UTILS_H_