#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int cnt = 0;

void fileOp()
{
    char filepath[] = "/home/gmrakari/github/m_C/Cstring/cnt_mtqq_lost_connfiles";
    char ret[10];
    char buffer[10];

    FILE *fp;

    int readcnt = 0;
    if ((fp = fopen(filepath, "r+")) == NULL)
    {
        printf("failed to read cnt_mtqq_lost_connfiles files\n");
    }
    else
    {
        fread(buffer, 1, 10, fp);
        fclose(fp);
    }

    if ((fp = fopen(filepath, "w")) == NULL)
    {
        printf("failed to write cnt_mtqq_lost_connfiles files\n");
    }
    else
    {
        readcnt = atoi(buffer);
        if (readcnt == 0)
        {
            sprintf(ret, "%d", ++cnt);
            fprintf(fp, "%s", ret);
        }
        else
        {
            cnt = readcnt;
            sprintf(ret, "%d", ++cnt);
            fprintf(fp, "%s", ret);
        }
        fclose(fp);
    }

    if (cnt > 9)
    {
        if ((fp = fopen(filepath, "w+")) == NULL)
        {
            printf("err:");
        }
        else
        {
            cnt = 0;
            readcnt = 0;
            sprintf(ret, "%d", cnt);
            fprintf(fp, "%s", ret);
            printf("err\n");
            fclose(fp);
        }
    }
}

void Test()
{
    fileOp();
}

int main()
{

    while (1)
    {
        Test();
        sleep(1);
    }
}