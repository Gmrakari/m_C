#include <stdio.h>

typedef struct {
    char *param;
    char *bin;
} path_t;

static void _load_path()
{
    char file_param_path[][64] = {
        "/root/local/file_int8.param",
        "/root/local/file_n.param"
    };

    char file_bin_path[][64] = {
        "/root/local/file_int8.bin",
        "/root/local/file_n.bin"
    };

    path_t file_int8 = {
        .param = file_param_path[0],
        .bin = file_bin_path[0]
    };

    path_t file_n = {
        .param = file_param_path[1],
        .bin = file_bin_path[1]   
    };
    
    printf("file_int8.param path:%s\r\n", file_int8.param);
    printf("file_int8.bin path:%s\r\n", file_int8.bin);

    printf("file_n.param path:%s\r\n", file_n.param);
    printf("file_n.bin path:%s\r\n", file_n.bin);
}

int main() {
    _load_path();
}