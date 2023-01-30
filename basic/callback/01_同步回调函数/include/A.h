#ifndef A_H
#define A_H

typedef void (*pcb)(int a);    // 函数指针定义，后面可以直接使用pcb
void SetCallBackFun(int a, pcb callback);

#endif // A_H
