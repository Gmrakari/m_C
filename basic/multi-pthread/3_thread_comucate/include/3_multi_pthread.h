
#ifndef __3_MULTI_PTHREAD_H_
#define __3_MULTI_PTHREAD_H_

#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define THREAD_NUM 3

typedef struct {
    pthread_t tid[THREAD_NUM];
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int flag;
} param_data_t;

void* (*func[THREAD_NUM])(void *);

void on_signal(int signo);

void* thread_wait_enroll_face(void* arg);


#endif // __3_MULTI_PTHREAD_H_