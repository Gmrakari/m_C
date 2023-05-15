/*
 * Date:15 May 2023 11:03 PM
 * Filename:_p2p.h
*/

#ifndef _P2P_H
#define _P2P_H

#include <bits/types.h>

typedef enum {
    GMRAKRI_PTR_TYPE_NORMAL = 0,
} gmrakri_ptr_type_t;

typedef struct {
    uint8_t is_init : 1;
    void *private;
    int (*init)(void);
    void (*deinit)(void);
    void (*lock)(void);
    void (*unlock)(void);
    void (*control)(int cmd, ...);
    void (*func)(void);
} gmrakri_ptr_t;

extern gmrakri_ptr_t gm_ptr;
extern int GMRAKRI_PTR_TYPE_NORMAL_INIT(gmrakri_ptr_t *ptr);

#define GMRAKRI_PTR_CHOOSE(type) ({\
    type##_INIT(&gm_ptr);\
})

#endif // _P2P_H
