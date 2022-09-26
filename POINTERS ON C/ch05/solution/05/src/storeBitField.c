#include "storeBitField.h"

int store_bit_field(int original_value, int value_to_store, unsigned starting_bit, unsigned ending_bit) {
    int storeLength = starting_bit - ending_bit + 1; // 需要存储的位数
    unsigned int mask = 0;

    // step 1
    // 先移出掩码中的1，后面多个0
    for (int i = 0; i < storeLength; i++) {
        mask |= 1;
        mask <<= 1;
    }

    // 移出掩码后面剩余的0（上面已经移出1个0，这里少移1个)
    for (int i = 0; i < ending_bit - 1; i++) {
        mask |= 1;
        mask <<= 1;
    }

    // step 2
    original_value &= ~mask;

    // step 3
    value_to_store <<= ending_bit;

    // step 4
    value_to_store &= mask;

    // step 5
    unsigned int result = value_to_store | original_value;
    return result;
}

void test() {
    int storeBit = store_bit_field(0xfffff, 0x123, 13, 9);
    printf("storeBit:%x\n", storeBit);
    
    return ;
}
