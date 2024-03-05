#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils_base64/01_base64.h"

// useage:
// make && ./app

#define DEBUG_MODE 1
#if DEBUG_MODE
    #define LOGD(format, ...)   printf("[%s](%d): " format, __func__, __LINE__, ##__VA_ARGS__)
#endif

#define IN_FILENAME "pictures.jpg"
#define OUT_FILENAME "base64.txt"

// 0:jpg转base64成功,-1:jpg转base64失败
static int _jpg_2_base64(unsigned char *in_jpg, size_t in_jpg_size, unsigned char **out_base64_str, size_t *out_len) {
    if (!in_jpg)
        return -1;

    int ret = 0;
    size_t len = 0;
    *out_base64_str = base64_encode(in_jpg, in_jpg_size, &len);
    if (!(*out_base64_str))
        return -1;

    *out_len = len;
    // LOGD("out_len:%ld\r\n", out_len);
    // LOGD("out_base64:%s\r\n", out_base64_str);

    return ret;
}

// 0:base64 str写到文件成功,-1:base64 str写到文件失败
static int _base64_to_file(const char *filename, const unsigned char *base64_str, const size_t base64_len)
{
    if (!filename)
        return -1;

    FILE *fp = NULL;
    int ret = 0;
    fp = fopen(filename, "w");
    if (!fp) {
        LOGD("fopen %s err!\r\n", filename);
        goto _exit;
    }

    if (fwrite(base64_str, 1, base64_len, fp) != base64_len) {
        LOGD("fwrite err!\r\n");
        ret = -1;
        goto _exit;
    }

    if (fclose(fp) != 0) {
        LOGD("fclose err!\r\n");
        ret = -1;
        goto _exit;
    }

_exit:
    return ret;
}

// 0:获取文件到buffer成功,-1:获取文件到buffer失败
static int _get_jpg_file_buffer(const char *filename, unsigned char **out_buf, size_t *out_len)
{
    if (!filename)
        return -1;

    FILE *fp;

    if (NULL == (fp = fopen(filename, "r+")))
        return -1;

    size_t file_end, file_start, file_len;

    fseek(fp, 0, SEEK_END);
    file_end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    file_start = ftell(fp);
    file_len = file_end - file_start;

    int ret = 0;
    size_t jpg_data_len = sizeof(unsigned char) * file_len;
    LOGD("jpg_data_len: %ld\r\n", jpg_data_len);
    unsigned char *jpg_data = malloc(jpg_data_len);
    if (!jpg_data) {
        if (fp) 
            fclose(fp);
        ret = -1;
        return ret;
    }
    memset(jpg_data, 0x00, jpg_data_len);

    size_t read_len = 0;
    while (read_len < jpg_data_len) {
        read_len += fread(jpg_data, 1, jpg_data_len, fp);
    }

    if (fp)
        fclose(fp);
    
    *out_buf = jpg_data;
    *out_len = jpg_data_len;

    return ret;
}

static int test_case()
{
    const char file_path[] = IN_FILENAME;
    int ret = 0;

    unsigned char *jpg_buffer;
    size_t jpg_buffer_len;

    if ((ret = _get_jpg_file_buffer(file_path, &jpg_buffer, &jpg_buffer_len)) != 0) {
        LOGD("_get_jpg_file_buffer err: %d!\r\n", ret);
        goto _exit;
    }

    unsigned char *base64_str = NULL;
    size_t base64_len = 0;
    ret = _jpg_2_base64(jpg_buffer, jpg_buffer_len, &base64_str, &base64_len);
    if (ret != 0) {
        LOGD("_jpg_2_base64 err: %d!\r\n", ret);
        goto _exit;
    }

    char output_file[] = OUT_FILENAME;
    ret = _base64_to_file(output_file, base64_str, base64_len);
    if (ret != 0) {
        LOGD("_base64_to_file err: %d!\r\n", ret);
        goto _exit;
    }

_exit:
    if (jpg_buffer) {
        free(jpg_buffer);
        jpg_buffer = NULL;
    }

    if (base64_str) {
        free(base64_str);
        base64_str = NULL;
    }

    return ret;
}

int main()
{
    int ret = 0;
    LOGD("jpg to base64 start!\r\n");

    if ((ret = test_case()) != 0) {
        LOGD("test_case err: %d!\r\n", ret);
        return ret;
    }

    LOGD("jpg to base64 done!\r\n");

    return 0;
}
