#include <stdio.h>
#include <stdint.h>

#define BUFF_SIZE  (1024)
#define BUFF_NUM   (1000 * 10)

static int _test_02()
{
//    char arr[BUFF_SIZE * BUFF_NUM] = {0};

    printf("[%s][%d]\r\n", __func__, __LINE__);
}

int main() {
    _test_02();

    printf("[%s][%d]\r\n", __func__, __LINE__);

    size_t len = sizeof(char) * BUFF_SIZE * BUFF_NUM;
    char *ptr = (char*)malloc(len);

    if (ptr) {
    	free(ptr);
	    ptr = NULL;
    }
    
    printf("[%s][%d]%02X\r\n", __func__, __LINE__, ptr[0]);

    return 0;
}
