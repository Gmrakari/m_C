#include <stdio.h>

int main() {
    // 千位数组
    int arr_thouds[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // 百位数组
    int arr_hunred[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // 十位数组
    int arr_ten0[] = {9, 0, 1, 5};
    int arr_ten1[] = {1, 2, 6, 0};
    int arr_ten2[] = {1, 2, 3, 7};
    int arr_ten3[] = {2, 3, 4, 8};
    int arr_ten4[] = {3, 4, 5, 9};
    int arr_ten5[] = {4, 5, 6, 0};
    int arr_ten6[] = {5, 6, 7, 1};
    int arr_ten7[] = {6, 7, 8, 2};
    int arr_ten8[] = {7, 8, 9, 3};
    int arr_ten9[] = {8, 9, 0, 4};
    int *arr_tens[] = {arr_ten0, arr_ten1, arr_ten2, arr_ten3, arr_ten4, arr_ten5, arr_ten6, arr_ten7, arr_ten8, arr_ten9};

    // 各个位数数组
    int arr_num0[] = {2, 3, 4, 6, 7, 8};
    int arr_num1[] = {3, 4, 5, 7, 8, 9};
    int arr_num2[] = {0, 4, 5, 6, 8, 9};
    int arr_num3[] = {0, 1, 5, 6, 7, 9};
    int arr_num4[] = {0, 1, 2, 6, 7, 8};
    int arr_num5[] = {1, 2, 3, 9, 8, 7};
    int arr_num6[] = {0, 2, 3, 4, 8, 9};
    int arr_num7[] = {0, 1, 3, 4, 5, 9};
    int arr_num8[] = {0, 1, 2, 4, 5, 6};
    int arr_num9[] = {1, 2, 3, 5, 6, 7};
    int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5, arr_num6, arr_num7, arr_num8, arr_num9};

    // 组合输出的计数器
    int combination_count = 0;

    int thouds_size = sizeof(arr_thouds) / sizeof(arr_thouds[0]);
    int hunred_size = sizeof(arr_hunred) / sizeof(arr_hunred[0]);
    int ten_size = sizeof(arr_ten0) / sizeof(arr_ten0[0]);
    int num_size = sizeof(arr_num0) / sizeof(arr_num0[0]);

    // 打开文件以写入
    FILE *file = fopen("b.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // 如果文件打开失败，返回错误
    }

    int *num = NULL;
    int *ten = NULL;

    // 遍历千位、百位、十位和个位数组，生成所有组合
    for (int i = 0; i < thouds_size; i++) { // 千位
        for (int j = 0; j < hunred_size; j++) { // 百位
            // 根据 hunred 选择十位数组
            ten = arr_tens[j];
            // 根据 thouds 选择个位数组
            num = arr_nums[i];

            for (int k = 0; k < ten_size; k++) { // 遍历选择的十位数组
                for (int l = 0; l < num_size; l++) { // 遍历选择的个位数组
                    // 格式化输出
                    if (j == hunred_size - 1 && k == ten_size - 1 && l == num_size - 1) {
                        fprintf(file, "%d%d%d%d", arr_thouds[i], arr_hunred[j], ten[k], num[l]);
                    } else {
                        fprintf(file, "%d%d%d%d,", arr_thouds[i], arr_hunred[j], ten[k], num[l]);
                    }
                    combination_count++;
                }
            }
        }

        // 在每一个千位遍历结束时换行
        if (i != thouds_size - 1)
            fprintf(file, "\n");
    }

    // 关闭文件
    fclose(file);

    printf("Total combinations: %d\n", combination_count); // 输出组合总数

    return 0;
}
