#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t data = 0x12345678;
    uint8_t *ptr = (uint8_t*)&data;

    if (ptr[0] == 0x78) {
        printf("litter ending\r\n");
        return 0;
    } 

    printf("big ending\r\n");
    return 0;
}