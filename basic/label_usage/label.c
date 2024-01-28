#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_SIZE (5)

static char *ptr = NULL;

int deinit(void);
int init(void);

int init(void)
{
    int ret = 0;
    ptr = malloc(PTR_SIZE);
    if (!ptr) {
        ret = -1;
        goto failed;
    }

    char buf[10] = {0};

    if (PTR_SIZE < sizeof(buf)) {
        printf("size not enough\r\n");
        ret = -1;
        goto failed;
    }
    printf("[%s][%d]ret:%d\r\n", __func__, __LINE__, ret);

    return ret;

failed:
    printf("[%s][%d]\r\n", __func__, __LINE__);
    deinit();
    return ret;
}

int deinit(void)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);
    if (ptr) {printf("[%s][%d]\r\n", __func__, __LINE__);
        free(ptr);
        ptr = NULL;
    }printf("[%s][%d]\r\n", __func__, __LINE__);
    return ret;
}

void test_app()
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    if (0 == (ret = init())) {
        printf("init ok\r\n");
    } else {
        printf("init err\r\n");
    }

    if (0 == (ret = deinit())) {
        printf("deinit ok\r\n");
    } else {
        printf("deinit err\r\n");
    }

    printf("[%s][%d]\r\n", __func__, __LINE__);
}

int main()
{
    test_app();
    return 0;
}