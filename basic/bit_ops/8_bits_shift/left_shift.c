#include <stdio.h>
#include <stdint.h>

#define UARTPINFO_MAGIC_HEAD_NUM     0x9529

static void _uint32_t_test(void *param)
{
    uint32_t *get = (uint32_t *)param;
    printf("get:%d -- %04x\r\n", *get, *get);

    uint8_t ubytes = (uint8_t)*get;

    printf("ubytes:%d -- %02x\r\n", ubytes, ubytes);

    // printf("ubytes:%d -- %02x, ubytes:%d -- %02x, ubytes:%d -- %02x, ubytes:%d -- %02x\r\n", 
    // ubytes, ubytes);

    // printf("ubytes:%d -- %04x, ubytes:%d -- %04x, ubytes:%d -- %04x, ubytes:%d -- %04x\r\n", 
    //         (uint8_t)*ubytes, *ubytes, *(ubytes + 1), *(ubytes + 1), 
    //         *(ubytes + 2), *(ubytes + 2), *(ubytes + 3), *(ubytes + 3));
}

static void _test_02()
{
    uint32_t val = 0;
    val = 1;
    val = val << 1;
    printf("val:%d -- %02x\r\n", val, val);

    val = val << 2;
    printf("val:%d -- %02x\r\n", val, val);

    val = val << 3;
    printf("val:%d -- %02x\r\n", val, val);

    val = val << 4;
    printf("val:%d -- %02x\r\n", val, val);

    val = val << 5;
    printf("val:%d -- %02x\r\n", val, val);

    val = val << 6;
    printf("val:%d -- %02x\r\n", val, val);

}

static int test()
{
    uint32_t val = 1;

    uint32_t hex = UARTPINFO_MAGIC_HEAD_NUM;
    printf("hex:%d -- %04x\r\n", hex, hex);

    _uint32_t_test(&hex);

    return 0;
}

int main()
{
    // test();
    _test_02();
}
