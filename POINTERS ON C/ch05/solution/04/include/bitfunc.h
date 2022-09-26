#ifndef _BITFUNC_H_
#define _BITFUNC_H_

#include <stdio.h>
#include <string.h>

void set_bit(char bit_array[], unsigned int bit_number);
void clear_bit(char bit_array[], unsigned int bit_number);
void assign_bit(char bit_array[], unsigned int bit_number, int value);
int test_bit(char bit_array[], unsigned int bit_number);

#endif // _BITFUNC_H_