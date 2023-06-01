#include <stdio.h>
#include "my_memcpy.h"

void *my_memcpy(void *dest, const void *src, size_t n)
{
    if (dest == NULL || src == NULL || n == 0) {
        return NULL;
    }
    char *dest_ch = (char*)dest;
    const char *src_ch = (const char*)src;

    for (size_t i = 0; i < n; i++) {
        dest_ch[i] = src_ch[i];
    }

    return dest;
}
