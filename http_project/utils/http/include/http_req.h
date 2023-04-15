#ifndef _HTTP_GET_H
#define _HTTP_GET_H

#include <string.h>

#define BUF_SIZE      (1024)
#define HTTP_RSP_OK   "HTTP/1.1 200 OK"

char *http_get(const char *url);

#endif // _HTTP_GET_H
