#include <stdio.h>

/* 函数的形参的作用域在于函数内部，如果加了{}符号，那么类型的定义作用域只能是在{}内 */
void func(int a, int c)
{
    printf("before a:%d\n", a); // a = 0;

    // int a = 0;
    // printf("after a:%d\n", a);
    {
        int c = 1;
        printf("after c:%d\n", c); // c = 1;
    }
    printf("out of defined c,this is before c:%d\n", c); // c = 0;
    return;
}

int main()
{
    int a, c;
    a = c = 0;
    func(a, c);
    return 0;
}