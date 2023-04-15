#include "parse_url.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_url(const char *url, url_data_t *data, size_t len)
{
    int ret = 0;
    if (url == NULL || data == NULL || len > PARSE_URL_PTL_SIZE + PARSE_URL_HOST_SIZE + PARSE_URL_PORT_SIZE + PARSE_URL_PATH_SIZE)
    {
        ret = -1;
        return ret;
    }

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

    return ret;
}
