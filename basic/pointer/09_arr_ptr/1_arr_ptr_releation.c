#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int _arr_pointer_releation(void)
{
    int a[] = {1, 2, 3, 4, 5};
    int *p = (int*)(&a + 1);

    int *num = (int*)&a[0];

    // printf("%d %d\r\n", *(p - 1), *(a + 1));
    printf("%d %d %d\r\n", *(p - 1), *(a + 1), *(num + 1));
    
    // printf("%d %d %d\r\n", *(p - 1), *p, *(p + 1));

    char *ptr[8];

    printf("%ld\r\n", sizeof(ptr));
    printf("%ld\r\n", sizeof(ptr) / sizeof(ptr[0]));

    return 0;
}

// gcc -g -o arr_ptr_app 1_arr_ptr_releation.c
int main() {
    int rc = 0;
    
    rc = _arr_pointer_releation();

    return rc;
}