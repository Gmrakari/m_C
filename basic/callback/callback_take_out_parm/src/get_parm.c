/**
 * 
 * @filename:get_parm.c
 * @function:
 * @return:
 * @author:Zhanyou Zhou (gmrakari@outlook.com)
 * @date:2023/1/31 23:31
 * 
 */

#include "cb_headers.h"

void _print(void) {
    printf("_print\r\n");
}

void get_param_fun() {
    printf("[%s][%d]\r\n", __func__, __LINE__);

    my_callback_fun_register(_print);
    printf("[%s][%d]\r\n", __func__, __LINE__);

}
