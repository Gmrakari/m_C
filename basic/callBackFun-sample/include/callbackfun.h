#ifndef _CALLBACKFUN_H_
#define _CALLBACKFUN_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>


typedef void (*pf_callback)(int a);  // 函数指针

typedef struct Compute_ST {
    int index;
    pf_callback function;
} Compute_ST;

int registerCallBackFun(Compute_ST *registedFun); // 注册

void mgmtbFun(int num); //触发事件，实现回调

#endif // _CALLBACKFUN_H_