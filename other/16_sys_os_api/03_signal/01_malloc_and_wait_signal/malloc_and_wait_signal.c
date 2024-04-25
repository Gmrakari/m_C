#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>

//#define BUFF_SIZE  (1024)
//#define BUFF_NUM   (1000 * 10)

#define BUFF_SIZE  (1024)
#define BUFF_NUM   (1000 * 1000)

static char *ptr = NULL;

static void sigint_handler(int signum) {
    if (ptr) {
        free(ptr);
        ptr = NULL;
        printf("Memory freed successfully.\n");
    }
    exit(signum);
}

static int _test_02() {
//    char arr[BUFF_SIZE * BUFF_NUM] = {0};

    printf("[%s][%d]\r\n", __func__, __LINE__);
}

int main() {
    signal(SIGINT, sigint_handler); // 注册SIGINT信号处理函数

    _test_02();

    printf("[%s][%d]\r\n", __func__, __LINE__);

    size_t len = sizeof(char) * BUFF_SIZE * BUFF_NUM;
    ptr = (char*)malloc(len);
    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("[%s][%d]%02X\r\n", __func__, __LINE__, ptr[0]);

    while (1) {
        // 循环等待信号
        //sleep(500);
    }

    return 0;
}
