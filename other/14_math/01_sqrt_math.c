#include <stdio.h>
#include <math.h>
#include <stdint.h>

static int test()
{
    double ret = (sqrt(2556 * 2556 + 1179 * 1179)) / 6.1;
    printf("ret:%.02f\r\n", ret);

    uint8_t size_1 = sizeof(uint8_t);
    printf("sizeof size1: %d\r\n", size_1);

    size_1 = 0xFF;
    printf("size1 value: %d\r\n", size_1);

    char buff[] = "size1 value";
    char buffs[] = "i want to get text to token len";

    // printf(": %d\r\n", size_1);
    
    int8_t size_2 = sizeof(int8_t);
    printf("sizeof size_2: %d\r\n", size_2);
    
    size_2 = 0xFF;
    printf("size_2 value: %d\r\n", size_2);

}

int main()
{
    test();
}