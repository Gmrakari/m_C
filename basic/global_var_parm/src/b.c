#include "b.h"

void funB() {
    int ret = get_val_func();

    printf("[%s]ret:%d\r\n", __func__, ret);


    int *new_val = 20000;
    set_val_func(new_val);

    ret = get_val_func();

    printf("[%s]ret:%d\r\n", __func__, ret);
    return ;
}
