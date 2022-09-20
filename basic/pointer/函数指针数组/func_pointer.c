#include <stdio.h>
int Max(int a, int b)
{
    printf("%d\n", a > b ? a : b);
    return a > b ? a : b;
}

//将函数指针定义成类型
typedef int (*pfun)(int, int);

// func这个函数参数是(int a, int b, int(*FUN)(int, int))
//返回值是个指针，这个指针是int (*) (int, int)型函数指针
// int(*func(int a, int b, int(*FUN)(int, int))) (int, int)
pfun func(int a, int b, pfun FUN)
{
    printf("max value=%d\n", FUN(a, b));
    return FUN;
}

void main()
{
    func(1, 2, Max);
    getchar();
}