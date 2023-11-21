#include "./c_lib/include/clib.h"
#include "./c_lib/include/clib_imp.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>  // memset
#include <stdlib.h>  // malloc

static uint32_t arr[] = {1, 2, 3, 4, 5};

static uint16_t u16_arr_src[] = {0xFAF0, 0xFBF1, 0xFCF2, 0xFDF3, 0xFEF4, 0xFFFA};

static void _print_arr(const uint8_t *str, const void *arr, size_t len, size_t type)
{
    if (str == NULL || arr == NULL || len == 0 || type == 0) return ;
    printf("%s [%d]\r\n", str, __LINE__);

    const uint8_t *byte_arr = (const uint8_t *)arr;

    for (size_t i = 0; i < len; i++) {
        if (type == sizeof(uint8_t)) {
            printf("%c ", byte_arr[i]);
        } else if (type == sizeof(uint16_t)) {
            // printf("i:%d, %d ", (uint32_t)i, *((const uint16_t *)(byte_arr + i)));
            printf("i:%d, %02X ", (uint32_t)i, *((const uint16_t *)(byte_arr + i)));
            // i += sizeof(uint16_t);
        } else if (type == sizeof(uint32_t)) {
            printf("%d ", *((const uint32_t *)byte_arr + i));
        } else if (type == sizeof(uint64_t)) {
            printf("%ld ", *((const uint64_t *)byte_arr + i));
        } else if (type == sizeof(float)) {
            printf("%f ", *((const float *)byte_arr + i));
        } else if (type == sizeof(double)) {
            printf("%lf ", *((const double *)(byte_arr + i)));
        } else {
            printf("Unsupported element size");
        }

        if (i == len - 1) {
            printf("\r\n");
        }
    }
    printf("\n");
}

static err_type_t _test_memcpy_nonsafe_case()
{
    err_type_t err = OK;
    uint32_t arr_len = sizeof(arr) / sizeof(arr[0]);

    uint32_t *dest_arr = (uint32_t*)malloc(sizeof(uint32_t) * arr_len);
    if (dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;
    }

    const uint8_t begin_str[] = "memcpy_nonsafe test begin";
    _print_arr(begin_str, dest_arr, arr_len, sizeof(dest_arr[0]));

    size_t len = sizeof(uint32_t) * arr_len;
    c_lib.memcpy_nonsafe(dest_arr, arr, len);

    const uint8_t after_str[] = "memcpy_nonsafe test after";
    _print_arr(after_str, dest_arr, arr_len, sizeof(dest_arr[0]));
    
    if (dest_arr) { free(dest_arr); dest_arr = NULL; }

    uint16_t u16_arr_len = sizeof(u16_arr_src) / sizeof(u16_arr_src[0]);

    uint16_t *u16_dest_arr = (uint16_t *)malloc(sizeof(uint16_t) * u16_arr_len);
    if (u16_dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;  
    }

    const uint8_t u16_begin_str[] = "memcpy_nonsafe test u16 begin";
    _print_arr(u16_begin_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    size_t u16_len = sizeof(uint16_t) * u16_arr_len;
    c_lib.memcpy_nonsafe(u16_dest_arr, u16_arr_src, u16_len);

    const uint8_t u16_after_str[] = "memcpy_nonsafe test u16 after";
    _print_arr(u16_after_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    if (u16_dest_arr) { free(u16_dest_arr); u16_dest_arr = NULL; }

    return err;
}

static err_type_t _test_memcpy_safe_case()
{
    err_type_t err = OK;
    uint32_t arr_len = sizeof(arr) / sizeof(arr[0]);

    uint32_t *dest_arr = (uint32_t*)malloc(sizeof(uint32_t) * arr_len);
    if (dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;
    }

    const uint8_t begin_str[] = "memcpy_safe test begin";
    _print_arr(begin_str, dest_arr, arr_len, sizeof(dest_arr[0]));

    size_t len = sizeof(uint32_t) * arr_len;
    c_lib.memcpy_safe(dest_arr, arr, len);

    const uint8_t after_str[] = "memcpy_safe test after";
    _print_arr(after_str, dest_arr, arr_len, sizeof(dest_arr[0]));
    
    if (dest_arr) { free(dest_arr); dest_arr = NULL; }

    uint16_t u16_arr_len = sizeof(u16_arr_src) / sizeof(u16_arr_src[0]);

    uint16_t *u16_dest_arr = (uint16_t *)malloc(sizeof(uint16_t) * u16_arr_len);
    if (u16_dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;  
    }

    const uint8_t u16_begin_str[] = "memcpy_safe test u16 begin";
    _print_arr(u16_begin_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    size_t u16_len = sizeof(uint16_t) * u16_arr_len;
    c_lib.memcpy_safe(u16_dest_arr, u16_arr_src, u16_len);

    const uint8_t u16_after_str[] = "memcpy_safe test u16 after";
    _print_arr(u16_after_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    if (u16_dest_arr) { free(u16_dest_arr); u16_dest_arr = NULL; }

    return err;
}

static err_type_t _test_memcpy_mem_non_overlap_case()
{
    err_type_t err = OK;
    uint32_t arr_len = sizeof(arr) / sizeof(arr[0]);

    uint32_t *dest_arr = (uint32_t*)malloc(sizeof(uint32_t) * arr_len);
    if (dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;
    }

    const uint8_t begin_str[] = "memcpy_mem_non_overlap test begin";
    _print_arr(begin_str, dest_arr, arr_len, sizeof(dest_arr[0]));

    size_t len = sizeof(uint32_t) * arr_len;
    c_lib.memcpy_mem_non_overlap(dest_arr, arr, len);

    const uint8_t after_str[] = "memcpy_mem_non_overlap test after";
    _print_arr(after_str, dest_arr, arr_len, sizeof(dest_arr[0]));
    
    if (dest_arr) { free(dest_arr); dest_arr = NULL; }

    uint16_t u16_arr_len = sizeof(u16_arr_src) / sizeof(u16_arr_src[0]);

    uint16_t *u16_dest_arr = (uint16_t *)malloc(sizeof(uint16_t) * u16_arr_len);
    if (u16_dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;  
    }

    const uint8_t u16_begin_str[] = "memcpy_mem_non_overlap test u16 begin";
    _print_arr(u16_begin_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    size_t u16_len = sizeof(uint16_t) * u16_arr_len;
    c_lib.memcpy_mem_non_overlap(u16_dest_arr, u16_arr_src, u16_len);

    const uint8_t u16_after_str[] = "memcpy_mem_non_overlap test u16 after";
    _print_arr(u16_after_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    if (u16_dest_arr) { free(u16_dest_arr); u16_dest_arr = NULL; }

    return err;
}

static err_type_t _test_memcpy_mem_non_overlap_fast_case()
{
    err_type_t err = OK;
    uint32_t arr_len = sizeof(arr) / sizeof(arr[0]);

    uint32_t *dest_arr = (uint32_t*)malloc(sizeof(uint32_t) * arr_len);
    if (dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;
    }

    const uint8_t begin_str[] = "memcpy_mem_non_overlap_fast test begin";
    _print_arr(begin_str, dest_arr, arr_len, sizeof(dest_arr[0]));

    size_t len = sizeof(uint32_t) * arr_len;
    c_lib.memcpy_mem_non_overlap_fast(dest_arr, arr, len);

    const uint8_t after_str[] = "memcpy_mem_non_overlap_fast test after";
    _print_arr(after_str, dest_arr, arr_len, sizeof(dest_arr[0]));
    
    if (dest_arr) { free(dest_arr); dest_arr = NULL; }

    uint16_t u16_arr_len = sizeof(u16_arr_src) / sizeof(u16_arr_src[0]);

    uint16_t *u16_dest_arr = (uint16_t *)malloc(sizeof(uint16_t) * u16_arr_len);
    if (u16_dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;  
    }

    const uint8_t u16_begin_str[] = "memcpy_mem_non_overlap_fast test u16 begin";
    _print_arr(u16_begin_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    size_t u16_len = sizeof(uint16_t) * u16_arr_len;
    c_lib.memcpy_mem_non_overlap_fast(u16_dest_arr, u16_arr_src, u16_len);

    const uint8_t u16_after_str[] = "memcpy_mem_non_overlap_fast test u16 after";
    _print_arr(u16_after_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    if (u16_dest_arr) { free(u16_dest_arr); u16_dest_arr = NULL; }

    return err;
}

static err_type_t _test_memcpy_net_case()
{
    err_type_t err = OK;
    uint32_t arr_len = sizeof(arr) / sizeof(arr[0]);

    uint32_t *dest_arr = (uint32_t*)malloc(sizeof(uint32_t) * arr_len);
    if (dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;
    }

    const uint8_t begin_str[] = "memcpy_net test begin";
    _print_arr(begin_str, dest_arr, arr_len, sizeof(dest_arr[0]));

    size_t len = sizeof(uint32_t) * arr_len;
    c_lib.memcpy_net(dest_arr, arr, len);

    const uint8_t after_str[] = "memcpy_net test after";
    _print_arr(after_str, dest_arr, arr_len, sizeof(dest_arr[0]));
    
    if (dest_arr) { free(dest_arr); dest_arr = NULL; }

    uint16_t u16_arr_len = sizeof(u16_arr_src) / sizeof(u16_arr_src[0]);

    uint16_t *u16_dest_arr = (uint16_t *)malloc(sizeof(uint16_t) * u16_arr_len);
    if (u16_dest_arr == NULL) {
        err = OUT_OF_MEMORY_ERR;
        return err;  
    }

    const uint8_t u16_begin_str[] = "memcpy_net test u16 begin";
    _print_arr(u16_begin_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    size_t u16_len = sizeof(uint16_t) * u16_arr_len;
    c_lib.memcpy_net(u16_dest_arr, u16_arr_src, u16_len);

    const uint8_t u16_after_str[] = "memcpy_net test u16 after";
    _print_arr(u16_after_str, u16_dest_arr, u16_arr_len, sizeof(u16_dest_arr[0]));

    if (u16_dest_arr) { free(u16_dest_arr); u16_dest_arr = NULL; }

    uint8_t u8_dest_arr[] = "11223344";
    uint32_t u8_dest_arr_len = sizeof(u8_dest_arr) / sizeof(u8_dest_arr[0]);

    const uint8_t u8_begin_str[] = "memcpy_net test u8 begin";
    _print_arr(u8_begin_str, u8_dest_arr, u8_dest_arr_len, sizeof(u8_dest_arr[0]));

    size_t u8_len = sizeof(uint8_t) * u8_dest_arr_len;
    c_lib.memcpy_net(u8_dest_arr + 2, u8_dest_arr,  2);

    const uint8_t u8_after_str[] = "memcpy_net test u8 after";
    _print_arr(u8_after_str, u8_dest_arr, u8_dest_arr_len, sizeof(u8_dest_arr[0]));

    return err;
}

int main()
{
    err_type_t err = OK;
    C_LIB_CHOOSE(C_LIB_TYPE_NORMAL);
    c_lib.init();

    // if (OK != (err = _test_memcpy_nonsafe_case())) {
    //     printf(" _test_memcpy_nonsafe_case err:%d\r\n", err);
    //     return err;
    // }
    
    // if (OK != (err = _test_memcpy_safe_case())) {
    //     printf("_test_memcpy_safe_case err:%d\r\n", err);
    //     return err;
    // }

    // if (OK != (err = _test_memcpy_mem_non_overlap_case())) {
        // printf("_test_memcpy_mem_non_overlap_case err:%d\r\n", err);
        // return err;
    // }

    // if (OK != (err = _test_memcpy_mem_non_overlap_fast_case())) {
    //     printf("_test_memcpy_mem_non_overlap_fast_case err:%d\r\n", err);
    //     return err;
    // }

    if (OK != (err = _test_memcpy_net_case())) {
        printf("_test_memcpy_net_case err:%d\r\n", err);
        return err;
    }

    printf("hello world\r\n");
}