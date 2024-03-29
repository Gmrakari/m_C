#ifndef _PARSE_URL_H
#define _PARSE_URL_H

#if 0

#include <stdio.h>

#define PARSE_URL_PTL_SIZE  8
#define PARSE_URL_HOST_SIZE 32
#define PARSE_URL_PORT_SIZE 8
#define PARSE_URL_PATH_SIZE 256

const int DEFAULT_HTTP_PORT   = 9006;
const int DEFAULT_HTTPS_PORTS = 443;

typedef struct {
    char ptl[PARSE_URL_PTL_SIZE];    // http / https / ws / tcp / mqtt / ftp /
    char host[PARSE_URL_HOST_SIZE];
    char port[PARSE_URL_PORT_SIZE];
    char path[PARSE_URL_PATH_SIZE];
} url_data_t;

int parse_url(const char *url, url_data_t *data, size_t len);

#endif

#endif // _PARSE_URL_H
