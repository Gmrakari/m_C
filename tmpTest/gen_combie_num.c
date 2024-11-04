#include <stdio.h>

int main() {

    // 千位3个一组
    // 百位每个不同 6位一组
    // 十位 一个
    // 个位 有不定长elem_len

    // 千位数组
    int arr_thouds[] = {0, 0, 0, 1, 1, 1, 5, 5, 5, 6, 6, 6, 4, 4, 4, 7, 7, 7, 0, 0, 0, 1, 1, 1, 5, 5, 5, 6, 6, 6, 4, 4, 4, 7, 7, 7};

    // 百位数组
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
    int arr_num1[] = {3, 4, 5, 7, 8, 9};
    int arr_num2[] = {1, 2, 3, 7, 8, 9};
    int arr_num3[] = {0, 2, 3, 4, 8, 9};
    int arr_num4[] = {0, 1, 2, 6, 7, 8};
    int arr_num5[] = {0, 1, 3, 4, 5, 9};

    int arr_num6[] = {4, 7};
    int arr_num7[] = {3, 4, 5, 7, 8, 9};
    int arr_num8[] = {1, 7};
    int arr_num9[] = {4};
    int arr_num10[] = {8};
    int arr_num11[] = {3, 5};

    int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5, arr_num6, arr_num7, arr_num8, arr_num9, arr_num10, arr_num11};

    int arr_nums_len[] = {sizeof(arr_num0) / sizeof(arr_num0[0]), sizeof(arr_num1) / sizeof(arr_num1[0]),
                           sizeof(arr_num2) / sizeof(arr_num2[0]), sizeof(arr_num3) / sizeof(arr_num3[0]),
                           sizeof(arr_num4) / sizeof(arr_num4[0]), sizeof(arr_num5) / sizeof(arr_num5[0]),
                           sizeof(arr_num6) / sizeof(arr_num6[0]), sizeof(arr_num7) / sizeof(arr_num7[0]),
                           sizeof(arr_num8) / sizeof(arr_num8[0]), sizeof(arr_num9) / sizeof(arr_num9[0]),
                           sizeof(arr_num10) / sizeof(arr_num10[0]), sizeof(arr_num11) / sizeof(arr_num11[0])};

    // 组合输出的计数器
    int combination_count = 0;

    int *hundred = NULL;
    int *num = NULL;
    int *ten = NULL;

    int thouds_elem_size = sizeof(arr_thouds) / sizeof(arr_thouds[0]);
    int hunred_elem_size = sizeof(arr_hunred0) / sizeof(arr_hunred0[0]);
    int ten_elem_size = sizeof(arr_ten0) / sizeof(arr_ten0[0]);
    int num_elem_size = sizeof(arr_num0) / sizeof(arr_num0[0]);

    int ten_idx = 0;
    int num_idx = 0;

    // 打开文件以写入
    FILE *file = fopen("b.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // 如果文件打开失败，返回错误
    }

    for (int i = 0; i < thouds_elem_size; i++) {
        if (ten_idx == thouds_elem_size / 2)
            ten_idx = 0;
        hundred = arr_hunred[ten_idx];
        if (i % 3 == 0) {
            num = arr_nums[num_idx];
            num_elem_size = arr_nums_len[num_idx];
            num_idx++;
        }
        for (int j = 0; j < ten_elem_size; j++) {
            ten = arr_tens[ten_idx];
            for (int k = 0; k < hunred_elem_size; k++) {
                for (int l = 0; l < num_elem_size; l++) {
                    if (l == num_elem_size - 1 && k == hunred_elem_size - 1) {
                        fprintf(file, "%d%d%d%d", arr_thouds[i], hundred[k], ten[j], num[l]);
                    } else {
                        fprintf(file, "%d%d%d%d,", arr_thouds[i], hundred[k], ten[j], num[l]);
                    }
                    combination_count++;
                }
            }
            ten_idx++;
        }
        // 在每一个千位遍历结束时换行
        if (i != thouds_elem_size - 1)
            fprintf(file, "\n");
    }

    // 关闭文件
    fclose(file);

    printf("Total combinations: %d\n", combination_count); // 输出组合总数

    return 0;
}
