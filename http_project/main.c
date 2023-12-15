#include <stdio.h>
#include <stdlib.h>

#include "./utils/http/include/http.h"
#include "./utils/http/include/http_req.h"


int main() {

    // const char *url = "http://192.168.80.2:9006/5";
    const char url[] = "http://192.168.80.2:9006/xxx.jpg";
    // char *buf = http_get(url);
    // if (!buf) {
    //     free(buf);
    //     buf = NULL;
    // }

    uint32_t res = http_get(url);

DEBUG_MSG();
    return 0;
}