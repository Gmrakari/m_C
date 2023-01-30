#include "fun_pointer_three.h"

typedef struct gfun 
{
    void (*pointerfun)(int);
}gfun;

void normal_fun(int data) {
    printf("get data:%d\r\n", data);
}

// 结构体指针的用法
void usage_03_test() {
    printf("--------usage_03_test--------\r\n");
    gfun gcode = {
        .pointerfun = normal_fun,
    };

    gcode.pointerfun(100);
    return ;
}
