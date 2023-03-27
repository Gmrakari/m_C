#include "binary_op.h"

bin_op_t bin_op = {0};
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
/**
 * @brief 清除某一位
 *
 * @param reg 操作的地址
 * @param theKbit 设置第K位
 * @return size_t 将theKbit设置为0
 */
unsigned int _clear_bits(unsigned int *reg, int theKbit)
{
    unsigned int ret = 0;
    *reg &= ~(1 << theKbit);
    ret = *reg;
    printf("register val:0x%08x\r\n", ret);
    return ret;
}


/**
 * @brief 判断number是否为2的幂
 *
 * @param number 操作的整数
 * @return -1:不是2的幂，0:2的幂
 */
int _check_is_power2(int number)
{
    int ret = 0;
    // 如果一个整数是2的幂，那么它的二进制表示中只有一位是1，其余位都是0。
    // 如果我们将一个2的幂和它减去1的结果进行按位与运算，得到的结果应该为0
    // 比如8(10):1000(2), 7(10):111(2)
    //   1000
    // & 0111
    // ------
    //   0000
    if ((number & (number - 1)) != 0 || number == 1)
        ret = -1;
    return ret;
}
unsigned int _reverse_2_bits(unsigned int number)
{
    unsigned int ret = 0;
    return ret;
}

void _print(unsigned int *reg)
{
    for (int i = 15; i >= 0; i--)
    {
        printf("%02x", (*reg >> i) & 1);
        if (i != 0) {
            printf(" ");
        }
    }
    printf("\r\n");
}

int bin_op_init(bin_op_t *dst)
{
    dst->read_bits = _read_bits;
    dst->set_bits = _set_bits;
    dst->clear_bits = _clear_bits;
    dst->check_is_power2 = _check_is_power2;
    dst->reverse_2_bits = _reverse_2_bits;
    dst->print = _print;
    me = dst;

    return 0;
}
