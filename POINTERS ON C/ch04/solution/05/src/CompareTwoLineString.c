#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

void func()
{
    FILE *fp;
    char preStr[BUFFSIZE];
    char curStr[BUFFSIZE];

    int prePrintFlag = 0;

    if ((fp = fopen("test.txt", "r")) == NULL)
    {
        printf("open test.txt error\n");
        return;
    }

    if (fgets(preStr, 1024, fp) != NULL)
    {
        while (fgets(curStr, 1024, fp) != NULL)
        {
            if (!strcmp(preStr, curStr))
            {
                if (prePrintFlag == 0)
                {
                    printf("%s", curStr);
                    prePrintFlag = 1;
                }
            }
            else
            {
                strcpy(preStr, curStr);
                prePrintFlag = 0;
            }
        }
    }

    fclose(fp);
}

int main()
{
    func();
}