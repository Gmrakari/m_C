#include <stdio.h>

#if 0
static void print_hex(const unsigned char *data, unsigned int len)
{
    if (!data || !len) {
        printf("print_hex param is null!\r\n");
        return ;
    }

    printf("output data:\n");

    const unsigned char *pdata = data;
    unsigned int plen = len;

    unsigned char buf[17] = {0};
    int print_idx = 0;
    int total_print = 0;

    int buf_idx = 0;
    int print_cnt = 0;

    for (int i = 0; i < len; i++) {
        printf("%02X", pdata[i]);

        buf[buf_idx++] = pdata[i];

        print_cnt = (len / 16);

        if (i != plen - 1) {
            printf(" ");
        }

        // if (!((i + 1) % 16)) {
        //     printf("\r\n");
        // } 


        if (!((i + 1) & 15)) {
            buf[buf_idx] = '\0';
            printf("|%s", buf);
            printf("\r\n");
            buf_idx = 0;

            total_print++;

            // printf("print_cnt:%d\r\n", print_cnt);
        }

        if (total_print < print_cnt) {

        }
    }
    printf("\r\n");

    return ;
}

int main()
{
    unsigned char data[] = "unlockunlockunlockunlockalarm_unlockreply_batterresidurevnlock";
    unsigned int data_len = sizeof(data) - 1;

    print_hex(data, data_len);

    return 0;
}

#endif

#include <stdio.h>
#include <ctype.h>

static void print_hex(const unsigned char *data, unsigned int len)
{
    if (!data || !len) {
        printf("print_hex param is null!\r\n");
        return;
    }

    printf("output data:\n");

    const unsigned char *pdata = data;
    unsigned int plen = len;

    unsigned char buf[17] = {0};
    int buf_idx = 0;

    for (unsigned int i = 0; i < len; i++) {
        printf("%02X ", pdata[i]);
        buf[buf_idx++] = isprint(pdata[i]) ? pdata[i] : '.';

        if ((i + 1) % 16 == 0) {
            buf[buf_idx] = '\0';
            printf("| %s\n", buf);
            buf_idx = 0;
        }
    }

    if (buf_idx > 0) {
        for (int i = buf_idx; i < 16; i++) {
            printf("   ");
        }
        buf[buf_idx] = '\0';
        printf("| %s\n", buf);
    }

    printf("\n");
}

int main()
{
    unsigned char data[] = "unlockunlockunlockunlockalarm_unlockreply_batterresidureversunlockhijackopen_idoorbeanti_lupdateupdateupdateopen,bunlock";
    unsigned int data_len = sizeof(data) - 1;

    print_hex(data, data_len);

    return 0;
}
