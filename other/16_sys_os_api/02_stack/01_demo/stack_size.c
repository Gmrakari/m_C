#include <stdio.h>
#include <stdint.h>

#define BUFF_SIZE  (1024)
// test segment fault
//#define BUFF_NUM   (1000 * 10)
// test ok
//#define BUFF_NUM   (1000 * 5)
// test segment fault
//#define BUFF_NUM   (1000 * 9)

#define BUFF_NUM   (1000 * 8)

char g_arr[BUFF_SIZE * BUFF_NUM + 1] = {0};

static int _test_02()
{
    char arr[BUFF_SIZE * BUFF_NUM] = {0};

    printf("[%s][%d]\r\n", __func__, __LINE__);
}

int main() {
    _test_02();

    printf("[%s][%d]\r\n", __func__, __LINE__);

    char *ptr = g_arr;
    
    printf("[%s][%d]%02X\r\n", __func__, __LINE__, ptr[0]);

    return 0;
}
