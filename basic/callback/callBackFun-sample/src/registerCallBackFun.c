#include "callbackfun.h"

pf_callback g_ptrFun;

int registerCallBackFun(Compute_ST *registedFun) {
    int index;
    index = registedFun->index;
    if (!index) {
        printf("registe failed\n");
        return -1;
    }
    g_ptrFun = registedFun->function;    // 注册函数
}
