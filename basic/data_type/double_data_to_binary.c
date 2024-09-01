#include <stdio.h>
#include <stdint.h>

void double_to_binary(double data) {
    uint64_t *ptr = (uint64_t*)&data;
    for (int i = 63; i >= 0; i--) {
        uint64_t bit = (*ptr >> i) & 1;
        printf("%lu", bit);
        if (i % 8 == 0) {
            printf(" "); 
        }
    }
    printf("\n");
}

void u32_to_binary(uint32_t value, unsigned char *output) {
    if (!output) return ;

    for (int i = 15; i >= 0; i--) {
        uint32_t bit = (value >> i) & 1;
        output[15 - i] = bit + '0';
    }
    output[16] = '\0';

    return ;
}

int main() {
    double data = 3.14159f;

    // printf("%f\r\n", data);

    // printf("sizeof(double):%ld\r\n", sizeof(double));

    // unsigned char *ptr = (unsigned char*)&data;

    // for (int i = 0; i < 8; i++) {
    //     printf("%02X ", ptr[i]);
    // }

    // 3.14159
    // 314159 * 10-5 
    // 314159 =>
    // 
    print_binary(data);

    uint32_t num = 314159;

    unsigned char u16_to_binary_str[16] = {0};
    u16_to_binary(num, u16_to_binary_str);

    printf("%s\r\n", u16_to_binary_str);

    printf("\r\n");
}