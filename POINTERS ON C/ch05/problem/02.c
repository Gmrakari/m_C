#include <stdio.h>

int func(void)
{
    static int counter = 1;
    return ++counter;
}

int main()
{
    int answer;
    answer = func() - func() * func(); //先执行func(), 再执行func() * func()得到的结果 最后与前面func()相减
    printf("answer:%d\n", answer);     // func() = 2, func() * func() -> 2 - 3 * 4 = -10
}