#include "fun_pointer_two.h"

void relfun(int data) {
    printf("get data:%d\r\n", data);
}

// pfun代表的是函数的类型，通过pfun来代表void (*)(int)函数类型即pfunc是指针函数的别名，pfunc p相当于定义了一个
// void (*p)(int)函数指针。 p = relfun 可以理解为将函数指针p指向relfun函数的地址，p(100) = 调用relfun(100)
void usage_02_test() {
    printf("--------usage_02_test--------\r\n");
    pfunc p = relfun;
    p(100);
    return ;
}
