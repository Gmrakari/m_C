#include <stdio.h>

int subString(char dst[], char src[], int start, int len)
{
    int getStrLen(char src[]);
    if (dst == NULL || src == NULL || start < 0 || len < 0)
    {
        dst = "";
        return 0;
    }

    int srcLen = getStrLen(src);
    if (srcLen < start)
        return 0;

    int dstIndex = 0, srcIndex;
    srcIndex = start;

    while (dstIndex < len)
    {
        if (src[srcIndex] != '\0')
        {
            dst[dstIndex++] = src[srcIndex++];
        }
        else
        {
            // dst[dstIndex] = '\0';
            break;
        }
    }
    dst[dstIndex] = '\0';
    return dstIndex;
}

int getStrLen(char src[])
{
    if (src == NULL)
        return 0;

    int strLen = 0;
    for (int i = 0; src[i] != '\0'; i++)
    {
        strLen++;
    }

    return strLen;
}

void test()
{
    char dst[30];
    char src[] = "abcdefghjikl";
    int start = 2;
    int len = 3;
    int ret = 0;
    ret = subString(dst, src, start, len);
    if (!ret)
    {
        printf("call subString error\n");
    }

    printf("%s\n", dst);

    return;
}

int main()
{
    test();
}
