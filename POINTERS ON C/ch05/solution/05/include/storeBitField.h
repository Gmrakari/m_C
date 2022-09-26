#ifndef _STOREBITFIELD_H_
#define _STOREBITFIELD_H_

#include <stdio.h>

int store_bit_field(int original_value, int value_to_store, unsigned starting_bit, unsigned ending_bit);

void test();

#endif // _STOREBITFIELD_H_
