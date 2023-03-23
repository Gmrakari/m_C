#include "binary_op.h"

#define USE_READ_BITS_TEST 0
#define USE_SET_BITS_TEST 0
#define USE_CLEAR_BITS_TEST 0
#define USE_CHECK_IS_POWER_TEST 1


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

static void _clear_bit_test(unsigned int reg, bin_op_t *bin_op)
{
    printf("origin data:\r\n");
    bin_op->print(&reg);

    printf("clear 0 bits data:");
    bin_op->clear_bits(&reg, 0);
    bin_op->print(&reg);
    printf("\r\n");
    printf("clear 1 bits data:");
    bin_op->clear_bits(&reg, 1);
    bin_op->print(&reg);
    printf("\r\n");
    printf("clear 2 bits data:");
    bin_op->clear_bits(&reg, 2);
    bin_op->print(&reg);
}

static void _check_is_power(unsigned int *number, size_t len, bin_op_t *bin_op)
{
    int ret = -1;
    for (int i = 0; i < len; i++) {
        if (!(ret = bin_op->check_is_power2(number[i]))) 
            printf("%d is power 2\r\n", number[i]);
    }

    return ;
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

#if USE_CLEAR_BITS_TEST
    // unsigned int reg = 0x12345678;
    unsigned int reg = 0x123;
    _clear_bit_test(reg, &bin_op);
#endif

#if USE_CHECK_IS_POWER_TEST
    unsigned int number[2048] = {0};
    for (unsigned int i = 0; i < sizeof(number)/ sizeof(number[0]); i++) {
        number[i] = i;
    }
    _check_is_power(number, sizeof(number)/ sizeof(number[0]), &bin_op);
#endif

    return 0;
}
