#include "demo.h"

// 任务函数示例
void task_example(void *arg) {
    int task_id = *(int *)arg;
    printf("Task %d is running on thread %ld\n", task_id, pthread_self());
    usleep(100000);  // 模拟任务执行时间
}

void demo() {
    // 创建线程池，包含3个线程，任务队列大小为5
    threadpool_t *pool = threadpool_create(3, 9);

    // 添加10个任务到线程池
    for (int i = 0; i < 9; ++i) {
        int *task_id = malloc(sizeof(int));
        *task_id = i + 1;
        threadpool_add(pool, task_example, task_id);
    }

    // 暂停一段时间，等待任务执行
    sleep(2);

    // 销毁线程池
    threadpool_destroy(pool);
}
