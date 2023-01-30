
#include "pub.h"

static void func(void) {
    printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("run pub func\r\n");
    printf("[%s][%d]\r\n", __func__, __LINE__);
}

void m_pub_func(void) {
    printf("m_pub_func\r\n");
    printf("[%s][%d]\r\n", __func__, __LINE__);

    mf_record_pass_upload_pic_register_cb(func);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    printf("\r\n");

    return ;
}
