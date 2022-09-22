#include <stdio.h>

/*
** test01:
** state为1，pol为0，
** value与pol异或为1
*/
void test01(int state) {
    int value = 1;
    int pol = 0;

    value = state ? 1 : 0;
    printf("state:%d, value = state ? 1 : 0; -> value:%d\n",state, value);

    value ^= pol;
    printf("pol:%d, value ^= pol; -> value:%d\n", pol, value);
    
    return ;

}

/*
** test02:
** state为0，pol为1，
** value与pol异或为1
*/
void test2(int state) {
    int value = 1;
    int pol = 1;

    value = state ? 1 : 0;
    printf("state:%d, value = state ? 1 : 0; -> value:%d\n",state, value);

    value ^= pol;
    printf("pol:%d, value ^= pol; -> value:%d\n", pol, value);
    
    return ;
}

/*
** test03:
** state为0，pol为1，
** value与pol异或为1
*/
void test3(int state) {
    int value = 1;
    int pol = 1;

    value = state ? 1 : 0;
    printf("state:%d, value = state ? 1 : 0; -> value:%d\n",state, value);

    value ^= pol;
    printf("pol:%d, value ^= pol; -> value:%d\n", pol, value);
    
    return ;
}

int main () {
    printf("test1:\r\n");
    int state = 1;
    test01(state);

    printf("\ntest2:\r\n");
    state = 0;
    test2(state);

    printf("\ntest3:\r\n");
    state = 1;
    test2(state);

    return 0;
}
