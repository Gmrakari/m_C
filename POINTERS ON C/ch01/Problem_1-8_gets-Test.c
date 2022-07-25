/*
 * @Author: Gmrakari gmrakari@outlook.com
 * @Date: 2022-07-25 10:45:29
 * @func:
 * @Parm:
 * @return:
 * @Filename: Problem_1-8_gets-Test.c
 * @Description:
 */

#include <stdio.h>
#include <string.h>

void test()
{
    char str[10];
    char *input = str;
    char output[10] = {0};
    while (gets(input) != NULL)
    {
        printf("do fun\n");
        break;
    }
    int nlength = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        nlength++;
    }
    strncpy(output, input, nlength + 1);
    // output[nlength + 1] = '\0';
    fputs(output, stdout);
    printf("\n");
}

int main()
{
    test();
}