#include <stdio.h>
#include "read_file_info_app.h"
#include "read_file.h"

int read_file_info_app() {
    printf("[%s]\r\n", __func__);

    int u32Ret = 0;
    char path[FILE_PATH_MAX_LEN] = {0};
    if (0 != (u32Ret = get_config_file_path(path))) 
        return -1;

    read_file(path);

    return 0;
}