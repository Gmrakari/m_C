#include <stdio.h>
// #include <netdb.h>
// struct hostent *gethostbyname(const char *name);

#include <sys/socket.h>
// struct hostent *gethostbyaddr(const void *addr, socklen_t len, int type);

#include <arpa/inet.h> // ip_addr_t
#include <string.h>

#include <netdb.h>

#include <stdlib.h>

#define STR_MAX_LEN (128)

typedef struct {
    char host[STR_MAX_LEN];
} param_info_t;

static int _dns_get_ip_by_host() {
    param_info_t info = {0};
    struct hostent *hostinfo = NULL;
    char *ip = NULL;

    char host[] = "www.baidu.com";
    strncpy(info.host, host, sizeof(info.host));

    hostinfo = gethostbyname(info.host);

    if (!hostinfo) return -1;

    struct in_addr **addr_list = (struct in_addr **)hostinfo->h_addr_list;
    while (*addr_list) {
        ip = calloc(1, 32);
        if (!ip) return -1;
        strncpy(ip, inet_ntoa(**addr_list), 32);
        break;
    }
    if (ip) {
        printf("ip:%s\r\n", ip);
        free(ip);
        ip = NULL;
    }

    return 0;
}

static void testFunc() {
    _dns_get_ip_by_host();
}

int main() {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    testFunc();
    printf("[%s][%d]\r\n", __func__, __LINE__);
}