
#include <stdio.h>

int func(int year)
{
    int leap_year;
    return leap_year = year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

int main()
{
    int leap_year = 0;

    int year;

    scanf("%d", &year);

    if (year % 400 == 0)
    {
        leap_year = 1;
    }
    else
    {
        if ((year % 4 == 0) && (year % 100 != 0))
        {
            leap_year = 1;
        }
        else
        {
            leap_year = 0;
        }
    }

    if (leap_year)
    {
        printf("year:%d is leap year!\n", year);
    }
    else
    {
        printf("year:%d is not leap year!\n", year);
    }

    printf("------------------------------\r\n");
    int ret = 0;
    ret = func(year);
    if (!ret)
    {
        printf("not leap year!\n");
    }
    else
    {
        printf("leap year!\n");
    }
    return 0;
}
