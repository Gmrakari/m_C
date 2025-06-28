#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <stdbool.h>
#include "template_demo.h"

static volatile bool exit_flag = false;
    
static void on_signal(int signo)
{
    if (signo == SIGINT || signo == SIGTERM || signo == SIGQUIT || signo == SIGPIPE) {
        exit_flag = true;
        printf("\nrecv signal: %d, exiting\n", signo);
        exit(0);
    }

    return ;
}

int main()
{
    /** redefine signal */
    signal(SIGINT, on_signal);   // Ctrl+C
    signal(SIGTERM, on_signal);  // 终止信号
    signal(SIGQUIT, on_signal);  // Ctrl+\

    demo_app();

    return 0;
}
