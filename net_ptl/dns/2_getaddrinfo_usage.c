#include <netdb.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <sys/types.h>
#include <sys/socket.h>
// #include <netdb.h>

int main() {
    const char *host = "www.baidu.com";
    const char *port = "80";

    struct addrinfo hints, *result, *p;

    // 清空 hints 结构体，以便初始化
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // 使用 IPv4 或 IPv6
    hints.ai_socktype = SOCK_STREAM; // 使用流式套接字
    hints.ai_protocol = 0;           // 任意协议

    // 获取地址信息
    int status = getaddrinfo(host, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    // 遍历结果，打印地址信息
    for (p = result; p != NULL; p = p->ai_next) {
        void *addr;
        char ipstr[INET6_ADDRSTRLEN];
        char ipaddr[INET_ADDRSTRLEN];

        // 获取地址信息的 IPv4 或 IPv6 地址
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // 将 IP 地址转换为字符串形式
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));

        printf("IP: %s\n", ipstr);
    }

    // 释放获取的地址信息
    freeaddrinfo(result);

    return 0;
}
