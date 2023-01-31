/**
 * 
 * @filename:take_parm_out.c
 * @function:
 * @return:
 * @author:Zhanyou Zhou (gmrakari@outlook.com)
 * @date:2023/1/31 21:54
 * 
 */

#include "cb_headers.h"

static void (*cb_fun)(void) = NULL;

void my_callback_fun_register(void (*cb)()) {
    cb_fun = cb;
}

void _generate_parm(void) {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    int a = 1, b = 2;
    int c = a + b;

    if (cb_fun) cb_fun();
    printf("[%s][%d]\r\n", __func__, __LINE__);
}
