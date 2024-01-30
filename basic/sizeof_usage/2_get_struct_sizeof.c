#include <stdint.h>
#include <stdio.h>

#define MAX_STR_LEN 10
                                     // 成员字节数, 总字节数
typedef struct {
    uint8_t len;                     // 1, 1
    uint16_t index;                  // 2, 3
    uint8_t times;                   // 1, 4
    uint8_t status;                  // 1, 5
    uint8_t use_t[6];                // 6, 11
    uint8_t expiry_t[6];             // 6, 17
    char passwd[MAX_STR_LEN];        // 10, 27 (pad + 3) => 30;与最大的成员最小倍数对齐
    uint8_t cnt;                     // 1, 31
    uint8_t valid;                   // 1, 32
    uint8_t start_h;                 // 1, 33
    uint8_t start_m;                 // 1, 34
    uint8_t end_h;                   // 1, 35
    uint8_t end_m;                   // 1, 36
    uint8_t week;                    // 1, 37
} tmp_passwd_t;

                                     // 成员字节数, 总字节数
typedef struct {
    uint8_t len;                     // 2, 2 pad ?
    uint16_t index;                  // 2, 4
    uint8_t times;                   // 1, 5
    uint8_t status;                  // 1, 6
    uint8_t use_t[6];                // 6, 12
    uint8_t expiry_t[6];             // 6, 18
    char passwd[MAX_STR_LEN];        // 10, 28
    uint8_t cnt;                     // 1, 29
    uint8_t valid;                   // 1, 30
    uint8_t start_h;                 // 1, 31
    uint8_t start_m;                 // 1, 32
    uint8_t end_h;                   // 1, 33
    uint8_t end_m;                   // 1, 34
    uint8_t week;                    // 1, 35
                                     // 1, 36 pad?
} tmp_passwd_t;

int main() {
    tmp_passwd_t tmp_passwd_ins;
    size_t size = sizeof(tmp_passwd_ins);

    // 没有对齐:1 + 2 + 1 + 1 + 6 * 1 + 6 * 1 + 1 * 10 + 1 + 1 + 1 + 1 + 1 + 1 + 1 = 34

    // 输出36
    printf("Size of tmp_passwd_t: %zu bytes\n", size);

    return 0;
}
