#ifndef _ERR_TYPE_H
#define _ERR_TYPE_H

#include <stdint.h>

typedef enum {
    OK = 0,
    TYPE_ERR,
    UN_INIT_ERR,
    RE_INIT_ERR,
    PARAM_ERR,
    UNKNOW_ERR,
    OUT_OF_MEMORY_ERR,
    RET_ERR,
} err_type_t;

#endif
