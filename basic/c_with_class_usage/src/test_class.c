
#include "class_headers.h"

static test_class_t *me;

static int _test_class_init(void) {
    int ret = -1;
    printf("_test_class_init\r\n");
    
    ret = 0;
    printf("_test_class_init finish\r\n");
    return ret;
}

static int _test_class_get(void) {
    int ret = -1;
    printf("_test_class_get\r\n");

    ret = 0;

    printf("_test_class_get finish\r\n");
    return ret;
}

int choose_test(test_class_t *tc) {
    int ret = -1;
    tc->init = _test_class_init;
    tc->get = _test_class_get;
    // me = tc;
    printf("choose_test type\r\n");
    return ret;
}
