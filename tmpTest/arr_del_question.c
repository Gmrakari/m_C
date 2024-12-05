#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int arr_num[1000] = {0};

static int _print_arr_elem(const int *arr, int len)
{
    if (!arr || !len)
        return -1;
    int rc = 0;

    const int *p = arr;
    for (int i = 0; i < len; i++){
        printf("%d", p[i]);
        if (i != len - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    return rc;
}

static int _remove_arr_elem(const int *src, int src_len, const int *dst, int dst_len, int **out, int *olen)
{
    if (!src || !src_len || !dst || !dst_len)
        return -1;
    
    _print_arr_elem(dst, dst_len);
    
    int tmp[1000] = {0};
    int tmp_idx = 0;
    // for (int i = 0; i < src_len; i++) {
        for (int j = 0; j < dst_len; j++) {
            for (int i = 0; i < src_len; i++) {
                if (src[i] != dst[j]) {
                    tmp[tmp_idx++] = src[i];
                    break;
                }
            }
        }
    // }

    int *out_arr = malloc(sizeof(int) * tmp_idx);
    if (!out_arr)
        return -1;

    memcpy(out_arr, tmp, sizeof(int) * tmp_idx);

    for (int i = 0; i < tmp_idx; i++) {
        printf("%d", tmp[i]);
        if (i != tmp_idx)
            printf(" ");
    }
    printf("\r\n");

    *out = out_arr;
    *olen = tmp_idx;

    return 0;
}



int main() {
    int input_num = 0;

    // scanf("%d", &input_num);

    input_num = 4;

    if (!input_num)
        return 0;
    
    if (input_num == 1)
        return input_num;

    int arr_num_idx = 0;
    for (int i = 0; i < input_num; i++) {
        arr_num[arr_num_idx++] = i;
    }

    _print_arr_elem(arr_num, arr_num_idx);

    int arr_num_len = input_num;
    int *ptr_arr = NULL;
    int ptr_arr_len = 0;
    int tmp[1000] = {0};
    int tmp_idx = 0;
    while (arr_num_len > 4) {
        tmp_idx = 0;
        for (int i = 0; i < arr_num_len; i++) {
            if (i != 0 && i % 3 == 0) {
                tmp[tmp_idx++] = arr_num[i];
            }
        }printf("[%s][%d]\r\n", __func__, __LINE__);

        _print_arr_elem(tmp, tmp_idx);

        _remove_arr_elem(arr_num, arr_num_len, tmp, tmp_idx, &ptr_arr, &ptr_arr_len);printf("[%s][%d]\r\n", __func__, __LINE__);

        arr_num_len = ptr_arr_len;printf("[%s][%d]\r\n", __func__, __LINE__);

        memset(arr_num, 0x00, sizeof(int) * sizeof(arr_num));printf("[%s][%d]\r\n", __func__, __LINE__);

        if (ptr_arr) {
            memcpy(arr_num, ptr_arr, sizeof(int) * ptr_arr_len);printf("[%s][%d]\r\n", __func__, __LINE__);
            free(ptr_arr);printf("[%s][%d]\r\n", __func__, __LINE__);
            ptr_arr = NULL;printf("[%s][%d]\r\n", __func__, __LINE__);
        }

        if (arr_num_len == 4) {printf("[%s][%d]\r\n", __func__, __LINE__);
            printf("arr_num:%d", arr_num[2]);
            break;
        }
    }

    return 0;
}
