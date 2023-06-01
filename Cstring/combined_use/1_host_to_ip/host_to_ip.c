#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>

char *host_to_ip(const char *host) 
{
    int ret = -1;
    char *ip = NULL;
    struct hostent *he = gethostbyname(host);
    if (he == NULL) {
        ret = -1;
        return NULL;
    }

    char **alias = he->h_aliases;
    while (*alias != NULL) {
        alias++;
    }

    struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
    while (*addr_list != NULL) {
        ip = calloc(1, 256);
        if (ip == NULL) {
            return NULL;
        }
        ip = inet_ntoa(**addr_list);
        break;
    }
    
    return ip;
}

int main() {
    char *host = "www.baidu.com";
    char *ip = host_to_ip(host);
    printf("ip:%s\r\n", ip);
}
