#include <stdio.h>
#include <stdint.h>
// #include "check_app.h"

#include "fsm_base.h"

// int fsg_base_main();

static int test_app()
{
    int rc = 0;
    // sig_data_check_ecc256();
    printf("[%s][%d]\r\n", __func__, __LINE__);

    fsg_base_main();

    return rc;
}

int main()
{
    test_app();

    return 0;
}
