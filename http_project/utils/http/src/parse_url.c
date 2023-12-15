#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parse_url.h"
#include "../include/http.h"

int parse_url(const char *url, size_t in_url_len, url_package_t *out_data) {
    int ret = 0;
    if (url == NULL || out_data == NULL || in_url_len > PARSE_URL_PTL_SIZE + PARSE_URL_HOST_SIZE + PARSE_URL_PORT_SIZE + PARSE_URL_PATH_SIZE) { 
        ret = -1;
        return ret;
    }

    const char *p = url;
    const char *end = url + in_url_len;
    size_t count = 0;
    int port = -1;

    // match Protocol
    while (p < end && *p != ':' && *p != '/') {
        out_data->ptl[count++] = *p++;
    }
    out_data->ptl[count] = '\0';

    // match Host
    count = 0;
    p++;  // match :

    // match //
    while (*p == '/') {
        p++;
    }

    while (p < end && *p != ':' && *p != '/') {
        out_data->host[count++] = *p++;
    }
    out_data->host[count] = '\0';

    // match port
    count = 0;
    if (p < end && *p == ':') { 
        p++; // match ':'
        port = 0;
        while (p < end && *p != '/') {
            port = port * 10 + (*p - '0');
            out_data->port[count++] = *p++;
        }
        out_data->port[count] = '\0';
    } else {
        if (!strcmp(out_data->ptl, "https")) {
            port = DEFAULT_HTTPS_PORTS;
        } else {
            port = DEFAULT_HTTP_PORT;
        }
    }

    count = 0;
    while (p < end) {
        out_data->path[count++] = *p++;
    }
    out_data->path[count] = '\0';

    return ret;
}
