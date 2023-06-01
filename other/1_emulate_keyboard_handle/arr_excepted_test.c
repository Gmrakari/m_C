#include <stdio.h>


// {0, 1, 2, 3} = mode1 => FARF
// {2, 1, 0, 3} = mode2 => RAFF
// {2, 0, 3, 1} = mode3 => None
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

int g_key_mode = -1;

int get_test() {
    int match = -1;

    int ep_order[4] = {0, 1, 2, 3};
    int order[4] = {2, 1, 0, 4};

    for (int i = 0; i < sizeof(g_key_order) / sizeof(g_key_order[0]); i++) {
        g_key_order[g_key_index++] = ep_order[i];
    }
    
    for (int i = 0; i < 4; i++) {
        printf("g_key_order:%d\r\n", g_key_order[i]);
    }

    printf("\r\n");
    printf("g_key_index:%d\r\n", g_key_index);


    // printf("g_expected_order size:%ld\r\n", sizeof(g_expected_order));
    // printf("rows size:%ld\r\n", sizeof(g_expected_order) / sizeof(g_expected_order[0]));
    // printf("columns size:%ld\r\n", sizeof(g_expected_order[0]) / sizeof(g_expected_order[0][0]));
    // printf("g_expected_order[0] size:%ld\r\n", sizeof(g_expected_order[0]));
    // printf("g_expected_order[0][0] size:%ld\r\n", sizeof(g_expected_order[0][0]));
    // printf("total:%ld\r\n", (sizeof(g_expected_order) / sizeof(g_expected_order[0])) * (sizeof(g_expected_order[0]) / sizeof(g_expected_order[0][0])));

    printf("\r\n");
    if (g_key_index == 4) {
        for (int i = 0; i < sizeof(g_expected_order) / sizeof(g_expected_order[0]); i++) {
            match = 1;
            for (int j = 0; j < g_key_index; j++) {
                printf("g_key_order[%d]:%d\r\n", j, g_key_order[j]);
                printf("g_expected_order[%d][%d]:%d\r\n", i, j, g_expected_order[i][j]);
                if (g_key_order[j] != g_expected_order[i][j]) {
                    match = -1;
                    break;
                }
            }
            g_key_index = 0;

            if (i == FAKE_AS_REAL_FACE_MODE) {
                g_key_mode = FAKE_AS_REAL_FACE_MODE;
            } else if (i == REAL_AS_FAKE_FACE_MODE) {
                g_key_mode = REAL_AS_FAKE_FACE_MODE;
            }
        }
    }

    if (match) {
        if (g_key_index == 4) {
            g_key_index = 0;
        }
    } else {
        g_key_mode = -1;
    }
    printf("match:%d\r\n", match);
    printf("g_key_mode:%d\r\n", g_key_mode);

    return match;
}

void func(int *arr, int arr_len) {
    for (int i = 0; i < arr_len; i++) {
        g_key_order[g_key_index++] = arr[i];
    }
}

void match_test()
{
    int match = -1;

    int ep_order_1[4] = {0, 1, 2, 3};
    int ep_order_2[4] = {2, 1, 0, 3};
    int ep_order_3[4] = {2, 0, 3, 1};

    func(ep_order_1, sizeof(ep_order_1) / sizeof(ep_order_1[0]));
    // func(ep_order_2, sizeof(ep_order_2) / sizeof(ep_order_2[0]));
    // func(ep_order_3, sizeof(ep_order_3) / sizeof(ep_order_3[0]));


    for (int i = 0; i < sizeof(g_expected_order) / sizeof(g_expected_order[0]); i++) {
        match = 1;
        for (int j = 0; j < g_key_index; j++) {
            if (g_key_order[j] != g_expected_order[i][j]) {
                match = -1;
                break;
            } else if ()
        }
    }

    
    
}

int main() {
    char c;

    // printf("开始接收键盘输入, 请按Ctrl+C结束程序。\n");

    // while (1) {
    //     while ((c = getchar()) != '\n') {
    //         printf("您输入的字符是: %c\r\n", c);
    //     }
    // }

    get_test();


    return 0;
}
