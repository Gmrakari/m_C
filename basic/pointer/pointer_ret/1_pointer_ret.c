#include <stdio.h>
#include <stdint.h>

static int *value;

void set_time(void) {

    int ret = 2;
    value = &ret;
    printf("ret:%d\r\n", ret);
}

int* get(void) {
    return value;
}

static void func(void)
{
    printf("static func\r\n");
    return ;
}

void func(void)
{
    printf("non static func\r\n");
    return ;
}

int main(int argc, char const *argv[]) {
    // set_time();

    // int *ge_val = get();
    // printf("ge_val:%d\r\n", *ge_val);

    func();
}
