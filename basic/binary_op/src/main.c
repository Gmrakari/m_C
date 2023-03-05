#include "binary_op.h"


int main()
{
    bin_op_t bin_op = {0};
    bin_op_init(&bin_op);

    bin_op.read_bits(3);
    printf("\r\n");
    bin_op.read_bits(4);
    printf("\r\n");
    bin_op.read_bits(5);
    printf("\r\n");
    bin_op.read_bits(6);

    return 0;
}
