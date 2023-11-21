#include "../include/clib_imp.h"
#include "../include/clib.h"
#include <pthread.h>
#include <semaphore.h>

#include <stdint.h> // uint8_t uint16_t...
#include <stdio.h>
#include <stdarg.h> // va_list va_start va_end

typedef struct {
    sem_t lock;
} c_lib_private_t;

static c_lib_private_t private;
static c_lib_t *me;

static err_type_t _c_lib_memcpy_init(void)
{
    err_type_t err = OK;
    printf("[%s][%d]\r\n", __func__, __LINE__);
 
    c_lib_t *c_lib = (c_lib_t*)me;

    if (c_lib->is_init) {
        err = RE_INIT_ERR;
        return err;
    }

    /* Init Lock*/
    c_lib->private = &private;
    if ((err = sem_init(&private.lock, 0, 1)) == -1) {
        err = RET_ERR;
        return err;
    } 

    return err;
}

static err_type_t _c_lib_memcpy_deinit(void)
{
    err_type_t err = OK;
    printf("[%s][%d]\r\n", __func__, __LINE__);


    sem_destroy(&private.lock);

    return err;
}

/*
** 注意：
** 内存拷贝不安全，会出现内存重叠的情况
** 
*/
static void _c_lib_memcpy_nonsafe(void *dest, void const *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) return ;
    uint8_t *origin_str = (uint8_t *)src;
    uint8_t *dest_str = (uint8_t *)dest;

    while (n--) {
        *dest_str++ = *origin_str++;
    }

    return ;
}

static void _c_lib_memcpy_safe(void *dest, void const *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) return ;
    uint32_t nchunks = n / sizeof(dest);  // 按照CPU位宽拷贝

    printf("cpu bits size:%d\r\n", nchunks);

    uint32_t slice = n % sizeof(dest);  // 剩余的按字节拷贝

    printf("lefe slice:%d\r\n", slice);

    unsigned long *s = (unsigned long *)src;
    unsigned long *d = (unsigned long *)dest;

    while (nchunks--) {
        *d++ = *s++;
    }

    while (slice--) {
        *((uint8_t*)d++) = *((uint8_t*)s++);
    }

    return ;
}

static void _c_lib_memcpy_mem_non_overlap(void *dest, void const *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) return ;

    uint8_t *d = NULL;
    const uint8_t *s = NULL;

    if (((uint32_t)dest > ((uint32_t)src + n)) || (dest < src)) {
        d = (uint8_t*)dest;
        s = (const uint8_t*)src;
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d = (uint8_t*)((uint32_t)dest + n - 1); // 从末端开始
        s = (const uint8_t*)((uint32_t)src + n - 1);

        while(n--) {
            *d-- = *s--;
        }
    }

    return ;
}

static void _c_lib_memcpy_mem_non_overlap_fast(void *dest, void const *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) return ;
    printf("[%s][%d]\r\n", __func__, __LINE__);
    uint32_t bytelen = n / sizeof(dest);
    uint32_t slice = n % sizeof(dest);


    uint32_t *d = (uint32_t*)dest;
    uint32_t *s = (const uint32_t*)src;

    printf("bytelen:%d, slice:%d\r\n", bytelen, slice);

    if (((uint32_t)dest > ((uint32_t)src + n)) || (dest < src)) {
        while (bytelen--)
            *d++ = *s++;

        while (slice--) 
            *(uint8_t*)d++ = *(uint8_t*)s++;

        uint16_t *p = (uint16_t)d;
        printf("%02X\r\n", p);
        printf("%02hn\r\n", p);
    } else {
        d = (uint8_t*)((uint32_t)dest + n - 4);
        s = (const uint8_t*)((const uint32_t*)src + n - 4);
        while (bytelen--) {
            printf("1 *d:%02X, *s:%02X", *d, *s);
            *d-- = *s--;
            printf("2 *d:%02X, *s:%02X", *d, *s);
        }
        d++;s++;
        uint8_t *d1 = (uint8_t*)d;
        const uint8_t *s1 = (const uint8_t*)s;
        d1--;s1--;
        while (slice--)
            *(uint8_t*)d1-- = *(uint8_t*)s1--;
    }

    return ;
}

static void _c_lib_memcpy_net(void *dest, void const *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) return ;

    uint32_t cpu_width = sizeof(void *);
    printf("cpu width:%d\r\n", cpu_width);

    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t*)src;

    // 如果目标在源之前且没有内存重叠
    if ((size_t)d < (size_t)s || (size_t)d >= (size_t)(s + n)) {
        // 按照 CPU 位宽进行内存拷贝
        while (n >= cpu_width) {
            *(size_t *)d = *(size_t *)s;
            d += cpu_width;
            s += cpu_width;
            n -= cpu_width;
        }
    }

    // 拷贝剩余字节，从前往后或者从后往前
    while (n > 0) {
        if ((size_t) d < (size_t)s || (size_t)d >= (size_t)(s + n)) {
            *d++ = *s++;
        } else {
            d += n - 1;
            s += n - 1;
            *d-- = *s--;
            break;
        }
        n--;
    }

    return ;
}

static err_type_t _c_lib_memcpy_lock(void)
{
    err_type_t err = OK;
    c_lib_t *c_lib = (c_lib_t *)me;
    c_lib_private_t *private = (c_lib_private_t *)c_lib->private;

    if (!c_lib->is_init) {
        err = UN_INIT_ERR;
        return err;
    }

    sem_post(&private->lock);

    return err;
}

static err_type_t _c_lib_memcpy_unlock(void)
{
    err_type_t err = OK;
    c_lib_t *c_lib = (c_lib_t *)me;
    c_lib_private_t *private = (c_lib_private_t *)c_lib->private;

    if (!c_lib->is_init) {
        err = UN_INIT_ERR;
        return err;
    }

    sem_wait(&private->lock);

    return err;
}

static err_type_t _c_lib_memcpy_control(uint32_t cmd, ...)
{
   err_type_t err = OK;
    c_lib_t *c_lib = (c_lib_t *)me;
    c_lib_private_t *private = (c_lib_private_t *)c_lib->private;

    if (!c_lib->is_init) {
        err = UN_INIT_ERR;
        return err;
    }

    (void)private;

    /* Control */
    va_list ap;
    va_start(ap, cmd);
    switch(cmd) {
        default:
            break;
    }
    va_end(ap);

   return err;
}

err_type_t C_LIB_TYPE_NORMAL_INIT(c_lib_t *c_lib)
{
   printf("[%s][%d]\r\n", __func__, __LINE__);
   err_type_t err = OK;
   c_lib->init = _c_lib_memcpy_init;
   c_lib->memcpy_nonsafe = _c_lib_memcpy_nonsafe;
   c_lib->memcpy_safe = _c_lib_memcpy_safe;
   c_lib->memcpy_mem_non_overlap = _c_lib_memcpy_mem_non_overlap;
   c_lib->memcpy_mem_non_overlap_fast = _c_lib_memcpy_mem_non_overlap_fast;
   c_lib->memcpy_net = _c_lib_memcpy_net;
   c_lib->lock = _c_lib_memcpy_lock;
   c_lib->unlock = _c_lib_memcpy_unlock;
   c_lib->deinit = _c_lib_memcpy_deinit;
   c_lib->control = _c_lib_memcpy_control;
   me = c_lib;

   return err;
}
