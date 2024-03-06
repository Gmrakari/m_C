#include <stdio.h>
#include <stdlib.h>

#include "./utils/http/include/http.h"
#include "./utils/http/include/http_req.h"

int main() {
DEBUG_MSG();
    const char url[] = "http://192.168.80.2:9006/xxx.jpg";
    int ret = 0;
    ret = http_get(url);DEBUG_MSG();
    if (ret != 0) {DEBUG_MSG();
        printf("http get err: %d\r\n", ret);
        return ret;
    }DEBUG_MSG();
    printf("http get succeeful%d\r\n", ret);
DEBUG_MSG();
    return ret;
}