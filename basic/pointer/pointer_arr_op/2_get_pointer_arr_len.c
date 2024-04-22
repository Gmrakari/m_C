#include <stdio.h>

static void _get_pointer_arr_len()
{
    unsigned char arr_1[] = {0xB5,0x00};
    unsigned int arr_1_len = sizeof(arr_1) / sizeof(arr_1[0]);

    unsigned char arr_2[] = {0x84,0x00};
    unsigned int arr_2_len = sizeof(arr_2) / sizeof(arr_2[0]);

    unsigned char arr_3[] = {0x85,0x01};
    unsigned int arr_3_len = sizeof(arr_3) / sizeof(arr_3[0]);

    unsigned char *ptr_arr[] = {arr_1, arr_2, arr_3};
    unsigned int ptr_arr_len = sizeof(ptr_arr) / sizeof(ptr_arr[0]);

    printf("[%s][%d]ptr_arr_len: %d\r\n", __func__, __LINE__, ptr_arr_len);

    return ;
}

int main()
{
    _get_pointer_arr_len();

    return 0;
}
