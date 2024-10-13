#if 0
#include <stdio.h>

int main()
{
#if 0
    int count = 0;
    // 千位数组
    int arr_thouds_0[] = {0}; // 千位只有0
    // 百位数组
    int arr_hunred[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 百位从0到9
    // 十位数组
    int arr_ten[] = {9, 0, 1, 5, 1, 2, 6, 0, 1, 2, 3, 7, 2, 3, 4, 8, 3, 4, 5, 9, 4, 5, 6, 0, 5, 6, 7, 1, 6, 7, 8, 2, 7, 8, 9, 3, 8, 9, 0, 4}; // 十位给出的数字
    // 个位数组
    int arr_num_0[] = {2, 3, 4, 6, 7, 8}; // 个位给出的数字

    // 依次遍历千、百、十、个四列的每个数字并组合
    for (int i = 0; i < sizeof(arr_thouds_0) / sizeof(arr_thouds_0[0]); i++) { // 遍历千位
        for (int j = 0; j < sizeof(arr_hunred) / sizeof(arr_hunred[0]); j++) { // 遍历百位
            for (int k = 0; k < sizeof(arr_ten) / sizeof(arr_ten[0]); k++) { // 遍历十位
                for (int l = 0; l < sizeof(arr_num_0) / sizeof(arr_num_0[0]); l++) { // 遍历个位
                    // 输出组合，保持格式化
                    printf("%d%d%d%d,", arr_thouds_0[i], arr_hunred[j], arr_ten[k], arr_num_0[l]);
                    count++;
                }
            }
        }
    }

    // printf("count:%d\r\n", count);

    int arr_thouds_1[] = {1}; // 千位只有1
    int arr_num1[] = {3,4,5,7,8,9};

    for (int i = 0; i < sizeof(arr_thouds_1) / sizeof(arr_thouds_1[0]); i++) { // 遍历千位
        for (int j = 0; j < sizeof(arr_hunred) / sizeof(arr_hunred[0]); j++) { // 遍历百位
            for (int k = 0; k < sizeof(arr_ten) / sizeof(arr_ten[0]); k++) { // 遍历十位
                for (int l = 0; l < sizeof(arr_num1) / sizeof(arr_num1[0]); l++) { // 遍历个位
                    // 输出组合，保持格式化
                    printf("%d%d%d%d,", arr_thouds_1[i], arr_hunred[j], arr_ten[k], arr_num1[l]);
                    count++;
                }
            }
        }
    }

    #endif 

    #if 0
    // 千位数组
    int arr_thouds_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 千位只有2
    // int arr_thouds_2[] = {0}; // 千位只有2
    // 百位数组
    int arr_hunred[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 百位从0到9
    // int arr_hunred[] = {0}; // 百位从0到9
    // 十位数组
    int arr_ten[] = {9, 0, 1, 5, 1, 2, 6, 0, 1, 2, 3, 7, 2, 3, 4, 8, 3, 4, 5, 9, 4, 5, 6, 0, 5, 6, 7, 1, 6, 7, 8, 2, 7, 8, 9, 3, 8, 9, 0, 4}; // 十位给出的数字

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

    // 组合输出的计数器
    int count = 0;

    // 遍历千、百、十、个四列的每个数字并组合
    for (int i = 0; i < sizeof(arr_thouds_2) / sizeof(arr_thouds_2[0]); i++) { // 遍历千位
        for (int j = 0; j < sizeof(arr_hunred) / sizeof(arr_hunred[0]); j++) { // 遍历百位
            for (int k = 0; k < sizeof(arr_ten) / sizeof(arr_ten[0]); k++) { // 遍历十位
                // 遍历个位数组 2 到 9
                int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5, arr_num6, arr_num7, arr_num8, arr_num9};
                for (int l = 0; l < sizeof(arr_nums) / sizeof(arr_nums[0]); l++) { // 遍历不同的个位数组
                    for (int m = 0; m < sizeof(arr_nums[l]) / sizeof(arr_nums[l][0]); m++) { // 遍历每个个位数组的数字
                        // 输出组合，保持格式化
                        printf("%d%d%d%d,", arr_thouds_2[i], arr_hunred[j], arr_ten[k], arr_nums[l][m]);
                        count++;
                    }
                }

            }
        }
    }

    printf("\nTotal combinations: %d\n", count); // 输出组合总数
#endif

    // 千位数组
    int arr_thouds_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 千位
    // 百位数组
    int arr_hunred[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 百位
    // 十位数组
    int arr_ten[] = {9, 0, 1, 5, 1, 2, 6, 0, 1, 2, 3, 7, 2, 3, 4, 8, 3, 4, 5, 9, 4, 5, 6, 0, 5, 6, 7, 1, 6, 7, 8, 2, 7, 8, 9, 3, 8, 9, 0, 4}; // 十位给出的数字

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

    // 组合输出的计数器
    int count = 0;

    // 打开文件以写入
    FILE *file = fopen("b.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // 如果文件打开失败，返回错误
    }

    // 遍历千、百、十、个四列的每个数字并组合
    for (int i = 0; i < sizeof(arr_thouds_2) / sizeof(arr_thouds_2[0]); i++) { // 遍历千位
        for (int j = 0; j < sizeof(arr_hunred) / sizeof(arr_hunred[0]); j++) { // 遍历百位
            for (int k = 0; k < sizeof(arr_ten) / sizeof(arr_ten[0]); k++) { // 遍历十位
                // 遍历个位数组 0 到 9
                int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5, arr_num6, arr_num7, arr_num8, arr_num9};
                for (int l = 0; l < sizeof(arr_nums) / sizeof(arr_nums[0]); l++) { // 遍历不同的个位数组
                    for (int m = 0; m < sizeof(arr_nums[l]) / sizeof(arr_nums[l][0]); m++) { // 遍历每个个位数组的数字
                        // 输出组合到文件，保持格式化
                        fprintf(file, "%d%d%d%d,", arr_thouds_2[i], arr_hunred[j], arr_ten[k], arr_nums[l][m]);
                        count++;
                    }
                }
            }
        }
    }

    // 关闭文件
    fclose(file);

    printf("Total combinations: %d\n", count); // 输出组合总数

    return 0;
}

#endif


#include <stdio.h>
#include <string.h>

#define MAX_COMBINATIONS 100000 // 预设最大组合数

// 函数检查组合是否存在
int exists(int combinations[][4], int count, int new_combination[4]) {
    for (int i = 0; i < count; i++) {
        if (combinations[i][0] == new_combination[0] &&
            combinations[i][1] == new_combination[1] &&
            combinations[i][2] == new_combination[2] &&
            combinations[i][3] == new_combination[3]) {
            return 1; // 组合存在
        }
    }
    return 0; // 组合不存在
}

int main() {
    // 千位数组
    int arr_thouds_2[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 千位
    // 百位数组
    int arr_hunred[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // 百位
    // 十位数组
    int arr_ten[] = {9, 0, 1, 5, 1, 2, 6, 0, 1, 2, 3, 7, 2, 3, 4, 8, 3, 4, 5, 9, 4, 5, 6, 0, 5, 6, 7, 1, 6, 7, 8, 2, 7, 8, 9, 3, 8, 9, 0, 4}; // 十位给出的数字

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

    // 组合输出的计数器
    int count = 0;

    // 创建一个二维数组以存储已写入的组合
    int combinations[MAX_COMBINATIONS][4];
    int combination_count = 0;

    // 打开文件以写入
    FILE *file = fopen("b.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1; // 如果文件打开失败，返回错误
    }

    // 遍历千、百、十、个四列的每个数字并组合
    for (int i = 0; i < sizeof(arr_thouds_2) / sizeof(arr_thouds_2[0]); i++) { // 遍历千位
        for (int j = 0; j < sizeof(arr_hunred) / sizeof(arr_hunred[0]); j++) { // 遍历百位
            for (int k = 0; k < sizeof(arr_ten) / sizeof(arr_ten[0]); k++) { // 遍历十位
                // 遍历个位数组 0 到 9
                int* arr_nums[] = {arr_num0, arr_num1, arr_num2, arr_num3, arr_num4, arr_num5, arr_num6, arr_num7, arr_num8, arr_num9};
                for (int l = 0; l < sizeof(arr_nums) / sizeof(arr_nums[0]); l++) { // 遍历不同的个位数组
                    for (int m = 0; m < sizeof(arr_nums[l]) / sizeof(arr_nums[l][0]); m++) { // 遍历每个个位数组的数字
                        // 创建新的组合
                        int new_combination[4] = {arr_thouds_2[i], arr_hunred[j], arr_ten[k], arr_nums[l][m]};
 
                        // 检查组合是否已经存在
                        if (!exists(combinations, combination_count, new_combination)) {
                            // 输出组合到文件，保持格式化
                            fprintf(file, "%d%d%d%d,", new_combination[0], new_combination[1], new_combination[2], new_combination[3]);
                            
                            // 保存组合
                            combinations[combination_count][0] = new_combination[0];
                            combinations[combination_count][1] = new_combination[1];
                            combinations[combination_count][2] = new_combination[2];
                            combinations[combination_count][3] = new_combination[3];
                            combination_count++;
                        }
                    }
                }
            }
        }
    }

    // 关闭文件
    fclose(file);

    printf("Total combinations: %d\n", combination_count); // 输出组合总数

    return 0;
}
