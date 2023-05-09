#include <stdio.h>
#include <stdint.h> // uint8

void _print_uint8_t_arr(uint8_t *arr, size_t len)
{
    if (arr == NULL) return ;
    for (int i = 0; i < len; i++) {
        printf("data[%d]:%d\t", i, arr[i]);
    }
    printf("\r\n");
}

void _print_int8_t_arr(int8_t *arr, size_t len)
{
    if (arr == NULL) return ;
    for (int i = 0; i < len; i++) {
        printf("data[%d]:%d\t", i, arr[i]);
    }
    printf("\r\n");
}

void _print_uint16_t_arr(uint16_t *arr, size_t len)
{
    if (arr == NULL) return ;
    for (int i = 0; i < len; i++) {
        printf("data[%d]:%d\t", i, arr[i]);
    }
    printf("\r\n");
}

void _print_int16_t_arr(int16_t *arr, size_t len)
{
    if (arr == NULL) return ;
    for (int i = 0; i < len; i++) {
        printf("data[%d]:%d\t", i, arr[i]);
    }
    printf("\r\n");
}

/*
result:
data[0]:254     data[1]:255     data[2]:0       data[3]:1
data[0]:-2      data[1]:-1      data[2]:0       data[3]:1
data[0]:65534   data[1]:65535   data[2]:0       data[3]:1       data[4]:2
data[0]:-2      data[1]:-1      data[2]:0       data[3]:1       data[4]:2
*/
void _tmp_test()
{
    uint8_t u_data[] = {-2, -1, 0, 1};
    size_t u_len = sizeof(u_data) / sizeof(u_data[0]);
    _print_uint8_t_arr(u_data, u_len);

    int8_t data[] = {-2, -1, 0, 1};
    size_t len = sizeof(data) / sizeof(data[0]);
    _print_int8_t_arr(data, len);

    uint16_t u16_data[] = {-2, -1, 0, 1, 2};
    size_t u16_len = sizeof(u16_data) / sizeof(u16_data[0]);
    _print_uint16_t_arr(u16_data, u16_len);

    int16_t _16_data[] = {-2, -1, 0, 1, 2};
    size_t _16_len = sizeof(_16_data) / sizeof(_16_data[0]);
    _print_int16_t_arr(_16_data, _16_len);

    printf("\r\n");
}

int main()
{
    _tmp_test();

    return 0;
}