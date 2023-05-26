#include <stdio.h>
#include <sys/types.h>     // size_t
#include <sys/socket.h>    // socket
#include <netinet/in.h>    // socket
#include <unistd.h>
#include <sys/time.h>      // fd_set
#include <string.h>        // strlen
#include <arpa/inet.h>    // inet_addr
#include <time.h>
#include "socket_client.h"

int sockfd = -1;

char* get_current_time_str()
{
    time_t now;
    time(&now);

    struct tm* tm_info = localtime(&now);

    static char time_str[MAX_MSG_LENGTH];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_info);

    return time_str;    
}

int client_app(void)
{
    int ret = 0;

    if (sockfd < 0) {
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("socket error");
            ret = -1;
            goto _exit;
        }

        struct sockaddr_in client_addr = {
            .sin_addr.s_addr = inet_addr(SERVER_IP),
            .sin_family = AF_INET,
            .sin_port = htons(TCP_PORT),
            .sin_zero = {0},
        };

        if (-1 == (ret = connect(sockfd, (const struct sockaddr *)&client_addr, sizeof(struct sockaddr_in)))) {
            perror("connect error");
            ret = -2;
            goto _exit;
        }
    }

    fd_set readfds;  // 可读文件描述符集合
    int maxfd;       // 最大文件描述符

    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    maxfd = sockfd;

    while (1) {
        fd_set tmpfds = readfds;  // 临时文件描述符集合用于传递给 select 函数

        struct timeval timeout;
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        ret = select(maxfd + 1, &readfds, NULL, NULL, &timeout);
        if (ret == -1) {   // 异常处理
            perror("select error");
            break;

        } else if (ret == 0) { // 超时处理
            FD_ZERO(&readfds);
            FD_SET(sockfd, &readfds);
            timeout.tv_sec = 3;
            timeout.tv_usec = 0;

            // 发送心跳包
            ret = send(sockfd, HEARTBEAT_MSG, strlen(HEARTBEAT_MSG), 0);
            if (ret < 0)
            {
                perror("send");
            }
            printf("send heart beat message: %s\n", HEARTBEAT_MSG);
            continue;
        } else {
            if (FD_ISSET(sockfd, &tmpfds)) {
                // 可读事件
                char buffer[BUFF_SIZE] = {0};
                size_t nbytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
                if (nbytes > 0) { //处理数据
                    printf("recv buffer:%s\r\n", buffer);
                } else if (nbytes == 0) {
                    // 连接关闭
                    printf("Connection closed by the server\n");
                    break;  
                } else {
                    // recv err
                    perror("recv err\r\n");
                    break;
                }
            }
        }
    }

_exit:
    if (sockfd >= 0) {
        close(sockfd);
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return ret;
}
