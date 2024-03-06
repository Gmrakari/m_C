#ifndef _UTILS_HTTP_H
#define _UTILS_HTTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define USE_DEBUG_MODE (1)

#if USE_DEBUG_MODE
    #define DEBUG_MSG(format, ...) \
    do { \
        printf("[%d][%s]"format"\r\n", __LINE__, __func__, ##__VA_ARGS__); \
    } while (0);
#else
    #define DEBUG_MSG(format, ...)
#endif

#define PARSE_URL_PTL_SIZE  (8)
#define PARSE_URL_HOST_SIZE (32)
#define PARSE_URL_PORT_SIZE (8)
#define PARSE_URL_PATH_SIZE (256)
#define BUFF_SIZE      (1024)
#define HTTP_RSP_OK   "HTTP/1.1 200 OK"

#define DEFAULT_HTTP_PORT (9006);
#define DEFAULT_HTTPS_PORTS (443);

typedef struct {
    char ptl[PARSE_URL_PTL_SIZE];    // http / https / ws / tcp / mqtt / ftp /
    char host[PARSE_URL_HOST_SIZE];
    char port[PARSE_URL_PORT_SIZE];
    char path[PARSE_URL_PATH_SIZE];
} url_package_t;

// 解析url，将url的所有字段传出到out_data中
int parse_url(const char *url, size_t in_url_len, url_package_t *out_data);

void func(void);

// clang-format off
// static const char *http_status_code_str(int status_code);

// char *http_get(const char *url);

int http_get(const char *url);

#endif // _UTILS_HTTP_H