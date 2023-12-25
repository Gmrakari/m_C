#include <stdlib.h>

#include "threadpool.h"

// 创建线程池
threadpool_t *threadpool_create(int thread_count, int queue_size) {
    threadpool_t *pool = (threadpool_t *)malloc(sizeof(threadpool_t));
    if (pool == NULL) {
        perror("Failed to allocate memory for thread pool");
        return NULL;
    }

    pool->queue = (threadpool_task_t *)malloc(queue_size * sizeof(threadpool_task_t));
    if (pool->queue == NULL) {
        perror("Failed to allocate memory for task queue");
        free(pool);
        return NULL;
    }

    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->thread_num = thread_count;
    pool->max_threads = thread_count;
    pool->cur_threads = 0;

    if (pthread_mutex_init(&(pool->lock), NULL) != 0) {
        perror("Failed to initialize mutex");
        free(pool->queue);
        free(pool);
        return NULL;
    }

    if (pthread_cond_init(&(pool->notify), NULL) != 0) {
        perror("Failed to initialize condition variable");
        pthread_mutex_destroy(&(pool->lock));
        free(pool->queue);
        free(pool);
        return NULL;
    }

    pool->threads = (pthread_t *)malloc(thread_count * sizeof(pthread_t));
    if (pool->threads == NULL) {
        perror("Failed to allocate memory for threads");
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
        free(pool->queue);
        free(pool);
        return NULL;
    }

    for (int i = 0; i < thread_count; ++i) {
        if (pthread_create(&(pool->threads[i]), NULL, threadpool_worker, (void *)pool) != 0) {
            perror("Failed to create threads");
            threadpool_destroy(pool);
            return NULL;
        }
        pool->cur_threads++;
    }

    return pool;
}

// 添加任务到线程池
int threadpool_add(threadpool_t *pool, void (*routine)(void *), void *arg) {
    pthread_mutex_lock(&(pool->lock));

    if (pool->count == pool->queue_size) {
        pthread_mutex_unlock(&(pool->lock));
        return -1; // 队列已满，添加任务失败
    }

    // 添加任务到队列
    pool->queue[pool->tail].routine = routine;
    pool->queue[pool->tail].arg = arg;
    pool->tail = (pool->tail + 1) % pool->queue_size;
    pool->count++;

    // 通知等待的线程有任务可执行
    pthread_cond_signal(&(pool->notify));

    pthread_mutex_unlock(&(pool->lock));

    return 0;
}

// 销毁线程池
int threadpool_destroy(threadpool_t *pool) {
    if (pool == NULL) {
        return -1;
    }

    pthread_mutex_lock(&(pool->lock));

    // 设置线程池状态为销毁中
    pool->thread_num = -1;

    // 通知所有等待的线程
    pthread_cond_broadcast(&(pool->notify));

    pthread_mutex_unlock(&(pool->lock));

    // 等待所有线程退出
    for (int i = 0; i < pool->cur_threads; ++i) {
        pthread_join(pool->threads[i], NULL);
    }

    free(pool->threads);
    free(pool->queue);

    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));

    free(pool);

    return 0;
}

// 线程执行函数
void *threadpool_worker(void *arg) {
    threadpool_t *pool = (threadpool_t *)arg;
    threadpool_task_t task;

    while (1) {
        pthread_mutex_lock(&(pool->lock));

        // 等待任务或者线程池被销毁
        while (pool->count == 0 && pool->thread_num > 0) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        // 判断线程池是否被销毁
        if (pool->thread_num < 0) {
            pthread_mutex_unlock(&(pool->lock));
            pthread_exit(NULL);
        }

        // 取出任务
        task.routine = pool->queue[pool->head].routine;
        task.arg = pool->queue[pool->head].arg;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count--;

        pthread_mutex_unlock(&(pool->lock));

        // 执行任务
        task.routine(task.arg);
    }

    pthread_exit(NULL);
    return NULL;
}
