#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define M (30)

unsigned char bitArray[M / 8 + 1];

static void setBit(int n)
{
    bitArray[n / 8] |= 1 << (n % 8);
}

static int getBit(int n)
{
    return bitArray[n / 8] & (1 << (n % 8));
}

static int test_1()
{
    return 0;
}

int main() {
    test_1();
    return 0;
}