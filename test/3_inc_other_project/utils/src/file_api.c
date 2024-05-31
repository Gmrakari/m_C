#include "file_api.h"

int write_buffer_to_file(const char *filepath, const char *buffer, int len)
{
    if (!filepath || !buffer || !len) {
        printf("[%s][%d]invalid pararm!\r\n", __func__, __LINE__);
        return -1;
    }

    FILE *fp = NULL;
    int ret = 0;
    fp = fopen(filepath, "w");
    if (!fp) {
        printf("[%s][%d] fopen %s err!\r\n", __func__, __LINE__, filepath);
        goto _exit;
    }

    if (fwrite(buffer, 1, len, fp) != len) {
        printf("[%s][%d] fwrite %s err!\r\n", __func__, __LINE__, filepath);
        ret = -1;
        goto _exit;
    }

    if (fclose(fp) != 0) {
        printf("[%s][%d] fclose %s err!\r\n", __func__, __LINE__, filepath);
        ret = -1;
        goto _exit;
    }

    return ret;

_exit:
    if (fp) {
        fclose(fp);
    }

    return ret;
}
