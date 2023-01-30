
#include "fun_pointer_one.h"

void (*pfun)(int data);

void myfun(int data) {
    printf("get data:%d\r\n", data);
}

// 首先定义了一个函数指针pfun,这个函数指针的返回值为void型，然后我们给函数指针赋值，赋值为myfun,也就是myfun函数的首地址
// 在C99中myfun函数名就是myfun函数的首地址，此时pfun获得了myfun的地址，pfun的地址等于myfun的地址
// 所以最终调用pfun(),也就是相当于调用了myfun()
void usage_01_test() {
    printf("--------usage_01_test--------\r\n");
    pfun = myfun;
    (*pfun)(100);
    return ;
}
