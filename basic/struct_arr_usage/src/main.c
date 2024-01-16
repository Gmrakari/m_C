#include <stdio.h>

#include "struct_in_arr_usage.h"

int main() {
    int ret = 0;
    
    if (0 != (ret = struct_in_arr_usage_func()))
        printf("struct_in_arr_usage_func err\r\n");

    return 0;
}
