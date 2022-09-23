#include "polymorphism.h"

// 4个回调函数(callbackFunc)
int add(int a, int b) {
    printf("回调函数使用的是add()\n");
    printf("a = %d, b = %d\n", a, b);
    return a + b;
}

int sub(int a, int b) {
    printf("回调函数使用的是sub()\n");
    printf("a = %d, b = %d\n", a, b);
    return a - b;
}

int mul(int a, int b) {
    printf("回调函数使用的是mul()\n");
    printf("a = %d, b = %d\n", a, b);
    return a * b;
}

int div(int a, int b) {
    printf("回调函数使用的是div()\n");
    printf("a = %d, b = %d\n", a, b);
    return a / b;
}

int registerFun(ptrFunc callbackFunc, int a, int b) {
    int ret = callbackFunc(a, b);
    printf("ret = %d\n", ret);

    return 0;
}