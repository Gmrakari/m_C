#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static int _get_file_info(void)
{
    int fd = -1;

    char filepath="../fseek_ftell_test_file.txt";

    fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        printf("[%s][%d]open err!\r\n", __func__, __LINE__);
        return -1;
    }

    struct stat sb;

    if ((fstat(fd, &sb)) == -1) {
        close(fd);
        return -1;
    }

    printf("[%s][%d]sb.st_size: %ld\r\n", __func__, __LINE__, sb.st_size);

    close(fd);  // 关闭文件描述符

    return 0;
}

int main()
{
    int ret = 0;
    ret = _get_file_info();
    if (ret != 0) {
        printf("[%s][%d]_get_file_info err!\r\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}

