#include "header.h"

extern pf_callback g_ptrFun;

void mgmtbFun(int event) {
    // 这时会跳转到callBackFun
    // 在main方法中把callBackFun赋值给了pf_callback函数指针
    // 这时的g_ptrFun指向callBackFun
    g_ptrFun(event);
}