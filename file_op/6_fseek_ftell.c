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

static int _fseek_ftell_usage(const char *filepath, int *olen)
{
    if (!filepath || !olen)
        return -1;

    int ret = 0;
    const char *path = filepath;

    FILE *fp = NULL;

    if (NULL == (fp = fopen(path, "r+"))) {
        DEBUG("open file : %s err!", path);
        return -1;
    }

    if (0 != (ret = fseek(fp, 0, SEEK_END))) {
        DEBUG("fseek err!");
        return -1;
    }

    size_t start = 0, end = 0, file_size = 0;
    end = ftell(fp);

    if (0 != (ret = fseek(fp, 0, SEEK_SET))) {
        DEBUG("fseek err!");
        return -1;
    }
    start = ftell(fp);

    file_size = end - start;

    DEBUG("file_size:%d", (int)file_size);

    *olen = file_size;

    return ret;
}

static int _fread_len_usage(const char *filepath, int *olen)
{
    if (!filepath || !olen)
        return -1;

    const char *path = "fseek_ftell_test_file.txt";

    FILE *fp;
    if (NULL == (fp = fopen(path, "r"))) {
        DEBUG("open file : %s err!", path);
        return -1;
    }

    int buffer[1024] = {0};

    int read_len = 0;

    read_len = fread(buffer, 1, sizeof(buffer), fp);

    fclose(fp);
    fp = NULL;

    DEBUG("read len: %d", (int)read_len);

    *olen = read_len;

    return 0;
}

static int _func_get_file_len_1(const char *filepath)
{
    if (!filepath)
        return -1;

    int len = 0;
    int rc = -1;

    rc = _fseek_ftell_usage(filepath, &len);
    if (rc != 0)
        DEBUG("_fseek_ftell_usage err");

    DEBUG("olen: %d", len);

    return rc;
}

static int _func_get_file_len_2(const char *filepath)
{
    if (!filepath)
        return -1;

    int len = 0;
    int rc = -1;

    rc = _fread_len_usage(filepath, &len);
    if (rc != 0)
        DEBUG("_fread_len_usage err");

    DEBUG("olen: %d", len);

    return rc;
}

static int _test_func_app(void)
{
    int ret = 0;
    const char filepath[] = "fseek_ftell_test_file.txt";

    DEBUG("test 1");

    ret = _func_get_file_len_1(filepath);

    printf("\r\n");
    DEBUG("test 2");
    ret = _func_get_file_len_2(filepath);

    return ret;
}

int main()
{
    _test_func_app();
}
