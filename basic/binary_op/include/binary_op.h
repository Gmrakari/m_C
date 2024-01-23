#ifndef _BINARY_OP_H
#define _BINARY_OP_H

#include <stdio.h>

typedef struct {
    unsigned int (*read_bits)(int theKbit);
    unsigned int (*set_bits)(unsigned int reg, int theKbit, int value);
    unsigned int (*clear_bits)(unsigned int *reg, int theKbit);
    int (*check_is_power2)(int number);
    void (*print)(unsigned int *reg);
    unsigned int (*reverse_2_bits)(unsigned int number);
} bin_op_t;

extern bin_op_t bin_op;

int bin_op_init(bin_op_t *dst);

#endif // _BINARY_OP_H
