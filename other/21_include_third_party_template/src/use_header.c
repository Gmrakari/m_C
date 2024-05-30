#include "use_header.h"
#include <stdio.h>

void app(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return ;
}
