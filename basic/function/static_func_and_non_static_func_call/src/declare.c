#include "declare.h"

static void _static_func_1(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    _nonstaic_func();
}

void _func_test1(int data)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);

    // error: static declaration of _static_func_1 follows non-static declaration
    // 普通函数不能调用静态成员函数
    // _static_func_1(); 

    // _static_func_1();

    _static_func_1();

    // _nonstaic_func();
    return ;
}

void _nonstaic_func()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
}


static void _static_func_2(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
}

// 普通函数可以调用静态函数
void _func_test2(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    _static_func_2();
}
