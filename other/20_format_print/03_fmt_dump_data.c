#include <stdio.h>
#include <string.h>
#include <ctype.h> // isprint

#define BYTES_PER_LINE                                          (16)

static void _dump_data(const unsigned char *data, unsigned int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return ;
    }

    printf("dump data:\r\n");

    unsigned char buf[BYTES_PER_LINE + 1] = {0};
    unsigned int i;

    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
        buf[i % BYTES_PER_LINE] = isprint(data[i]) ? data[i] : '.';

        if ((i + 1) % BYTES_PER_LINE == 0) {
            buf[BYTES_PER_LINE] = '\0';
            printf("| %s\n", buf);
        }
    }

    if (i % BYTES_PER_LINE != 0) {
        for (unsigned int j = i % BYTES_PER_LINE; j < BYTES_PER_LINE; j++) {
            printf("   ");
        }
        buf[i % BYTES_PER_LINE] = '\0';
        printf("| %s\r\n", buf);
    }

    return ;
}

int main()
{
    const char *str = "";

    _dump_data(str, strlen(str));

    return 0;
}
