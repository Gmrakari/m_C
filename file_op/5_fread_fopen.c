#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static int cnt = 0;

/*
** FILE *fopen(const char *path, const char *mode);
** parm:mode字符串则代表着流形态
**
** r 打开只读文件，该文件必须存在。
** r+ 打开可读写的文件，该文件必须存在。
** w 打开只写文件，若文件存在则文件长度清为0，即该文件内容会消失。若文件不存在则建立该文件。
** w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
**
*/

/*
**  @method : fileOp()
**  @brief  : 文件操作，将文件中写入一个数字，读取文件中的数字
**  @return : 返回文件中的数字
**
*/

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