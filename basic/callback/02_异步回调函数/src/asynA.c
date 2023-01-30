#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "A.h"

// 底层实现A
typedef struct parameter {
    int a;
    pcb callback;
} parameter;

void *callback_thread(void *p1) {    // 用一个线程
    //do something
    parameter *p = (parameter*)p1;
    sleep(5);
    p->callback(p->a);    //函数指针执行函数，这个函数来自于应用层B
}

// 留给应用层B的接口函数
void SetCallBackFun(int a, pcb callback) {
    printf("A:start\n");
    parameter *p = malloc(sizeof(parameter));
    p->a = a;
    p->callback = callback;

    // create thread
    pthread_t pid;
    pthread_create(&pid, NULL, callback_thread, (void *)p);
    printf("A:end\r\n");

    // 阻塞，等待线程pid结束，才往下走
    pthread_join(pid, NULL);
}
