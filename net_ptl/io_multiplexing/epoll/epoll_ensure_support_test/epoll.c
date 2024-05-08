#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/epoll.h>
 
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
 
// 相比于select与poll，epoll最大的好处是不会随着关心的fd数目的增多而降低效率 
 
int main(void)
{
    int count = 0;
    int listenfd;
    if ((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("creeate socket failed: %d\n", errno);
		return -1;
	}
 
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
		printf("setsockopt failed: %d\n", errno);
		return -1;
	}
 
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		printf("bind failed: %d\n", errno);
		return -1;
	}

    if (listen(listenfd, SOMAXCONN) < 0) {
		printf("listen failed: %d\n", errno);
		return -1;
	}

    int epollfd;
    epollfd = epoll_create1(EPOLL_CLOEXEC); //epoll实例句柄
	if (epollfd <= 0) {
		printf("epoll_create1 failed: %d\n", errno);
		return -1;
	}
	
	printf("epoll check successfuly.\n");
 
    return 0;
}
