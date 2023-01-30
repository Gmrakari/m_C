#include "fun_pointer_four.h"

typedef struct gfunc {
    int (*pfunc)(int);
}gfunc;

int _myfunction(int data) {
    printf("get data:%d\r\n", data);
    return (data * 2);
}

int rt_data(int data,int (*tr_fun)()) {
    return ((*tr_fun)(data));
}

// 结构体中的函数指针指向了_myfunction的函数地址，在回调函数中我们将函数指针gf.pfunc作为rt_data(int data, int (*tr_fun)())函数
// 的参数即为int (*tr_fun)();回调函数中的return (*tr_fun)(data)相当于对指针进行了简单引用，返回这个指针指向地址的内容值
void usage_04_test() {
    printf("--------usage_04_test--------\r\n");
    int ret = 0;
    gfunc gf;
    gf.pfunc = _myfunction;
    ret = rt_data(100, gf.pfunc);
    printf("return data:%d\r\n", ret);
    return ;
}
