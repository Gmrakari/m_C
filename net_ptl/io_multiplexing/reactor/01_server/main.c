#include "reactor_server.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static void _hdl_sig(int sig)
{
    printf("app exit!\r\n");
    exit(0);
}

int main()
{
    struct sigaction sa;

    // set signal hdl func
    sa.sa_handler = _hdl_sig;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    // register signal app
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    reactor_server_app();

    printf("[%s][%d]\r\n", __func__, __LINE__);

    return 0;
}
