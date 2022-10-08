#include <stdio.h>

void func1() {
    printf("fun1:\r\n");
    int i[10];
    printf("i:%p\n", i);
    int *p = &i[0];
    int offset;

    p += offset;

    printf("p:%p\n", p);
    printf("p:%x\n", p);
    printf("*p:%d\n", *p);
    
    printf("----------------------\n");
    return ;
}

void func2() {
    printf("fun2:\r\n");
    int i[10];
    printf("i:%p\n", i);

    int *p = &i[0];
    int offset;

    p += 3;

    printf("p:%p\n", p);
    printf("p:%x\n", p);
    printf("*p:%d\n", *p);

    printf("----------------------\n");
    return ;
}

int main() {
    func1();
    func2();

    return 0;
}