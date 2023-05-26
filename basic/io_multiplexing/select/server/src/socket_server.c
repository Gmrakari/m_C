#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>    // IPPROTO_TCP
#include <arpa/inet.h>    // inet_addr
#include <unistd.h>       // close sockfd 
#include "socket_server.h"

#define TCP_SERVER_IP "127.0.0.1"
#define TCP_SERVER_PORT (8000)
#define TCP_RECV_BUFFER_SIZE (1024)

int sockfd = -1;

int server_app(void)
{
    int ret = 0;
    int newsockfd;
    socklen_t client_len;
    char buffer[TCP_RECV_BUFFER_SIZE] = {0};

    if ((ret = (sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) < 0) {
        printf("socket err\r\n");
        printf("ret:%d\r\n", ret);
        return ret;
    }

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = inet_addr(TCP_SERVER_IP),  // INADDR_ANY
        
        .sin_family = AF_INET,
        .sin_port = htons(TCP_SERVER_PORT),
        .sin_zero = {0},
    };

    if ((ret = bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))) < 0) {
        printf("ret:%d\r\n", ret);
        printf("bind err\r\n");
        return ret;
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen err\r\n");
        return -1;
    }

    printf("Server listening on port %d\n", TCP_SERVER_PORT);

    while (1) {
        client_len = sizeof(struct sockaddr_in);
        newsockfd = accept(sockfd, (struct sockaddr *)&server_addr, &client_len);
        if (newsockfd < 0) {
            perror("accept error");
            return -1;
        }

        printf("new client connect\r\n");

        while (1) {
            memset(buffer, 0, sizeof(buffer));
            size_t nbytes = recv(newsockfd, buffer, TCP_RECV_BUFFER_SIZE - 1, 0);
            if (nbytes < 0) {
                printf("recv buffer err\r\n");
                break;
            } else if (nbytes == 0) {
                printf("client disconnected\r\n");
                return -1;
            } else {
                printf("received message from client:%s\r\n", buffer);

                const char *resp_msg = "resp from server msg\r\n";
                size_t sent_bytes = send(newsockfd, resp_msg, strlen(resp_msg), 0);
                if (sent_bytes < 0) {
                    perror("send error\r\n");
                    break;
                }
            }
        }

        if (newsockfd >= 0) {
            close(newsockfd);
        }

    }

    if (sockfd >= 0) {
        close(sockfd);
    }
    
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return ret;
}
