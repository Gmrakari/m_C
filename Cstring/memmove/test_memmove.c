#include <string.h>
#include <stdio.h>

static int url_https_to_http(char *url) {
    if (!url) return -1;

    char *https = strstr(url, "https://");

    if (https) {
        https[4] = '\0';
        memmove(https + 4, https + 5, strlen(https + 5) + 1);
    }

    printf("%s\r\n", https);
    return 0;
}

int main() {

    char url[] = "https://www.baidu.com";
    url_https_to_http(url);

    return 0;
}
