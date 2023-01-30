#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "A.h"

void fCallBack(int a) {
    // do something
    printf("B:start\r\n");
    printf("a = %d\r\n", a);
    sleep(5);
    printf("B:end\r\n");
}

// author :漫漫程序之路
// article:同步回调函数和异步回调函数
// ref    :https://www.cnblogs.com/still-smile/p/12048078.html

int main() {
    SetCallBackFun(4, fCallBack);
    return 0;
}

/*
** run ret:
**
** A:start
** A:end
** (sleep 5s)
** B:start
** a = 4
** B:end
**
*/
