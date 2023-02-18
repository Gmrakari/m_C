#include "declare.h"

void test01(void)
{
    _func_test1(0);
}

void test02(void)
{
    _func_test2();
}

int main() {

    // test01();
    // test02();
    return 0;
}

// 结论:
// 普通函数可以调用静态函数
// 静态成员函数不能调用普通函数

