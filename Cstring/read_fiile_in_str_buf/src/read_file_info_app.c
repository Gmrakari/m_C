#include <stdio.h>
#include "read_file_info_app.h"
#include "read_file.h"

int read_file_info_app() {
    printf("[%s]\r\n", __func__);

    const char path[] = "/www";
    read_file(path);

    return 0;
}