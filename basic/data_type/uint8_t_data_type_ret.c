#include <stdio.h>
#include <stdint.h> // uint8

uint8_t uint8_data_type_ret_func()
{
    return (uint8_t)-1;
}

int8_t int8_data_type_ret_func()
{
    return (int8_t)0xff;
}


int main() {
    uint8_t ret = uint8_data_type_ret_func();
    printf("ret:%d(%x)\r\n", (int8_t)ret, ret);

    int8_t ret1 = 0xff;//int8_data_type_ret_func();
    printf("ret1:%d(%x)\r\n", ret1, ret1);

    printf("equal: %d\r\n", ret == (int8_t)ret1);

    return 0;
}
