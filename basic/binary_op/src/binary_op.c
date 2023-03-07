#include "binary_op.h"

static bin_op_t *me;

void check_endian(void)
{
    int num = 1;
    char *p = (char*)&num;

    if (*p == 0) {
        printf("the machine is big endian.\r\n");
    } else {
        printf("the machine is litter endian.\r\n");
    }
}

void printBinary(unsigned int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

/*
 * @method:读取某个寄存器的某一位
 * @brief
 * @return
 */
unsigned int _read_bits(int theKbit)
{

    check_endian();
    unsigned int ret = 0;

    printf("[%s][%d]\r\n", __func__, __LINE__);
    unsigned int reg = 0x12345678;
    unsigned int bit = (reg >> theKbit) & 1;

    printBinary(reg);

    printf("theKbit %d, value:%u\r\n", theKbit, bit);

    return ret;
}

/**
 * @brief 设置某一位
 * 
 * @param reg 操作的地址
 * @param theKbit 设置第K位
 * @return size_t 将theKbit设置为1
 */
unsigned int _set_bits(unsigned int reg, int theKbit)
{
    unsigned int ret = 0;
    reg |= (1 << theKbit);
    ret = reg;

    printf("value:0x%08x\r\n", ret);

    return ret;
}
unsigned int _clear_bits(int theKbit)
{
    unsigned int ret = 0;

    return ret;
}

int _check_is_power2(int number)
{
    int ret = 0;
    return ret;
}
unsigned int _reverse_2_bits(unsigned int number)
{
    unsigned int ret = 0;
    return ret;
}

int bin_op_init(bin_op_t *dst)
{
    dst->read_bits = _read_bits;
    dst->set_bits = _set_bits;
    dst->clear_bits = _clear_bits;
    dst->check_is_power2 = _check_is_power2;
    dst->reverse_2_bits = _reverse_2_bits;
    me = dst;

    return 0;
}
