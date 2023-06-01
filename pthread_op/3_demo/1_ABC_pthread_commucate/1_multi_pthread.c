#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int flag = 0;

void* (*func[3]) (void *);


void* threadA(void* arg) {
    while (1) {
        printf("Thread A is running\r\n");

        // 等待键盘输入
        getchar();

        pthread_mutex_lock(&mutex);
        flag = 1; // 设置标志位表示需要执行线程C
        pthread_cond_signal(&cond); // 发送信号通知等待的线程C
        pthread_mutex_unlock(&mutex);

        printf("Thread A notifies Thread C\r\n");
    }

    return NULL;
}

void* threadB(void* arg) {
    while (1) {
        printf("Thread B is running\r\n");
        sleep(1);
    }

    return NULL;
}

void* threadC(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (flag == 0) {
            pthread_cond_wait(&cond, &mutex); // 等待线程A发出通知信号
        }
        flag = 0; // 重置标志位，以便下一次接收通知

        pthread_mutex_unlock(&mutex);

        printf("Thread C starts in Thread B\r\n");

        // 执行线程C的工作
        printf("Thread C is done\r\n");
    }

    return NULL;
}

int main() {
    pthread_t tid[3];

    func[0] = &threadA;
    func[1] = &threadB;
    func[2] = &threadC;

    // tid1 = 接收触发注册人脸线程
    // tid2 = 人脸识别线程
    // tid3 = 执行注册人脸操作
    for (int i = 0; i < 3; i++) {
        pthread_create(&tid[i], NULL, func[i], NULL);
    }
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // 创建线程A、线程B和线程C
    // pthread_create(&tidA, NULL, threadA, NULL);
    // pthread_create(&tidB, NULL, threadB, NULL);
    // pthread_create(&tidC, NULL, threadC, NULL);

    // 等待线程A结束
    // pthread_join(tidA, NULL);
    pthread_join(tid[0], NULL);

    

    // 停止线程B
    // pthread_cancel(tidB);
    pthread_cancel(tid[1]);


    // 等待线程C结束
    // pthread_join(tidC, NULL);
    pthread_join(tid[2], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
