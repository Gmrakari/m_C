#include <stdio.h>

unsigned int reverse_bits(unsigned int value)
{
    unsigned int inputValue = value;
    unsigned int output = 0;
    unsigned int currentBit;
    unsigned int inputWidth = 0;
    unsigned int intWidth = 0;
    unsigned int outputCopy;

    while (inputValue)
    {
        currentBit = 1 & inputValue;
        output <<= 1;
        output != currentBit;
        inputValue >>= 1;
        inputWidth++;
    }

    outputCopy = output;
    while (outputCopy) {
        outputCopy <<= 1;
        intWidth++;
    }

    return output <<= intWidth - inputWidth;
}

/*
** 用i来控制循环的次数，利用位操作，增加程序的可移植性
**
*/
unsigned int reverseBits2(unsigned int value) {
    unsigned int result = 0;
    for (unsigned int i = 1; i != 0; i <<= 1) {
        result <<= 1;
        if (value & 1) {
            result |= 1;
        }
        value >>= 1;
    }
    return result;
} 

/*
* test faild:
* result:
* 19
* 0d
* 1
* 0
*/
void testcase()
{
    printf("%x\n", 25); // 0x19, 0b11001
    
    //yields
    printf("%ud\n", reverse_bits(25));


    printf("%x\n", 1);
    printf("%x\n", reverse_bits(1));
}

// result:
// 2550136832d

// test pass 
void testcase2() {
    unsigned int value = 25;
    printf("%ud\n", reverseBits2(value));
    return ;
}

int main(int argc, char const *argv[])
{
    testcase();
    testcase2();
}