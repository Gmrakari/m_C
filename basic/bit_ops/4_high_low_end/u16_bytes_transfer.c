#include <stdio.h>
#include <stdint.h>

uint16_t u16BytesSwap_1(uint16_t *value) {
    if (!value) return 0;
    return ((*value & 0xFF) << 8 | (*value & 0xFF00) >> 8);
}

uint16_t u16BytesSwap_2(uint16_t *value) {
    if (!value) return 0;
    return (((*value >> 8) & 0xFF) | ((*value << 8) & 0xFF00));
}

static void printValue(const uint8_t test_num, const char *str_name, uint16_t data) {
    printf("test %d %s\r\n", test_num, str_name == NULL ? NULL : str_name);
    uint8_t *buf = (uint8_t*)&data;
    for (int i = 0; i < sizeof(uint16_t); i++) {
        if (i == 0)
            printf("0x");
        printf("%02X", buf[i]);
    }
    printf("\r\n");
}

int testFunc() {
    uint16_t data[2] = {0x2EAC, 0x2EAC};
    // const char *str_name[6] = {"src:", "dest:"};
    // int num = 0;
    // for (int i = 0; i < 2; i++) {
    //     num++;
    //     for (int j = 0; j < 2; j++) {
    //         // printValue(num, str_name[j], data[j]);
    //         // u16BytesSwap_1(&data[i]);
    //         // printValue(num, str_name[j], data[j]);
    //         // u16BytesSwap_2(&data[i]);
    //     }
    // }

    uint8_t *buf = (uint8_t*)&data[0];

    printf("test 1:%02X%02X\r\n", buf[0], buf[1]);

    data[0] = u16BytesSwap_1(&data[0]);

    buf = (uint8_t*)&data[0];

    printf("%02X%02X\r\n", buf[0], buf[1]);

    printf("\r\n");

    buf = (uint8_t*)&data[1];

    printf("test 2:%02X%02X\r\n", buf[0], buf[1]);

    data[1] = u16BytesSwap_2(&data[1]);

    buf = (uint8_t*)&data[1];

    printf("%02X%02X\r\n", buf[0], buf[1]); 

    return 0;
}

int main() {
    testFunc();
    return 0;
}
