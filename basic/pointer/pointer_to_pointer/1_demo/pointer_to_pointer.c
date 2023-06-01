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

void test_1()
{
    int vals[] = {7, 6, 5, -4, 3, 2, 1, 0};
    int *fp = vals;
    FindCredit(&fp);
    printf("%d\n", *fp);
}

void _print_pointer_relation_info()
{
    int a = 10;
    int *p = &a;
    int **q = &p;

    printf("a = %d, &a = %p\r\n", a, &a);                           // a = 10, &a = 0x7ffd1659e494
    printf("p = %d, p = %p, &p = %p\r\n", *p, p, &p);               // *p = 10, p = &a = 0x7ffd1659e494, &p = 0x7ffd1659e498
    printf("**q = %d, *q = %p, q = %p, &q:%p\r\n", **q, *q, q, &q); // **q = 10, *q = 0x7ffd1659e494, q = 0x7ffd1659e498, &q:0x7ffd1659e4a0
}

int main()
{
    #if 0
    test_1();
    #endif

    _print_pointer_relation_info();
}
