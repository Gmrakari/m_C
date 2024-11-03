#include <stdio.h>

int main() {
    // 千位数组
    // int arr_thouds[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int arr_thouds[] = {0, 1, 5, 6, 4, 7};

    int arr_hunred0[] = {0, 1, 5, 6, 7, 9};
    int arr_hunred1[] = {0, 1, 3, 4, 5, 9};
    int arr_hunred2[] = {0, 1, 2, 4, 5, 6};

    int arr_hunred3[] = {0, 4, 5, 6, 8, 9};
    int arr_hunred4[] = {0, 2, 3, 4, 8, 9};
    int arr_hunred5[] = {0, 1, 3, 4, 5, 9};

    int arr_hunred6[] = {0, 1, 2, 4, 5, 6};
    int arr_hunred7[] = {0, 4, 5, 6, 8, 9};
    int arr_hunred8[] = {0, 1, 5, 6, 7, 9};

    int arr_hunred9[]  = {0, 1, 3, 4, 5, 9};
    int arr_hunred10[] = {3, 4, 5, 7, 8, 9};
    int arr_hunred11[] = {0, 4, 5, 6, 8, 9};

    int arr_hunred12[] = {1, 2, 3, 5, 6, 7};
    int arr_hunred13[] = {0, 1, 5, 6, 7, 9};
    int arr_hunred14[] = {0, 1, 2, 6, 7, 8};

    int arr_hunred15[] = {0, 2, 3, 4, 8, 9};
    int arr_hunred16[] = {2, 3, 4, 6, 7, 8};
    int arr_hunred17[] = {3, 4, 5, 7, 8, 9};

    // 百位数组
    int *arr_hunred[] = {arr_hunred0,arr_hunred1,arr_hunred2,arr_hunred3,arr_hunred4,arr_hunred5,arr_hunred6,arr_hunred7,arr_hunred8,arr_hunred9,arr_hunred10,arr_hunred11,arr_hunred12,arr_hunred13,arr_hunred14,arr_hunred15,arr_hunred16,arr_hunred17};

    int arr_hunred_nums = sizeof(arr_hunred) / sizeof(arr_hunred[0]);

    int arr_ten0[] = {3};
    int arr_ten1[] = {7};
    int arr_ten2[] = {8};
    int arr_ten3[] = {2};
    int arr_ten4[] = {6};
    int arr_ten5[] = {7};
    int arr_ten6[] = {8};
    int arr_ten7[] = {2};
    int arr_ten8[] = {3};
    int arr_ten9[] = {7};
    int arr_ten10[] = {1};
    int arr_ten11[] = {2};
    int arr_ten12[] = {9};
    int arr_ten13[] = {3};
    int arr_ten14[] = {4};
    int arr_ten15[] = {6};
    int arr_ten16[] = {0};
    int arr_ten17[] = {1};

    // 十位数组
    int *arr_tens[] = {arr_ten0, arr_ten1, arr_ten2, arr_ten3, arr_ten4, arr_ten5, arr_ten6, arr_ten7, arr_ten8, arr_ten9, arr_ten10, arr_ten11, arr_ten12, arr_ten13, arr_ten14, arr_ten15, arr_ten16, arr_ten17};

    // 各个位数数组
    int arr_num0[] = {2, 3, 4, 6, 7, 8};
    int arr_num1[] = {3, 4, 5, 7, 9, 8};
    int arr_num2[] = {1, 2, 3, 7, 8, 9};
    int arr_num3[] = {0, 2, 3, 4, 8, 9};
    int arr_num4[] = {0, 1, 2, 6, 7, 8};
    int arr_num5[] = {0, 1, 3, 4, 5, 9};
    int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5};

    // 组合输出的计数器
    int combination_count = 0;

    int *hundred = NULL;
    int *num = NULL;
    int *ten = NULL;

    int thouds_size = sizeof(arr_thouds) / sizeof(arr_thouds[0]);
    int hunred_size = sizeof(arr_hunred0) / sizeof(arr_hunred0[0]);
    int ten_size = sizeof(arr_ten0) / sizeof(arr_ten0[0]);
    int num_size = sizeof(arr_num0) / sizeof(arr_num0[0]);

    int ten_idx = 0;
    for (int i = 0; i < thouds_size; i++) {
        hundred = arr_hunred[i];
        for (int j = 0; j < hunred_size; j++) {
            num = arr_nums[i];
            ten = arr_tens[i];
            for (int k = 0; k < ten_size; k++) {
                for (int l = 0; l < num_size; l++) {
                    printf("%d%d%d%d,", arr_thouds[i], hundred[j], ten[k], num[l]);
                    combination_count++;
                    if (l == num_size - 1) {
                        printf("\r\n");
                        // ten_idx++;
                    }
                }
            }
        }
    }

    // 打开文件以写入
    // FILE *file = fopen("b.txt", "w");
    // if (file == NULL) {
    //     perror("Failed to open file");
    //     return 1; // 如果文件打开失败，返回错误
    // }

    // 遍历千位、百位、十位和个位数组，生成所有组合
    // for (int i = 0; i < thouds_size; i++) { // 千位
    //     for (int j = 0; j < hunred_size; j++) { // 百位
    //         // 根据 hunred 选择十位数组
    //         ten = arr_tens[j];
    //         // 根据 thouds 选择个位数组
    //         num = arr_nums[i];

    //         for (int k = 0; k < ten_size; k++) { // 遍历选择的十位数组
    //             for (int l = 0; l < num_size; l++) { // 遍历选择的个位数组
    //                 // 格式化输出
    //                 if (j == hunred_size - 1 && k == ten_size - 1 && l == num_size - 1) {
    //                     fprintf(file, "%d%d%d%d", arr_thouds[i], arr_hunred[j], ten[k], num[l]);
    //                 } else {
    //                     fprintf(file, "%d%d%d%d,", arr_thouds[i], arr_hunred[j], ten[k], num[l]);
    //                 }
    //                 combination_count++;
    //             }
    //         }
    //     }

    //     // 在每一个千位遍历结束时换行
    //     if (i != thouds_size - 1)
    //         fprintf(file, "\n");
    // }

    // 关闭文件
    // fclose(file);

    printf("Total combinations: %d\n", combination_count); // 输出组合总数

    return 0;
}
