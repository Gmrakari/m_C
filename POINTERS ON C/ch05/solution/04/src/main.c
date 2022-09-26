#include "bitfunc.h"
#include "bitfuncCopy.h"

// test failed:
// output:
// 0000 
void test() {
    char str[] = "0000";
    set_bit(str, 1);
    printf("%s\n", str);
    return ;
}

// test successful
// output:
// 2000
// 900000
void testCopy() {
    char str[] = "0000";
    set_bit_2(str, 1);
    printf("%s\n", str);

    char bit_array[] = "100000";
    set_bit_2(bit_array, 3);
    printf("%s\n", bit_array);
    return ;
}

int main(int argc, char const *argv[]) {
    test();
    testCopy();
    return 0;
}
