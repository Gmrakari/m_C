
/*
** pointer func  : 是指函数返回值是某一类型的指针，本质是一个函数
** 指针函数的定义为 : 类型标识符 *函数名(参数表),例如:int *f(x, y);
** 指针函数是一个函数，只不过这个函数的返回值是一个地址值。
** 函数返回值必须用同类型的指针变量来接受，也就是说，指针函数一定有函数返回值，而且在主调函数中，函数返回值必须赋给同类型的指针变量。
** 由于返回的是一个地址，所以类型说明符一般都是int
*/

#include <stdio.h>

int *GetDate(int week, int day);

int main()
{
    int week, day;
    do
    {
        printf("Enter week(1 - 5) day(1 - 7)\n");
        scanf("%d%d", &week, &day);
    } while (week < 1 || week > 5 || day < 1 || day > 7);

    printf("%d\r\n", *GetDate(week, day));
}

//函数返回的是数组某元素的地址，然后输出的是这个地址里的值。
int *GetDate(int week, int day)
{
    static int calendar[5][7] = {
        {1, 2, 3, 4, 5, 6, 7},
        {8, 9, 10, 11, 12, 13, 14},
        {15, 16, 17, 18, 19, 20, 21},
        {22, 23, 24, 25, 26, 27, 28},
        {29, 30, 31, -1}};

    return &calendar[week - 1][day - 1];
}
