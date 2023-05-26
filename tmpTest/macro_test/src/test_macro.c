#include "test_macro.h"

#include <string.h>
#include <stdio.h>

char *str_func()
{
    static char str[STR_BUF_LEN];

    strncpy(str, "str_func_input", sizeof(str));

    return str;
}

void macro_app() {

    printf("msg:%s\r\n", GET_STR_FUN());
    printf("[%s][%d]\r\n", __func__, __LINE__);

}
