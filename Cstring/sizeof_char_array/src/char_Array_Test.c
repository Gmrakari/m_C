#include <stdio.h>
int main()
{
    char arr[10] = {0};
    // for (int i = 0; i < 100; i++)
    // {
    //     arr[i] = arr[i] - 0;
    // }

    // for (int i = 0; i < (int)sizeof(arr) / sizeof(arr[0]); i++)
    // {
    //     printf("%s", arr[i]);
    // }
    // return 0;

    printf("sizeof arr:%ld\n", sizeof(arr) / sizeof(arr[0])); // sizeof arr : 10
}