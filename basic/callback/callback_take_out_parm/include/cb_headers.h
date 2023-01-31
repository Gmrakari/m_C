/**
 * 
 * @filename:cb_headers.h
 * @function:
 * @return:
 * @author:Zhanyou Zhou (gmrakari@outlook.com)
 * @date:2023/1/31 21:52
 * 
 */

#ifndef CALLBACK_TAKE_OUT_PARM_CB_HEADERS_H
#define CALLBACK_TAKE_OUT_PARM_CB_HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void my_callback_fun_register(void (*cb)());
void _generate_parm(void);

void _print(void);
void get_param_fun();

#endif //CALLBACK_TAKE_OUT_PARM_CB_HEADERS_H
