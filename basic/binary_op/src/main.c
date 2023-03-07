#include "binary_op.h"

#define USE_READ_BITS_TEST 0
#define USE_SET_BITS_TEST 1

void read_bits_test(bin_op_t *bin_op)
{
    bin_op->read_bits(3);
    printf("\r\n");
    bin_op->read_bits(4);
    printf("\r\n");
    bin_op->read_bits(5);
    printf("\r\n");
    bin_op->read_bits(6);
}

void set_bits_test(unsigned int reg, bin_op_t *bin_op)
{
    bin_op->set_bits(reg, 0);
    printf("\r\n");
    bin_op->set_bits(reg, 1);
    printf("\r\n");
    bin_op->set_bits(reg, 2);
}

int main()
{
    bin_op_t bin_op = {0};
    bin_op_init(&bin_op);

#if USE_READ_BITS_TEST
    read_bits_test(&bin_op);
#endif

#if USE_SET_BITS_TEST
    // unsigned int reg = 0x12345678;
    unsigned int reg = 0x10;
    set_bits_test(reg, &bin_op);
#endif

    return 0;
}
