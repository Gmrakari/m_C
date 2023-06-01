#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

#define THREAD_NUM 3

typedef struct {
    pthread_t tid[THREAD_NUM];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int flag;
} param_data_t;

static param_data_t s_param_data = {0};

void* (*func[THREAD_NUM])(void *);


static bool exit_flag = false;

static void on_signal(int signo)
{
  if (SIGINT == signo || SIGTSTP == signo || SIGTERM == signo || SIGQUIT == signo || SIGPIPE == signo || SIGKILL == signo)
  {
    exit_flag = 1;
  }
}

void* thread_wait_enroll_face(void* arg) {
    while (!exit_flag) {
        printf("Thread_wait_enroll_face\r\n");

        // 等待键盘输入,模拟触发注册
        getchar();

        pthread_mutex_lock(&s_param_data.mutex);
        s_param_data.flag = 1; // 设置标志位表示需要执行线程thread_op_db
        pthread_cond_signal(&s_param_data.cond); // 发送信号通知等待的线程thread_op_db
        pthread_mutex_unlock(&s_param_data.mutex);

        printf("通知thread_op_db线程work\r\n");
    }

    return NULL;
}

void* thread_face_recognize(void* arg) {
    while (!exit_flag) {
        printf("Thread_face_recognize is running\r\n");
        sleep(1);
    }

    return NULL;
}

void* thread_op_db(void* arg) {
    while (!exit_flag) {
        pthread_mutex_lock(&s_param_data.mutex);
        while (s_param_data.flag == 0) {
            pthread_cond_wait(&s_param_data.cond, &s_param_data.mutex); // 等待线程thread_wait_enroll_face发出通知信号
        }
        s_param_data.flag = 0; // 重置标志位，以便下一次接收通知

        pthread_mutex_unlock(&s_param_data.mutex);

        printf("thread_op_db starts in thread_face_recognize\r\n");

        // 执行线程thread_op_db的工作
        printf("thread_op_db is done\r\n");
    }

    return NULL;
}

void app_run()
{
    // tid1 = 接收触发注册人脸线程
    // tid2 = 人脸识别线程
    // tid3 = 执行注册人脸操作
    func[0] = &thread_wait_enroll_face;
    func[1] = &thread_face_recognize;
    func[2] = &thread_op_db;

    for (int i = 0; i < THREAD_NUM; i++) {
        pthread_create(&s_param_data.tid[i], NULL, func[i], NULL);
    }

    pthread_mutex_init(&s_param_data.mutex, NULL);
    pthread_cond_init(&s_param_data.cond, NULL);

    // 等待线程thread_wait_enroll_face结束
    pthread_join(s_param_data.tid[0], NULL);
    
    // 停止线程thread_face_recognize
    pthread_cancel(s_param_data.tid[1]);

    // 等待线程thread_op_db结束
    pthread_join(s_param_data.tid[2], NULL);

    pthread_mutex_destroy(&s_param_data.mutex);
    pthread_cond_destroy(&s_param_data.cond);
}

int main() {
    /** redefine signal */
    signal(SIGINT, on_signal);
    signal(SIGTERM, on_signal);

    app_run();

    return 0;
}

/* 
** 标志位 + 条件变量 + 互斥锁控制
** 1. 触发注册人脸的时候，设置标志位，表示需要执行数据库增加操作，发送信号到数据库增加操作的线程
** 2. 数据库增加操作的线程循环等待触发注册人脸发出的通知信号，得到信号，操作数据库，操作完，重置标志位
** 3. 在main中，设置人脸识别停止，在sleep(1)处取消，然后会停止执行，执行完
*/