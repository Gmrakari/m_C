#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int flag = 0;

static int thread_a = 0;
static int thread_b = 0;

void* threadA(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // 线程A的工作
        printf("Thread A is working\n");
        printf("thread_a:%d\n", thread_a++);
        // sleep(2); // 模拟线程A执行时间

        if (thread_a >= 100) {
            flag = 1; // 设置标志位表示线程A执行完毕
            pthread_cond_signal(&cond); // 发送信号通知等待的线程B
            pthread_mutex_unlock(&mutex);
            break; // 退出循环
        }

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* threadB(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        // while (flag == 0) {
        //     pthread_cond_wait(&cond, &mutex); // 等待线程A执行完毕的信号
        // }
        // 线程B的工作
        printf("Thread B is working\n");
        printf("thread_b:%d\n", thread_b++);
        pthread_mutex_unlock(&mutex);

        if (thread_b >= 150) {
            break; // 退出循环
        }
    }
    return NULL;
}

int main() {
    pthread_t tidA, tidB;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建线程A和线程B
    pthread_create(&tidA, NULL, threadA, NULL);
    pthread_create(&tidB, NULL, threadB, NULL);

    // 等待线程A和线程B结束
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
