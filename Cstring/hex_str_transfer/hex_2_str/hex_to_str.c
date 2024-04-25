#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static void _test_01(const uint8_t *data, uint16_t len) {
    if (!data || !len) return ;

    int idx = 0;
    char test[17 * 2 + 1] = {0};
    for (int i = 0; i < len; i++) {
        if (data[i] == 0x00)
            continue;
        idx += snprintf(test + idx, sizeof(test) - idx, "%c", data[i]);
    }
    printf("idx:%d\r\n", idx);
    test[idx] = '\0';

    printf("strlen test:%d\r\n", (int)strlen(test));
    printf("test:%s\r\n", test);

    uint8_t *ptr = test;
    for (int i = 0;i < idx; i++) {
        printf("%02X", ptr[i]);
        if (i != idx - 1) {
            printf(" ");
        }
    }
    printf("\r\n");
}

static void _test_() {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x00, 0x00, 0x72,0x6E,0x30,0x31,0x64,0x64,0x39,0x39,0x36,0x44,0x43,0x62,0x43,0x46,0x32,0x42};
    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    uint8_t data1[] = {0x72,0x6E,0x30,0x31,0x64,0x64,0x39,0x39,0x36,0x44,0x43,0x62,0x43,0x46,0x32,0x42};
    uint16_t data_len1 = sizeof(data1) / sizeof(data1[0]);

    uint8_t data2[] = {0x01, 0x02, 0x03, 0x00, 0x00, };
    uint16_t data_len2 = sizeof(data2) / sizeof(data2[0]);

    _test_01(data, data_len);
    // _test_01(data1, data_len1);
    // _test_01(data2, data_len2);

    return ;
}

int main() {
    _test_();
    return 0;    
}
