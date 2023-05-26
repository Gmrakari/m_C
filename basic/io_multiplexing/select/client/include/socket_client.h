#ifndef __SOCKET_CLIENT_H
#define __SOCKET_CLIENT_H

#include <string.h>
#include <time.h>

#define BUFF_SIZE (1024)
#define TCP_PORT (8000)
#define SERVER_IP "127.0.0.1"
#define MAX_MSG_LENGTH 256

char *get_current_time_str();

#define GET_CURRENT_TIME_STR() get_current_time_str()
#define HEARTBEAT_MSG "{heartbeat msg - "GET_CURRENT_TIME_STR()"}"

int client_app(void);

#endif // __SOCKET_CLIENT_H