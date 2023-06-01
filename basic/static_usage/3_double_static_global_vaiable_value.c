#include <stdio.h>

void fun(int value)
{
    int ret = value;
    printf("ret:%d\n", ret);
}

static int s1;
static int s1;

int main()
{
    printf("0 % 0 :%d", 0 % 0);
    printf("%d", s1);
}
