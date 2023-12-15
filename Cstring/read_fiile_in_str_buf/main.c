#include <stdio.h>

#include "./include/read_file_info_app.h"

int main(char *argc, int *argv[]) {
    int u32Ret = 0;
    if (0 != (u32Ret = read_file_info_app()))
        return -1;

    return 0;
}