#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int div(int a, int b)
{
    return a / b;
}

int main()
{
    int x, y;
    int input = 0;
    int ret = 0;
    char op;

    // int (*p[5])(int x, int y) = {0, add, sub, mul, div};
    int (*p[])(int x, int y) = {0, add, sub, mul, div};
    printf("choose op(0 ~ 4) 1:add 2:sub 3:mul 4:div\n");
    scanf("%d", &input);

    switch (input)
    {
    case 1:
        op = '+';
        printf("calc add\n");
        break;
    case 2:
        op = '-';
        printf("calc sub\n");
        break;
    case 3:
        op = '*';
        printf("calc mul\n");
        break;
    case 4:
        op = '/';
        printf("calc div\n");
        break;
    default:
        break;
    }

    printf("input two op nums:\n");
    scanf("%d%d", &x, &y);
    ret = (*p[input])(x, y);
    printf("%d %c %d,ret = %d\n", x, op, y, ret);
    return 0;
}
