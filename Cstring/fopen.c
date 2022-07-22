#include <stdio.h>
#include <string.h>

void fileOp()
{
    int cnt = 3;
    char filepath[] = "/home/gmrakari/github/m_C/Cstring/debug_info.txt";
    char *buffer = "\"iccid\":\"898604A4192170153703\"";
    char iccid[21] = {0};
    const char endbuf[] = "\n";
    FILE *fd;

    printf("strlen(buffer):%ld\n", strlen(buffer));
    printf("sizeof(buffer):%ld\n", sizeof(buffer));

    memcpy(iccid, buffer, strlen(buffer));

    if ((fd = fopen(filepath, "ab+")) == NULL)
    {
        printf("failed to open files\n");
        return;
    }

    fprintf(fd, endbuf);
    while (cnt--)
    {
        fprintf(fd, iccid);
        fprintf(fd, endbuf);
    }

    fclose(fd);
    printf("OK\n");
}

void Test()
{
    fileOp();
}

int main()
{
    Test();
}