#include <stdio.h>
#include "gm_base64.h"

static int _test_base64_app()
{
    unsigned char src[] = "abc";

    printf("src: %s\r\n", src);

    size_t en_olen = 0;
    size_t de_olen = 0;
    char *ostr = gm_base64_encode(src, sizeof(src), &en_olen);
    if (ostr) {
        printf("encode: %s\r\n", ostr);

        char *dest = gm_base64_decode(ostr, strlen(ostr), &de_olen);
        
        free(ostr);
        ostr = NULL;
        if (dest) {
            printf("decode: %s\r\n", dest);
            free(dest);
            dest = NULL;
        }
    }

    return 0;
}


int main()
{
    _test_base64_app();
    return 0;
}
