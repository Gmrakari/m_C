#include <stdio.h>

#include <stdlib.h> // malloc

void print_arr(const char *arr_name_str, int *arr, int arr_len)
{
    for (int i = 0; i < arr_len; i++) {
        printf("%s[%d]:%d\r\n", arr_name_str, i, arr[i]);
    }
    printf("\r\n");
}

void move_arr() {
    const char src_arr_str[] = "src_arr";
    const char dest_arr_str[] = "dest_arr";

    int src_arr[] = {-1, 2, 0, 4, 5, 3, 0};
    int len = sizeof(src_arr) / sizeof(src_arr[0]);

    print_arr(src_arr_str, src_arr, len);

    int hash_arr[7];
    for (int i = 0; i < len; i++) {
        int num = src_arr[i];
        if (num != 0) {
            hash_arr[num] = 1;
        }
    }

    int dest_arr[7];
    int idx = 0;

    for (int i = 0; i < len; i++) {
        int num = src_arr[i];
        if (hash_arr[num] == 1) {
            dest_arr[idx++] = src_arr[i];
        }
    }

    int fill_len = len - idx;
    while (fill_len > 0) {
        dest_arr[idx++] = 0;
        fill_len--;
    }

    print_arr(dest_arr_str, dest_arr, len);
}

void move_arr_opt() 
{
    const char src_arr_str[] = "src_arr";
    int src_arr[] = {-1, 2, 0, 4, 5, 3, 0};
    int len = sizeof(src_arr) / sizeof(src_arr[0]);
    
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (src_arr[i] != 0) {
            src_arr[idx++] = src_arr[i];
        }
    }

    int fill_len = len - idx;
    while (fill_len > 0) {
        src_arr[idx++] = 0;
        fill_len--;
    }

    print_arr(src_arr_str, src_arr, len);
}

void move_arr_two_pointer_method()
{
    const char src_arr_str[] = "src_arr";
    int src_arr[] = {-1, 2, 0, 4, 5, 3, 0};
    int len = sizeof(src_arr) / sizeof(src_arr[0]);

    int left = 0;
    int right = 0;

    while (right < len) {
        // 找到第一个非零元素
        if (src_arr[right] != 0) {
            // 交换非零元素和左指针对应的元素
            printf("[%d]:%d\r\n", right, src_arr[right]);
            int temp = src_arr[right];
            src_arr[right] = src_arr[left];
            src_arr[left] = temp;
            left++;
            printf("left:%d\r\n", left);
        }
        right++;
        printf("right:%d\r\n", right);
    }
    // print_arr(src_arr_str, src_arr, len);
}

static void _move_arr_test_case()
{
#if 0
    move_arr();
#endif

#if 1
    move_arr_opt();

    move_arr_two_pointer_method();
#endif
}

int main()
{
    _move_arr_test_case();
}