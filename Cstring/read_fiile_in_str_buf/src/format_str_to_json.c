#include <stdio.h>
#include "format_str_to_json.h"

int format_str_to_json(const char *str, cJSON *json) {
    if (!str || !json) return -1;

    printf("[%s]\r\n", __func__);

    return 0;
}