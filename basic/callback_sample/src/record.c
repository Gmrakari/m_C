#include "record.h"

static struct {
    int *num;
} private;

static void (*record_pass_cb)(void) = NULL;

void mf_record_pass_upload_pic_register_cb(void (*cb)()) {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    record_pass_cb = cb;
    printf("[%s][%d]\r\n", __func__, __LINE__);
}

void m_record_func(void) {
    printf("run m_record_func\r\n");
    printf("[%s][%d]\r\n", __func__, __LINE__);

    if (record_pass_cb) {
        printf("[%s][%d]\r\n", __func__, __LINE__);
        record_pass_cb();
    }
    printf("[%s][%d]\r\n", __func__, __LINE__);

    printf("\r\n");

    return ;
}
