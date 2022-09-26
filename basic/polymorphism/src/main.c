#include "polymorphism.h"

void test1() {
    int a = 10, b = 2;
    int (*p[])(int a, int b) = {add, sub, mul, m_div};
    int i = 0;

    for (i = 0;i < 4; i++) {
        registerFun(*p[i],a, b);
    }

    return ;
}

void test2() {
    data_t *mData = (data_t*)malloc(sizeof(data_t));
    int a = 10, b = 2;
    mData->a = a;
    mData->b = b;
    mData->callback = add;
    registerFun2(mData);

    free(mData);
    mData = NULL;

    data_t *mData2[4];

    for (int i = 0; i < 4; i++) {
         mData2[i] = (data_t *)malloc(sizeof(data_t));
    }

    int (*p[])(int a, int b) = {add, sub, mul, m_div};

    for(int i = 0;i < 4; i++) {
        mData2[i]->a = a;
        mData2[i]->b = b;
        mData2[i]->callback = *p[i];
        registerFun2(mData2[i]);
    }

    for(int i = 0;i < 4; i++) {
        free(mData2[i]);
        mData2[i] = NULL;
    }
}

int main() {
    //test1();
    test2();
    return 0;
}