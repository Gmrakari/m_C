
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#define WS_URL            "ws://iot.com"

int gen_url(char **out_url, int *out_url_len)
{
    int err = 0;
    char uuid[] = "123456";
    char sign_method[] = "HmacSHA1";
    char sign[] = "1234567";

    char ts_str[16] = {0};
    time_t ts = time(NULL);

    snprintf(ts_str, sizeof(ts_str), "%ld", ts);

    printf("ts_str:%s\r\n", ts_str);
    printf("ts:%ld\r\n", ts);
    printf("ts second:%ld\r\n", ts * 1000);

    int url_len = strlen(WS_URL) + 1             // ?
                 + strlen("uuid=") + strlen(uuid) + 1              // &
                 + strlen("timestamp=") + strlen(ts_str) + 1       // &
                 + strlen("signMethod=") + strlen(sign_method) + 1 // &
                 + strlen("sign=") + strlen(sign) + 1;             // null

    printf("[%s][%d]url_len: %d\r\n", __func__, __LINE__, url_len);

    char *url = malloc(sizeof(char) * url_len);
    if (!url) {
        err = -1;
        return err;
    }
    memset(url, 0x00, url_len);

    int len = sprintf(url, "ws://iot.com/ws/v1/access?uuid=%s&timestamp=%s&signMethod=%s&sign=%s", uuid, ts_str, sign_method, sign);
    // len = len - 
    printf("url:%s\r\n", url);
    printf("[%s][%d]len: %d\r\n", __func__, __LINE__, len);
    if (len != url_len - 1) {
        printf("[%s][%d]sprintf gen url err!\r\n", __func__, __LINE__);
        free(url);
        url = NULL;
        err = -1;
        return err;
    }

    printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("request url:%s\r\n", url);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    *out_url = url;
    *out_url_len = strlen(url);

    return 0;
}

static int _test_01()
{
    char *url = NULL;
    int url_len = 0;

    for (int i = 0; i < 3; i++) {
        int err = gen_url(&url, &url_len);
        if (err != 0) {
            printf("gen_url err!\r\n");
        }

        if (url) {
            free(url);
            url = NULL;
        }
    }
}

int main() 
{
    _test_01();

    return 0;
}
