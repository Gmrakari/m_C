
#include "class_headers.h"

test_class_t test_class;

int type_choose(type_t type) {
    int ret = -1;

    switch (type) {
        case TYPE_TEST:
            choose_test(&test_class); break;
        default:
            ret = 0;
            break;
    }
    return ret;
}
