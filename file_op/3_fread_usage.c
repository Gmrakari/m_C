#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void test_01()
{
    char filepath[] = "3_fread_usage_demo.txt";
    char buffer[2];

    buffer[0] = 'a';
    buffer[1] = 'b';

    FILE *fp;

    fp = fopen(filepath, "wb+");
    if (!fp) {
        printf("fopen %s err!\r\n", filepath);
        return ;
    }

    int ret = 0;
    ret = fwrite(buffer, 1, sizeof(buffer), fp);
    printf("fwrite ret:%d\r\n", ret);

    // 将文件指针移动到文件的开头
    fseek(fp, 0, SEEK_SET);

    char read_buf[3] = {0};

    ret = fread(read_buf, 1, sizeof(read_buf), fp);
    printf("fread ret:%d\r\n", ret);
    printf("read_buf:%s\r\n", read_buf);

    fclose(fp);

    return ;
}

int main(int argc, int *argv[])
{
    test_01();
}