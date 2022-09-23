#include "polymorphism.h"

int main() {

    int (*p[])(int a, int b) = {add, sub, mul, div};
    int a = 10, b = 2;
    int i = 0;
    for (i = 0;i < 4; i++) {
        registerFun(*p[i],a, b);
    }
}