#include <stdio.h>

void copy_n(char dst[], char src[], int n)
{
    if (dst == NULL || src == NULL || n <= 0)
        return;

    int index = 0;
    while (index < n && src[index] != '\0')
    {
        dst[index] = src[index];
        index++;
    }
    while (index < n)
    {
        dst[index] = '\0';
        index++;
    }
    dst[index] = '\0';

    return;
}

void copy_n2(char dst[], char src[], int n)
{
    if (n == 0)
        return;

    int dst_index, src_index;
    src_index = 0;
    for (dst_index = 0; dst_index < n; dst_index++)
    {
        dst[dst_index] = src[src_index];
        if (src[src_index] != '\0')
        {
            src_index++;
        }
    }
    dst[dst_index] = '\0';
}

void test()
{
    char str[] = "absadasdjalksdsad asda";
    char dst[30];
    printf("%d\n", strlen(str));
    printf("str1:%s\n", str);
    copy_n(dst, str, 10);
    printf("%s\n", dst);

    char str2[] = "absadasdjalksdsad asda";
    char dst2[30];
    printf("str2:%s\n", str2);
    copy_n2(dst2, str2, 10);
    printf("%s\n", dst2);
    return 0;
}

int main()
{
    test();
}