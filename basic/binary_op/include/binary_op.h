#ifndef _BINARY_OP_H
#define _BINARY_OP_H

/*
 *
 *
 */
#include <stdio.h>
//#include

typedef struct {
    unsigned int (*read_bits)(int theKbit);
    unsigned int (*set_bits)(unsigned int reg, int theKbit);
    unsigned int (*clear_bits)(unsigned int reg, int theKbit);
    int (*check_is_power2)(int number);
    unsigned int (*reverse_2_bits)(unsigned int number);
} bin_op_t;

int bin_op_init(bin_op_t *dst);

//typedef struct bin_op_t bin_op;

#endif // _BINARY_OP_H
