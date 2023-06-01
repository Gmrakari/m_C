#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_SIZE  20

typedef struct {
    char *str;
    char *dst;
    char *status;
} recv_data_t;

static recv_data_t *header = NULL;

void test_stcmp()
{

    header = (recv_data_t*)malloc(sizeof(char) * sizeof(recv_data_t));
    if (header == NULL) return ;

    header->str = malloc(sizeof(char) * LEN_SIZE);
    if (header->str == NULL) return ;
    strncpy(header->str, "server", strlen("server"));

    header->dst = malloc(sizeof(char) * LEN_SIZE);
    if (header->dst == NULL) return ;
    strncpy(header->dst, "123", strlen("123"));

    header->status = malloc(sizeof(char) * LEN_SIZE);
    if (header->status == NULL) return ;
    strncpy(header->status, "err", strlen("err"));

    if (!strcmp(header->str, "server") && (!strcmp(header->status, "ok") || !strcmp(header->status, "err"))) {
        printf("exit\r\n");
    } else {
        printf("handle\r\n");
    }

    free(header);
    free(header->str);
    free(header->dst);
    free(header->status);
    return ;
}

int main()
{
    test_stcmp();
}


