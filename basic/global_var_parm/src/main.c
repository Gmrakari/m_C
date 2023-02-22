#include "a.h"
#include "b.h"

int main()
{
    printf("start\r\n");
    funA();
    funB();
    funA();

    // int *option[] = {"5", "10", "15", "20", "25", "30"};

    // for (int i = 0; i < sizeof(option[0]) / sizeof(option); i++)
    // {
    //     printf("%d:%d\r\n", i, *option[i]);
    // }

    int option[] = {5, 10, 15, 20, 25, 30};

    for (int i = 0; i < 6; i++)
    {
        printf("%d:%d\r\n", i, option[i]);
    }

    return 0;
}
