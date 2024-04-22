#include <stdio.h>

#include <time.h>

#define LOGD(fmt, ...)   printf("[%s][%s](%d): " fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__)

int main()
{
    int val = 0;
    int ret = 5;

    int flip_flag_1 = 0;
    int flip_flag_2 = 0;

    while (1) {//LOGD("");

        if (!flip_flag_1) {
            flip_flag_1 = 1;
            if (!flip_flag_2) {
                flip_flag_2 = 1;
                val = 1;
            } else {
                flip_flag_2 ^= flip_flag_2;
                val = 3;
            }
        } else {
            flip_flag_1 ^= flip_flag_1;
            val = 2;
        }

        // printf("[%s][%d]val: %d\r\n", __func__, __LINE__, val);
        LOGD("val:%d\r\n", val);

        sleep(1);
    }

    return 0;
}
