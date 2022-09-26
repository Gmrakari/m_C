#ifndef _POLYMORPHISM_H
#define _POLYMORPHISM_H

#include <stdio.h>
#include <stdlib.h>

typedef int (*ptrFunc)(int, int);

typedef struct data {
    int a;
    int b;
    ptrFunc callback;
} data_t;

int add(int a, int b);

int sub(int a, int b);

int mul(int a, int b);

int m_div(int a, int b);

int registerFun(ptrFunc callbackFunc, int a, int b);

int registerFun2(data_t *data);

#endif // _POLYMORPHISM_H