#include <stdio.h>

double func(int n)
{
    if (n <= 0)
    {
        printf("can not input <= 0 number\r\n");
        return 0;
    }

    float sqrt_last, sqrt_new = 1.0;
    do
    {
        sqrt_last = sqrt_new;
        sqrt_new = (sqrt_last + n / sqrt_last) / 2;
        printf("sqrt_new:%.15e\n", sqrt_new);
    } while (sqrt_new != sqrt_last);

    printf("squre : %g\n", sqrt_new);
    return sqrt_new;
}

int main()
{
    int num;
    scanf("%d", &num);

    float ret = 0;
    ret = func(num);

    if (ret == 0)
    {
        printf("func error\r\n");
    }
    return 0;
}