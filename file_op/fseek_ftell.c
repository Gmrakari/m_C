#include <stdio.h> //fseek
#include <string.h> // strlen

#define DEBUG_OUTPUT 1

#if DEBUG_OUTPUT
#define DEBUG(format, ...) printf("[%s][%d]"format"\r\n", __func__, __LINE__, ##__VA_ARGS__)
#endif

// int fseek (FILE *__stream, long int __off, int __whence);
// __whence:
// SEEK_SET 	/* 文件开头 Seek from beginning of file.  */
// SEEK_CUR 	/* 文件指针当前位置 Seek from current position.  */
// SEEK_END 	/* 文件末尾 Seek from end of file.  */

static void _fseek_ftell_usage()
{
    int ret = 0;
    const char *path = "fseek_ftell_test_file.txt";

    size_t str_len = strlen(path);
    DEBUG("str_len:%d", (int)str_len);

    FILE *fp;
    if (NULL == (fp = fopen(path, "r+"))) {
        DEBUG("open file : %s err!", path);
        return ;
    }

    if (0 != (ret = fseek(fp, 0, SEEK_END))) {
        DEBUG("fseek err!");
    }

    size_t start = 0, end = 0, file_size = 0;
    end = ftell(fp);

    if (0 != (ret = fseek(fp, 0, SEEK_SET))) {
        DEBUG("fseek err!");
    }
    start = ftell(fp);

    file_size = end - start;

    DEBUG("file_size:%d", (int)file_size);

    if (file_size != str_len) {
        DEBUG("cal err");
    }

    DEBUG("cal %d", (int)file_size);
}

static void _test_app()
{
    _fseek_ftell_usage();
}

int main()
{
    _test_app();
}
