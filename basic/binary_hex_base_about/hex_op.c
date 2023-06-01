#include <stdio.h>
// #include <bits/types.h>
#include <stdint.h>
void ret(void) {
    uint8_t ori_data = 0x90;

    if (ori_data == 0x91) {
        printf("0x91\r\n");
    }
    else if (ori_data == 0x92) {
        printf("0x92\r\n");
    }
    else {
        printf("0x90\r\n");
    }

}

int main(int argc, char const *argv[]) {
    ret();
}
