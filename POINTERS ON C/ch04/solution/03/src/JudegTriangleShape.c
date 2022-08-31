#include <stdio.h>

void valueSwap(int *a, int *b)
{
    int tmp;
    if (*a < *b)
    {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

int JudegTriangleShapeFunc(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0)
        return 0;

    int tmp;
    if (a < b)
    {
        valueSwap(&a, &b);
    }

    if (a < c)
    {
        valueSwap(&a, &c);
    }

    if (b < c)
    {
        valueSwap(&b, &c);
    }

    if (c < 0)
    {
        printf("is not triangle\r\n");
        return 0;
    }
    else if (b + c <= a)
    {
        printf("is not triangle\r\n");
        return 0;
    }
    else if (a == b && b == c)
    {

        printf("equilateral triangle\r\n");
        return 1;
    }
    else if (a == b || b == c)
    {
        printf("an isosceles triangle\r\n");
    }
    else
    {
        printf("scalene triangle\r\n");
    }

    printf("a:%d b:%d c:%d\n", a, b, c);
    return 1;
}

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    int ret = 0;
    ret = JudegTriangleShapeFunc(a, b, c);

    if (!ret)
    {
        printf("JudegTriangleShapeFunc call error\r\n");
    }
    return 0;
}