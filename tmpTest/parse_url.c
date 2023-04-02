/**
 * 
 * @filename:_parse_url.c
 * @function:
 * @return:
 * @author:Zhanyou Zhou (gmrakari@outlook.com)
 * @date:2023/4/2 21:18
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARSE_URL_PTL_SIZE  8
#define PARSE_URL_HOST_SIZE 32
#define PARSE_URL_PORT_SIZE 8
#define PARSE_URL_PATH_SIZE 256

const int DEFAULT_HTTP_PORT   = 80;
const int DEFAULT_HTTPS_PORTS = 443;

typedef struct {
    char ptl[PARSE_URL_PTL_SIZE];
    char host[PARSE_URL_HOST_SIZE];
    char port[PARSE_URL_PORT_SIZE];
    char path[PARSE_URL_PATH_SIZE];
} url_data_t;

static void _parse_url(const char *url, url_data_t *data, size_t len)
{
    if (url == NULL || data == NULL || len > PARSE_URL_PTL_SIZE + PARSE_URL_HOST_SIZE + PARSE_URL_PORT_SIZE + PARSE_URL_PATH_SIZE)
        return ;

    const char *p = url;
    const char *end = url + len;
    size_t count = 0;
    int port = -1;

    // match Protocol
    while (p < end && *p != ':' && *p != '/') {
        data->ptl[count++] = *p++;
    }
    data->ptl[count] = '\0';

    // match Host
    count = 0;
    p++;  // match :

    // match //
    while (*p == '/') {
        p++;
    }

    while (p < end && *p != ':' && *p != '/') {
        data->host[count++] = *p++;
    }
    data->host[count] = '\0';

    // match port
    count = 0;
    if (p < end && *p == ':') {
        p++; // match ':'
        port = 0;
        while (p < end && *p != '/') {
            port = port * 10 + (*p - '0');
            data->port[count++] = *p++;
        }
        data->port[count] = '\0';
    } else {
        if (!strcmp(data->ptl, "https")) {
            port = DEFAULT_HTTPS_PORTS;
        } else {
            port = DEFAULT_HTTP_PORT;
        }
    }

    count = 0;
    while (p < end) {
        data->path[count++] = *p++;
    }
    data->path[count] = '\0';
}

int main(void)
{
//    char *url = "http://openai.com:44412/public/gmrakari";
    char url[] = "https://www.example.com:8080/path/to/file";

    url_data_t url_arg = {0};

    size_t url_len = strlen(url);

    _parse_url(url, &url_arg, url_len);

    printf("url->ptl:%s\r\n", url_arg.ptl);
    printf("url->host:%s\r\n", url_arg.host);
    printf("url->port:%s\r\n", url_arg.port);
    printf("url->path:%s\r\n", url_arg.path);
}


