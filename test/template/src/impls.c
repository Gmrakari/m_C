#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "impls.h"
#include "conf.h"

int app(void)
{
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return 0;
}
