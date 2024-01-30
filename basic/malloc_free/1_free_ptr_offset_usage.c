#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void test() {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};

    uint8_t *ptr = data;

    uint8_t *pptr = malloc(10);
    if (!pptr) return ;

    memcpy(pptr, data, sizeof(data));

    pptr = pptr + 2;

    // ptr = ptr + 1;

    for (int i = 0; i < 3; i++) {
        printf("%02X\r\n", ptr[i]);
    }

    if (pptr) {
        pptr = pptr - 2;
        free(pptr);
        pptr = NULL;
    }
}


int main() {
    test();
}