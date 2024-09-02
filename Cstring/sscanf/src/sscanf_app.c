
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

    char tmp[] = "{\"ts\":1724925986}";

    long unsigned int val = 0;
    if (sscanf(tmp, "{\"ts\":%ld}", &val) == 1) {
        printf("Extracted ts value: %ld\n", val);
    } else {
        printf("Failed to extract ts value\n");
    }

    return 0;
}
