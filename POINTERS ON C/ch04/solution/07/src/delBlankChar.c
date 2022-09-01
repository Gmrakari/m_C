#include <stdio.h>
#include <string.h>

void deblank(char string[])
{
    if (string == NULL)
        return;
    int i = 0, j = 0;
    char ch;
    char tmp[50];

    while (string[i] == ' ' || string[i] == '\t') //预处理，将前面有空格的处理掉
    {
        ++i;
    }

    while (string[i] != '\0')
    {
        if ((i > 0 && string[i] == ' ' && string[i - 1] == ' ') || string[i] == ' ')
        {
            i++;
            continue;
        }
        else
        {
            tmp[j++] = string[i++];
        }
    }

    tmp[j] = '\0';
    strcpy(string, tmp);
}

void test()
{
    char str[] = "            ab     c d  e         f ";
    printf("%s\n", str);

    deblank(str);

    printf("%s\n", str);
}

int main()
{
    test();
}