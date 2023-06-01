#include <stdio.h>

void sprintf_case()
{
    printf("sprintf case test:\r\n");
    char buf[5];
    int ret = sprintf(buf, "%d", 1234);
    printf("ret:%d, buf:%s\n", ret, buf); // 4, 1234

    char buf2[5];
    int ret2 = sprintf(buf2, "%d", 12345);
    printf("ret2:%d, buf2:%s\n", ret2, buf2); // 5, 12345

    printf("\n------------\r\n");
    return;
}

void snprintf_case()
{
    printf("snprintf case test:\r\n");
    char buf[5];
    int ret = snprintf(buf, sizeof(buf), "%d", 1234);
    printf("ret:%d, buf:%s\n", ret, buf); // 4, 1234

    char buf2[5];
    int ret2 = snprintf(buf2, sizeof(buf2) + 1, "%d", 12345);
    printf("ret2:%d, buf2:%s\n", ret2, buf2); // 5. 12345

    printf("\n------------\r\n");
    return;
}

void snprintf_case_2()
{
    printf("snprintf case test 2:\r\n");
    char buf[5];
    int ret = snprintf(buf, 5, "%d", 1234);
    printf("ret:%d, buf:%s\n", ret, buf); // 4, 1234

    char buf2[5];
    int ret2 = snprintf(buf2, 5, "%d", 12345);
    printf("ret2:%d, buf2:%s\n", ret2, buf2); // 5, 1234

    printf("\n------------\r\n");
    return;
}

void test()
{
    sprintf_case();
    snprintf_case();
    snprintf_case_2();

    return;
}

int main()
{
    test();
    return 0;
}