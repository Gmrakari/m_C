#include <stdio.h>
#include <stdint.h>

#include "tmp_passwd_list_db.h"
#include "utils/db_conf.h"

int main()
{
    int ret = 0;

    printf("[%s][%d]start to run app!\r\n", __func__, __LINE__);

    #if 0
    ret = db_list_app();
    if (ret != 0) {
        printf("[%s][%d]\r\n", __func__, __LINE__);
        return ret;
    }
    #endif

    #if 1
    ret = tmp_passwd_db_list_app();
    if (ret != 0) {
        printf("[%s][%d]\r\n", __func__, __LINE__);
        return ret;
    }
    #endif 

    printf("[%s][%d]run finish!\r\n", __func__, __LINE__);

    return 0;
}
