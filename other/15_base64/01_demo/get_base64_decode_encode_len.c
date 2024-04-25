#include <stdio.h>
#include <string.h>

static size_t base64_get_encode_len_1(size_t slen)
{
    size_t n;

    n = slen / 3 + ( slen % 3 != 0 );
    n *= 4;

    return n;
}

size_t base64_get_encode_len_2(size_t slen)
{
    size_t n;

    n = slen >> 1;
    n += slen & 1;
    n = (n << 2) + (n << 1);

    return n;
}

size_t base64_get_encode_len_3(size_t slen)
{
    size_t n;

    n = (slen >> 2) + ((slen % 3 != 0) << 2);
    n <<= 2;
    return n;
}

void test() {
    size_t len = 1280;
    size_t res_1 = 0;
    size_t res_2 = 0;
    size_t res_3 = 0;
    res_1 = base64_get_encode_len_1(len);
    printf("res_1: %ld\r\n", res_1);

    res_2 = base64_get_encode_len_2(len);
    printf("res_2: %ld\r\n", res_1);

    res_3 = base64_get_encode_len_3(len);
    printf("res_3: %ld\r\n", res_1);

}

int main() {
    test();
}
