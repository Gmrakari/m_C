#include "class_headers.h"

int main() {
    int ret = 0;
    ret = type_choose(TYPE_TEST);
    printf("ret:%d\r\n", ret);
    test_class.init();
    test_class.get();
    printf("init and get finish\r\n");
}
