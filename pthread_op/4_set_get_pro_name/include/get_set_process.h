#ifndef _GET_SET_PROCESS_H_
#define _GET_SET_PROCESS_H_

#include <stdio.h>

int print(void);

// 设置进程名字
void set_process_name(const char *name);

// 获取进程名字
void get_process_name();

// 设置父进程终止时子进程接收的信号
void set_parent_death_signal(int signal);

// 获取父进程终止时子进程接收的信号
void get_parent_death_signal();

// 设置进程核心转储是否可用
void set_dumpable(int value);

// 获取进程核心转储是否可用
void get_dumpable();

void app();

#endif // _GET_SET_PROCESS_H_