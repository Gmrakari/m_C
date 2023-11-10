#include <stdio.h>
#include <stdint.h>

#define USE_TEST_CASE_1 0
#define USE_TEST_CASE_2 0
#define USE_TEST_CASE_3 0
#define USE_TEST_CASE_4 1

#define U32_BITS_SWAP(x) \
    ((((x) & 0x000000FF) << 24) + \
    (((x) & 0x0000FF00) << 8) + \
    (((x) & 0x00FF0000) >> 8) + \
    (((x) & 0xFF000000) >> 24))

uint32_t uint32_bits_swap(uint32_t value) {
    uint32_t res;

    res = ((value & 0x000000FF) << 24)  +
            ((value & 0x0000FF00) << 8)  +
            ((value & 0x00FF0000) >> 8) +
            ((value & 0xFF000000) >> 24);

    return res;
}

static void case_1() {
    uint32_t data = 0x12345678;
    uint8_t *ptr = (uint8_t *)&data;

    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    data = uint32_bits_swap(data);

    ptr = (uint8_t *)&data;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);
}

static void case_2() {
    uint32_t num = 0x1234;
    uint8_t *pchar = (uint8_t *)&num;
    printf("%X %X %X %X\r\n", pchar[0], pchar[1], pchar[2], pchar[3]);

    uint32_t res;
    res = ((num & 0x000000FF) << 24);
    pchar = (uint8_t *)&res;

    printf("%X %X %X %X\r\n", pchar[0], pchar[1], pchar[2], pchar[3]);
}

static void case_3() {
    uint32_t num = 0x12345678;
    uint8_t *ptr = (uint8_t *)&num;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    uint32_t res;
    res = ((num & 0x000000FF) << 24);
    ptr = (uint8_t *)&res;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    num = 0x12345678;
    res = ((num & 0x0000FF00) << 8);
    ptr = (uint8_t *)&res;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    num = 0x12345678;
    res = ((num & 0x00FF0000) >> 8);
    ptr = (uint8_t *)&res;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);


    num = 0x12345678;
    res = ((num & 0xFF000000) >> 24);
    ptr = (uint8_t *)&res;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);
}

static void case_4() {
    uint32_t data = 0x12345678;
    uint8_t *ptr = (uint8_t *)&data;

    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);

    data = U32_BITS_SWAP(data);

    ptr = (uint8_t *)&data;
    printf("%X %X %X %X\r\n", ptr[0], ptr[1], ptr[2], ptr[3]);
}

static void test() {
    #if USE_TEST_CASE_1
        case_1();
    #endif

    #if USE_TEST_CASE_2
        case_2();
    #endif

    #if USE_TEST_CASE_3
        case_3();
    #endif

    #if USE_TEST_CASE_4
        case_4();
    #endif
}

int main() {
    test();
    printf("Hello, World\r\n");
    return 0;
}