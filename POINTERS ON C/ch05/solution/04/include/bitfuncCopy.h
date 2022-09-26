#ifndef _BITFUNCCOPY_H_
#define _BITFUNCCOPY_H_

#include <stdio.h>
#include <string.h>
#include <limits.h> // CHAR_BIT = 9
//#define CHAR_BIT 8

unsigned int character_offset(unsigned int bit_number);
unsigned int bit_offset(unsigned int bit_number);
void set_bit_2(char bit_array[], unsigned int bit_number);
void clear_bit_2(char bit_array[], unsigned int bit_number);
void assign_bit_2(char bit_array[], unsigned int bit_number, int value);
int test_bit_2(char bit_array[], unsigned int bit_number);

#endif // _BITFUNCCOPY_H_
