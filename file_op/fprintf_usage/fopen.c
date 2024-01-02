#include <stdio.h>
#include <string.h>

#define FILE_PATH "../res/debug_info.txt"
#define FILE_PATH_MAX_LEN (256)

void fileOp()
{
    int cnt = 3;
    char filepath[FILE_PATH_MAX_LEN] = {0};
    strncpy(filepath, FILE_PATH, sizeof(filepath));
    char *buffer = "\"iccid\":\"898604A4192170153703\"";
    char iccid[21] = {0};
    const char endbuf[] = "\n";
    FILE *fd;

    printf("strlen(buffer):%ld\n", strlen(buffer));
    printf("sizeof(buffer):%ld\n", sizeof(buffer));

    memcpy(iccid, buffer, strlen(buffer));

    if ((fd = fopen(filepath, "ab+")) == NULL)
    {
        perror("failed to open files\n");
        return;
    }

    fprintf(fd, endbuf);
    while (cnt--)
    {
        fprintf(fd, "%s", iccid);
        fprintf(fd, "%s", endbuf);
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