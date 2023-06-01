#include <stdio.h>

const int g_expected_order[][4] = {
    {0, 1, 2, 3},
    {2, 1, 0, 3},
    {2, 0, 3, 1}
};

int g_key_index = 0;
int g_key_order[4] = {0};

typedef enum {
    FAKE_AS_REAL_FACE_MODE = 0,
    REAL_AS_FAKE_FACE_MODE,
    NONE_MODE,
} recoed_mode_t;

int g_result_mode = -1;

void processKeyboardInput(int input) {
    g_key_order[g_key_index++] = input;

    if (g_key_index == 4) {
        for (int i = 0; i < 3; i++) {
            int match = 1;
            for (int j = 0; j < 4; j++) {
                if (g_key_order[j] != g_expected_order[i][j]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                g_result_mode = i;
                break;
            }
        }
        g_key_index = 0;
    }
}

void test(int *arr, int arr_len, int i) {
    for (int i = 0; i < arr_len; i++) {
        processKeyboardInput(arr[i]);
    }

    // 输出匹配的模式结果
    if (g_result_mode != -1) {
        printf("Matched mode: %d\n", g_result_mode);
    } else {
        printf("No matching mode found.\n");
    }
    printf("\r\n");
}

void for_test(void) {
    // int ep_order[][4] = {{0, 1, 2, 3}, {2, 1, 0, 3}, {2, 0, 3, 1}};
    int ep_order[][4] = {{1, 1, 2, 3}, {1, 1, 1, 3}, {2, 2, 3, 1}};


    for (int i = 0; i < sizeof(ep_order) / sizeof(ep_order[0]); i++) {
        printf("test:%d\r\n", i);
        test(ep_order[i], sizeof(ep_order[i]) / sizeof(ep_order[i][0]), i);
    }
}

int main() {
    for_test();
    return 0;
}
