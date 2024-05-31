#include "reactor.h"
#include <stdio.h>
#include <errno.h> // perror

#include <unistd.h> // fcntl
#include <fcntl.h>  // fcntl

#include <sys/socket.h> // struct sockaddr_in
#include <sys/epoll.h>

#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_EVENT           (10)
#define READ_BUFFER_SIZE    (1024)
#define SERVER_PORT         (5757)
#define SERVER_IP           ("127.0.0.1")

static void _set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    return ;
}

static void _hdl_conn(int listen_fd, int epoll_fd)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_sock = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock == -1) {
        perror("accept");
        return ;
    }

    printf("accepted conn from :%s :%d\r\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    _set_nonblocking(client_sock);

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = client_sock;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_sock, &ev) == -1) {
        perror("epoll_ctl: client_sock");
        close(client_sock);
    }

    return ;
}

static void _hdl_read(int client_sock, int epoll_fd) 
{
    char buf[READ_BUFFER_SIZE] = {0};
    int n = read(client_sock, buf, sizeof(buf));
    if (n <= 0) {
        if (n == 0) {
            printf("client disconnect!\r\n");
        } else {
            perror("read");
        }
    } else {
        buf[n] = '\0';
        printf("recv: %s\r\n", buf);

        if (write(client_sock, buf, n) == -1) {
            perror("write");
            close(client_sock);
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_sock, NULL);
        }
    }

    return ;
}

static void _tcp_server(void)
{
    int listen_sock, epoll_fd;
    struct sockaddr_in server_addr;
    struct epoll_event ev, events[MAX_EVENT];

    // 
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    _set_nonblocking(listen_sock);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    socklen_t server_len = sizeof(server_addr);
    if ((bind(listen_sock, (struct sockaddr *)&server_addr, server_len)) == -1) {
        perror("bind");
        close(listen_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(listen_sock, SOMAXCONN) == -1) {
        perror("lienten");
        close(listen_sock);
        exit(EXIT_FAILURE);
    }

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(listen_sock);
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        close(listen_sock);
        close(epoll_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENT, -1);

        if (nfds == -1) {
            perror("epoll_wait");
            close(listen_sock);
            close(epoll_fd);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == listen_sock) {
                _hdl_conn(listen_sock, epoll_fd);
            } else {
                _hdl_read(events[i].data.fd, epoll_fd);
            }
        }
    }

    close(listen_sock);
    close(epoll_fd);

    return ;
}

void client_reactor()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);

    _tcp_server();

    return ;
}
