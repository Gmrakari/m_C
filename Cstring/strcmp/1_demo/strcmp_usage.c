
#include <stdio.h>
#include <string.h>

/*
** int strcmp(const char *str1, const char *str2);
** 返回值: 如果返回值小于 0，则表示 str1 小于 str2
**        如果返回值大于 0，则表示 str1 大于 str2。
**        如果返回值等于 0，则表示 str1 等于 str2。
**
*/

int func_strcmp_test()
{
    char str[] = "abcd";
    char des[] = "eghj";

    if (!strcmp(str, des))
    {
        printf("str is :%s, des is :%s are the same!\r\n", str, des);
    }
    else
    {
        printf("the str and the des are different!\r\n");
    }

    return 0;
}

int main()
{
    int func_strcmp_test();
    int ret = func_strcmp_test();

    if (ret != 0)
    {
        printf("func_strcmp_test error : %d\r\n", ret);
    }
}