#include <stdio.h>

enum MONEY
{
    PENNEY = 1,
    NICKEL = 5,
    DIME = 10,
    QUARTER = 25
};

void funcTest()
{
    enum MONEY output;
    output = PENNEY;
    printf("%d\n", output);

    for (output = PENNEY; output <= QUARTER; output++)
    {
        printf("data element:%d\n", output); //会输出1-25的值 然后打印出来
    }
}

int main()
{
    funcTest();
}
