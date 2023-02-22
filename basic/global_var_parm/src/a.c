#include "a.h"

static int *val = 15000;

void set_val_func(int *value)
{
    val = value;
}

int *get_val_func(void)
{
    return val;
}

void funA()
{
    int ret = get_val_func();
    printf("[%s]ret:%d\r\n", __func__, ret);

    return ;
}
