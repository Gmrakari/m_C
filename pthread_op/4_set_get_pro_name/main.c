#include <stdio.h>
#include "get_set_process.h"

int main() 
{
    print();

    app();
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}
