#include <stdio.h>
#include <string.h>

static void _test()
{
    char *arr[] = {"abcde", "asdqad12", "123i21y3"};

    for (int i = 0; i < 3; i++) {
        printf("arr[%d] strlen:%ld\r\n", i, strlen(arr[i]));
        if (strncmp(arr[i], "abcde", (strlen(arr[i]))) == 0) {
            printf("match %d\r\n", i);
        }
    }

}

int main()
{
    _test();
    return 0;
}

