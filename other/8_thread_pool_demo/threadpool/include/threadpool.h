#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <stdio.h>
#include <pthread.h>

typedef struct {
    void (*routine)(void *);
    void *arg;
} threadpool_task_t;

typedef struct threadpool_t{
    threadpool_task_t *queue;
    int queue_size;
    int head;
    int tail;
    int thread_num;
    int count;
    int max_threads;
    int cur_threads;
    pthread_mutex_t lock;
    pthread_cond_t notify;
    pthread_t *threads;
} threadpool_t;

// 创建线程池
threadpool_t *threadpool_create(int thread_count, int queue_size);

// 添加任务到线程池
int threadpool_add(threadpool_t *pool, void (*routine)(void *), void *arg);

// 销毁线程池
int threadpool_destroy(threadpool_t *pool);

// 线程执行函数
void *threadpool_worker(void *arg);

int app(void);

#endif // _THREADPOOL_H