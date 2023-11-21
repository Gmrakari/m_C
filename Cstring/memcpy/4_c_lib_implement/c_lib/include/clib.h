#ifndef _CLIB_H
#define _CLIB_H

#include <stdint.h>
#include <stddef.h>
#include "err_type.h"

typedef enum {
    C_LIB_TYPE_NORMAL = 0,
} c_lib_type_t;

struct c_lib_t{
    uint8_t is_init : 1;
    void *private;
    err_type_t (*init)(void);
    err_type_t (*deinit)(void);
    void (*memcpy_nonsafe)(void *dest, void const *src, size_t n);
    void (*memcpy_safe)(void *dest, void const *src, size_t n);
    void (*memcpy_mem_non_overlap)(void *dest, void const *src, size_t n);
    void (*memcpy_mem_non_overlap_fast)(void *dest, void const *src, size_t n);
    void (*memcpy_net)(void *dest, void const *src, size_t n);
    err_type_t (*lock)(void);
    err_type_t (*unlock)(void);
    err_type_t (*control)(uint32_t cmd, ...);
};

typedef struct c_lib_t c_lib_t;

extern c_lib_t c_lib;
extern err_type_t C_LIB_TYPE_NORMAL_INIT(c_lib_t *c_lib);

#define C_LIB_CHOOSE(type) ({\
    type##_INIT(&c_lib);\
})

#endif // _M_CLIB_H
