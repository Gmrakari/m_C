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

typedef struct {
    unsigned char get_dns_flag : 1;
} private_t;

static int _dns_get_ip_by_host(param_info_t *info, private_t *private_data) {
    struct hostent *hostinfo = NULL;
    char *ip = NULL;

    hostinfo = gethostbyname(info->host);

    if (!hostinfo) {
        printf("Failed to get DNS for %s\n", info->host);
        return -1;
    }

    struct in_addr **addr_list = (struct in_addr **)hostinfo->h_addr_list;
    while (*addr_list) {
        ip = calloc(1, 32);
        if (!ip) {
            return -1;
        }
        strncpy(ip, inet_ntoa(**addr_list), 32);
        break;
    }

    if (ip) {
        printf("IP for %s: %s\n", info->host, ip);
        free(ip);
        ip = NULL;
    }

    private_data->get_dns_flag = 1;

    return 0;
}

static void testFunc() {
    param_info_t info = {0};
    private_t private_data = {0};

    const char host[] = "www.baidu.com";
    strncpy(info.host, host, sizeof(info.host));

    int retry_count = 0;
    while (1) {
        if (!_dns_get_ip_by_host(&info, &private_data) || private_data.get_dns_flag) {
            break;
        }

        if (++retry_count > 5) {
            printf("Exceeded maximum retry count. Exiting...\n");
            break;
        }

        // Add a delay before retrying
        sleep(1);
    }
}

int main() {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    testFunc();
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}
