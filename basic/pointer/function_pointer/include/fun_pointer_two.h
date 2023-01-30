#ifndef __FUN_POINTER_USAGE_TWO_H_
#define __FUN_POINTER_USAGE_TWO_H_

#include <stdio.h>
#include <string.h>

// typedef 的功能是定义新的类型，第一句就是定义了一种pfun的类型，并定义这种类型为指向某种函数的指针，
// 这种函数以一个int为参数并返回void类型
typedef void (*pfunc)(int data);
void relfun(int data);
void usage_02_test();

#endif
