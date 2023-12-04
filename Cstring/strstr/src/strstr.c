#include <string.h>
#include <stdlib.h>

#include "strstr.h"

char *m_strstr(const char *src, const char *match_src) {
    if (!src || !match_src || (*src == '\0' && *match_src == '\0')) return NULL;

    if (*match_src == '\0') return (char*)src;

    while (*src) {
        const char *h_src = src;
        const char *n_match_src = match_src;

        while (*h_src && *n_match_src && (*h_src == *n_match_src)) {
            h_src++;
            n_match_src++;
        }

        if (*n_match_src == '\0') return (char*)src;

        src++;
    }

    return NULL;
}

void strstr_func(void) {
    printf("[%s][%d]\r\n", __func__, __LINE__);


    char *str = "abcdef";

    char *res = strstr(str, "de");
    if (res == NULL)
        return ;

    size_t len = res - str + 2;
    printf("len:%d\r\n", len);

    char *dest = strstr(str, "de");
    if (dest == NULL) return ;

    size_t dest_len = dest - str + 2;
    printf("dest_len:%d\r\n", dest_len);

    // char *data = malloc(256);
    // if (data == NULL) { return ;}

    // memcpy(data, str + len, len);

    // printf("data:%s\r\n", data);

    // if (!data) {
    //     free(data);
    //     data = NULL;
    // }

}

