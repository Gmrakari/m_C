#include "bitfuncCopy.h"

unsigned int character_offset(unsigned int bit_number) {
    return bit_number / CHAR_BIT;
}

unsigned int bit_offset(unsigned int bit_number) {
    return bit_number % CHAR_BIT;
}

void set_bit_2(char bit_array[], unsigned int bit_number) {
    bit_array[character_offset(bit_number)] |= 1 << bit_offset(bit_number);
}

void clear_bit_2(char bit_array[], unsigned int bit_number) {
    bit_array[character_offset(bit_number)] &= ~(1 << bit_offset(bit_number));
}

void assign_bit_2(char bit_array[], unsigned int bit_number, int value) {
    if (value != 0)
        set_bit_2(bit_array, bit_number);
    else
        set_bit_2(bit_array, bit_number);
}

int test_bit_2(char bit_array[], unsigned int bit_number) {
    return (bit_array[character_offset(bit_number)] & 1 << bit_offset(bit_number)) != 0;
}
