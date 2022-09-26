#include "bitfunc.h"

void set_bit(char bit_array[], unsigned int bit_number) {
    int bitArrLen = strlen(bit_array);
    if (bitArrLen < bit_number) {
        bit_array[bitArrLen - bit_number - 1] = '1';
    }
    return ;
}

void clear_bit(char bit_array[], unsigned int bit_number) {
    int bitArrLen = strlen(bit_array);
    if (bitArrLen < bit_number) {
        bit_array[bitArrLen - bit_number - 1] = '0';
    }
    return ;
}

void assign_bit(char bit_array[], unsigned int bit_number, int value) {
    int bitArrLen = strlen(bit_array);
    if (bitArrLen < bit_number && value == 1) {
        bit_array[bitArrLen - bit_number - 1] = '1';
    }

    else if (bitArrLen < bit_number && value == 0) {
        bit_array[bitArrLen - bit_number - 1] = '0';
    }
    
    return ;
}

int test_bit(char bit_array[], unsigned int bit_number) {
    int bitArrLen = strlen(bit_array);
    if (bitArrLen < bit_number) {
        if (bit_array[bit_number] != '0') {
            return 1;
        }
        else {
            return 0;
        }
    }
}
