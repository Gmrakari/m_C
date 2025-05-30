#include "usr_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int usr_api_app(void)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return ret;
}
