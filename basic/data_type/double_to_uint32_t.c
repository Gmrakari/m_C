#include <stdio.h>
#include <stdint.h>

int main() {
    double double_value = 1234.5678;
    uint32_t uint_value = (uint32_t)double_value;
    
    printf("Double value: %.4f\n", double_value);
    printf("Converted uint32_t value: %u\n", uint_value);

    int ret = 0;

    int value = 1;

    ret |= value;

    printf("ret:%d\r\n", ret);
    
    return 0;
}