#include "header.h"

int main()
{
    int ret;
    int arr[] = {10, 0, -10};
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len; i++)
    {
        ret = parmADD(arr[i]);
        printf("parmADD ret%d:%d\n", i + 1, ret);
    }

    for (int i = 0; i < len; i++)
    {
        ret = parmAbsolute(arr[i]);
        printf("parmAbsolute ret%d:%d\n", i + 1, ret);
    }

    return 0;
}