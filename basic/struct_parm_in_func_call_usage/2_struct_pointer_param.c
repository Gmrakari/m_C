#include <stdio.h>
#include <stdint.h>
#include <string.h> // strlen
#include <stdlib.h> // malloc

typedef struct {
    char *key;
    int key_len;
    char *data;
    int data_len;
    char *pwd;
    int *pwd_len;
} gen_passwd_param_t;

#define BUF_MAX_LEN (10)

static void func(gen_passwd_param_t *param) {
    if (!param) return ;

    char buf[] = "buf";
    uint32_t num = 0;

    param->key = (char*)malloc(BUF_MAX_LEN);
    if (!param->key) return ;
    snprintf(param->key, BUF_MAX_LEN, "%s%d", buf, num++);
    param->key_len  = strlen(param->key);

    // 注意:两种取长度的区别
    // param->key_len = snprintf(NULL, 0, param->key);
    // printf("len:%d\r\n", len);
    // printf("param->key_len:%d\r\n", param->key_len );

    param->data = (char*)malloc(BUF_MAX_LEN);
    if (!param->data) return ;
    snprintf(param->data, BUF_MAX_LEN, "%s%d", buf, num++);
    param->data_len  = strlen(param->data);

    param->pwd = (char*)malloc(BUF_MAX_LEN);
    if (!param->pwd) return ;
    snprintf(param->pwd, BUF_MAX_LEN, "%s%d", buf, num++);

    param->pwd_len = (int*)malloc(sizeof(int));
    if (!param->pwd_len) return ;

    // 方式一:
    // int value = 10;
    // memcpy(param->pwd_len, &value, sizeof(int));

    // 方式二:
    *param->pwd_len = 10;
}

static void printFunc(gen_passwd_param_t *param) {
    if (!param || !param->key || !param->data || !param->pwd) return ;

    printf("key:%s\r\n", param->key);
    printf("key_len:%d\r\n", param->key_len);
    printf("data:%s\r\n", param->data);
    printf("data_len:%d\r\n", param->data_len);
    printf("pwd:%s\r\n", param->pwd);
    // printf("pwd_len:%d\r\n", param->pwd_len); // err:print pwd_len address
    printf("pwd_len:%d\r\n", *param->pwd_len);   // ok: print pwd_len value
}

static void freeFunc(gen_passwd_param_t *param) {
    if (param->data) { free(param->data); param->data = NULL; }
    if (param->key) { free(param->key); param->key = NULL; }
    if (param->pwd) { free(param->pwd); param->pwd = NULL; }
    if (param->pwd_len) { free(param->pwd_len); param->pwd_len = NULL; }
}

static void testFunc(void) {

    gen_passwd_param_t param = {
                                .data = NULL, 
                                .key_len = 0, 
                                .data = NULL, 
                                .data_len = 0, 
                                .pwd = NULL, 
                                .pwd_len = NULL
    };

    func(&param);

    printFunc(&param);

    freeFunc(&param);
}

int main() {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    testFunc();
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}