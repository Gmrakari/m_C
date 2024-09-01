#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PROC_SELF_EXE_PATH  "/proc/self/exe"

static int _get_proc_exe_path(unsigned char **outpath, int *outpath_len)
{
    int ret = 0;

    int len = -1;

    char buf[1024] = {0};

    len = readlink(PROC_SELF_EXE_PATH, buf, sizeof(buf) - 1);
    if (len == -1) {
        perror("Error getting executable path");
        return -1;
    }

    buf[len] = '\0';

    *outpath = malloc(len + 1);
    if (!*outpath) {
        printf("[%s][%d]malloc out err!\r\n", __func__, __LINE__);
        return -1;
    }

    memset((char *)*outpath, 0x00, len + 1);

    strncpy((char *)*outpath, buf, len + 1);
    *outpath_len = (int)len;
    
    return 0;
}

static int _test_get_current_exe_app_path(void)
{
    unsigned char *path = NULL;
    int path_len = 0;
    int ret = 0;
    ret = _get_proc_exe_path(&path, &path_len);
    if (ret != 0 || !path) {
        printf("[%s][%d]_get_proc_exe_path err!\r\n", __func__, __LINE__);
        return ret;
    }

    if (path) {
        printf("[%s][%d]path: %s\r\n", __func__, __LINE__, path);
        printf("[%s][%d]path len: %d\r\n", __func__, __LINE__, path_len);
        free(path);
        path = NULL;
    }

    return ret;
}

int main() {

    _test_get_current_exe_app_path();

    return 0;
}
