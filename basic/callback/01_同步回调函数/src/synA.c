
#include <stdio.h>
#include "A.h"

// 底层实现A
// 留给应用层B的接口函数
void SetCallBackFun(int a, pcb callback) {
    printf("A:start\r\n");
    callback(a);
    printf("A:end\r\n");
}
