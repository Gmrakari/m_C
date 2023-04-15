#include "http_req.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

url_data_t g_data = {0};

static char *_create_http_req_buf(const char *url, size_t len)
{
    int ret = 0;
    char *req_buf = NULL;

    if (0 != (ret = parse_url(url, &g_data, len))) {
        ret = -1;
        return NULL;
    }

    req_buf = malloc(256);

    snprintf(req_buf, 256, "GET %s HTTP/1.1\r\n
    Host:%s:%s\r\n\r\n", g_data.path, g_data.host, g_data.port);

    return req_buf;
}


char *http_get(const char *url)
{
    int ret = -1;
    int socket_fd = -1;
    int req_buf_len = 0;
    int recv_len = - 1;
    int out_len = -1;
    int offset = 0;
    int need_get_header = 1;

    char *ip = NULL;
    char *req_buf = NULL;

    url_data_t data = {0};
    struct sockaddr_in client_addr;
    char *buff = (char*)malloc(BUFF_SIZE);

    ip = host_to_ip(g_data.host);
    if (ip == NULL) {
        ret = -1;
        return ret;
    }

    req_buf = _create_http_req_buf(url);
    if (req_buf == NULL) {
        ret = -1;
        return ret;
    }

    // 1.create socketfd
    if (ret == (socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
    {
        return ret;
    }

    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = g_data.port;
    client_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(client_addr.sin_zero), 0, sizeof(client_addr.sin_zero));

    if (-1 == (ret = connect(socket_fd, (struct sockaddr *)&client_addr, sizeof(struct sockaddr)))) {
        ret = -1;
        return ret;
    }

    // 2.send http req
    req_buf_len = strlen(req_buf);
    if (req_buf_len != write(socket_fd, req_buf, req_buf_len)) {
        ret = -1;
        return ret;
    }

    // 3.recv package and data
    while (1)
    {
        // 4.up to buff_size, handle once
        recv_len = recv(socket_fd, buff + offset, BUFF_SIZE - offset, 0);
        offset += recv_len;

        if (offset == BUFF_SIZE)
        {
            if (need_get_header) {    // get http package param
                need_get_header = 0;
                // check if resp OK
                if (strncmp(HTTP_RSP_OK, (char *)buff, sizeof(HTTP_RSP_OK) - 1)) {
                    ret = -1;
                    return ret;
                }
                printf("HTTP Header: %s!\r\n", HTTP_RSP_OK);

                
            }

        }


    }





    
}