
#include <stdio.h>
#include <string.h>
#include "sscanf_app.h"

int sscanf_app(void) {
    printf("[%d][%s]\r\n", __LINE__, __func__);
    char data[] = "Gmrakari 110 man";
    char name[16] = {0};
    int num = 0;
    char sex[8] = {0};

    int res = sscanf(data, "%s %d %s", name, &num, sex);
    if (res == 3) {
        printf("name:%s, num:%d, sex:%s\r\n", name, num, sex);
    } else {
        printf("fail to parse\r\n");
    }
    return 0;
}
