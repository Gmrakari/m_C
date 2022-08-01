#include <stdio.h>

/*
** 1、长 赋值给 短 （短 = 长）
** 截取低位，然后按照短整数的数据类型解析。
**
** 2、短 赋值给 长 （长 = 短）
**    a.两个数据都是无符号的数据，短整数直接高位补0。
**    b.两个数据都是有符号的数据，短整数进行符号位扩展。
**    c.两个数一个是有符号数，一个数是无符号数，那么先将短整数进行位数扩展，过程中保持数值不变，然后按照长整数的数据类型解析数据。
**
** 例如:
** double 转 float 将会丢失精度。
** float 转 double 值不变。
**
*/

void funcSolution1_4()
{
    long int a = 1;
    short int b = 2;

    // b = a;
    printf("long int a = 1, short int b = 2, b = a : %d\n", b = a);
    printf("\n");
    return;
}

void funcSolution1_5()
{
    double a = 1.0;
    float b = a;

    printf("double a = 1.0, float b, b = a : %f\n", b);
    return;
}

int main()
{
    funcSolution1_4();
    funcSolution1_5();
}