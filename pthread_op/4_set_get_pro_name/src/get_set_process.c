#include "get_set_process.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <signal.h>

int print(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return 0;
}

// 设置进程名字
void set_process_name(const char *name) {
    prctl(PR_SET_NAME, name, 0, 0, 0);
}

// 获取进程名字
void get_process_name() {
    char name[64];
    prctl(PR_GET_NAME, name, 0, 0, 0);
    printf("Process name: %s\n", name);
}

// 设置父进程终止时子进程接收的信号
void set_parent_death_signal(int signal) {
    prctl(PR_SET_PDEATHSIG, signal, 0, 0, 0);
}

// 获取父进程终止时子进程接收的信号
void get_parent_death_signal() {
    int deathsig = prctl(PR_GET_PDEATHSIG, 0, 0, 0, 0);
    printf("Parent death signal: %d\n", deathsig);
}

// 设置进程核心转储是否可用
void set_dumpable(int value) {
    prctl(PR_SET_DUMPABLE, value, 0, 0, 0);
}

// 获取进程核心转储是否可用
void get_dumpable() {
    int dumpable = prctl(PR_GET_DUMPABLE, 0, 0, 0, 0);
    printf("Process is dumpable: %d\n", dumpable);
}

void app()
{
    // 设置进程名字为 "my_process"
    set_process_name("pro_name");
    // 获取进程名字
    get_process_name();

    // 设置父进程终止时子进程接收的信号为 SIGTERM
    set_parent_death_signal(SIGTERM);

    // 获取父进程终止时子进程接收的信号
    get_parent_death_signal();

    // 设置进程核心转储是否可用为 1（可用）
    set_dumpable(1);
    // 获取进程核心转储是否可用
    get_dumpable();
}
