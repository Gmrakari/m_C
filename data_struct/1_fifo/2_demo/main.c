#include "ring_buffer.h"
#include <stdio.h>

// #define LOGI(format, ...) printf("[%s][%s][%d]"format"\r\n" , __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#define LOGI(format, ...) printf("[%s][%d]"format"\r\n" , __func__, __LINE__, ##__VA_ARGS__)

// static unsigned char data[] = {0x01, 0x02, 0x03};
static unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

#define FIFO_MAX_SIZE                      (10)

static void _ring_buffer_test()
{
    RingBuffer *fifo = RingBuffer_Malloc(FIFO_MAX_SIZE);LOGI();
    if (!fifo) {LOGI();
        printf("[%s][%d]RingBuffer_Malloc err!\r\n", __func__, __LINE__);
        return ;
    }

    LOGI("RingBuffer_Len: %d", RingBuffer_Len(fifo));
    LOGI("RingBuffer_Avail: %d", RingBuffer_Avail(fifo));

    int ilen = 0;
    ilen = RingBuffer_In(fifo, &data, sizeof(data));
    if (ilen != sizeof(data)) {
        LOGI("RingBuffer_In err\r\n");
    }

    LOGI("RingBuffer_Len: %d", RingBuffer_Len(fifo));
    LOGI("RingBuffer_Avail: %d", RingBuffer_Avail(fifo));

    unsigned char buf[FIFO_MAX_SIZE] = {0};
    int olen = RingBuffer_Out(fifo, &buf, sizeof(buf));
    LOGI("olen: %d", olen);

    for (int i = 0; i < olen; i++) {
        printf("%02X", buf[i]);
        if (i != (olen - 1)) {
            printf(" ");
        }
    }
    printf("\r\n");

    LOGI("RingBuffer_Len: %d", RingBuffer_Len(fifo));
    LOGI("RingBuffer_Avail: %d", RingBuffer_Avail(fifo));

    if (fifo) {LOGI();
        RingBuffer_Free(fifo);
    }LOGI();

    return ;
}

int main()
{LOGI();
    _ring_buffer_test();
LOGI();
    return 0;
}
