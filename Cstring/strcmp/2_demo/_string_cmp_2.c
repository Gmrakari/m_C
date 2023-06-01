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

static int test_stcmp()
{
    int ret = 0;
    header = (recv_data_t*)malloc(sizeof(char) * sizeof(recv_data_t)); // malloc有个问题,第一个moalloc的大小

// 改进:
// 1.
    header = (recv_data_t*)malloc(sizeof(recv_data_t));
    if (header == NULL) {
        printf("header malloc err!");
        ret = -1;
        return ret;
    }

// 2.
    char str[] = "server";
    size_t len = strlen(str);
    header->str = malloc(sizeof(char) * (len + 1));
    if (header->str == NULL) {
        printf("header->str malloc err!");
        free(header);                        // 检查header->str 如果为空,释放header的内存,否则会出现内存泄露
        header = NULL;
        ret = -1;
        return ret;
    }
    strncpy(header->str, (const char*)str, len);

    char dst[] = "123";
    len = strlen(dst);
    header->dst = malloc(sizeof(char) * (len + 1));
    if (header->dst == NULL) {
        printf("header->dst malloc err!");
        free(header->str);
        free(header);
        ret = -1;
        return ret;
    }        
    strncpy(header->dst, (const char*)dst, len);

    char status[] = "ok";
    len = strlen(status);
    header->status = malloc(sizeof(char) * (len + 1));
    if (header->status == NULL) {
        printf("header->status malloc err!");
        free(header->dst);
        free(header->str);
        free(header);
        ret = -1;
        return ret;
    }
    strncpy(header->status, (const char*)status, len);
    
    if (!strcmp(header->str, "server") && (!strcmp(header->status, "ok") || !strcmp(header->status, "err"))) {
        printf("exit\r\n");
    } else {
        printf("handle\r\n");
    }

    free(header->status);  // 内存释放顺序
    free(header->dst);
    free(header->str);
    free(header);
    return ret;
}

int main()
{
    test_stcmp();
}


