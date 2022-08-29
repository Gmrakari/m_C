#include <stdio.h>

/*
** 指针的指针需要用到指针的地址
** char c = 'A';
** char *p = &c;
** char **cp = &p;
**
** 通过指针的指针，不仅可以访问它指向的指针，还可以访问它指向的指针所指向的数据
** char *p1 = *cp;
** char c1 = **cp;
**
**
*/

// 利用指针的指针可以允许被调用函数修改局部指针变量和处理指针数组。
// return -4
void FindCredit(int **fpp)
{
    while (**fpp != 0)
    {
        if (**fpp < 0)
            break;
        else
            (*fpp)++;
    }
}

int main()
{
    int vals[] = {7, 6, 5, -4, 3, 2, 1, 0};
    int *fp = vals;
    FindCredit(&fp);
    printf("%d\n", *fp);
}
