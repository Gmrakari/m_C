#include <stdio.h>

void ret(void) {
    int ret = 0;
    int param = 1;
    int get_scanf_num;

    do {
        printf("[%s][%d]\r\n", __func__, __LINE__);
        if (param) {
            int num = 0;
            printf("start to get scanf num\r\n");
            scanf("%d", &get_scanf_num);
            num = get_scanf_num;
            if (num != 0) {
                printf("[%s][%d]\r\n", __func__, __LINE__);
                param = 0;
            }
            printf("[%s][%d]\r\n", __func__, __LINE__);
            ret = num;
        }
        printf("[%s][%d]\r\n", __func__, __LINE__);

    } while (ret == 0);

}

int func(void) {
    int successful = 0;
    if (successful) {
        printf("successful:%d\r\n", successful);
        return successful;
    }
    return 0;
}

int ret_func() {
    int ret = 0;
    if (!(ret = func())) {
        printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("ret:%d\r\n", ret);
        return ret;
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("ret:%d\r\n", ret);
    return 0;
}

int main(int argc, char const *argv[]) {
    // ret();
    ret_func();
}
