#include "http_get.h"

int main() {
    const char *url = "www.baidu.com";
    char *data = http_get(url);

    if (data) {
        printf("get data:%s\r\n", data);
        free(data);
    }
    return 0;
}