#include <stdio.h>

#include "format_pairs_to_json.h"

cJSON *format_pairs_to_json(const pairs_info_t **pairs_info, const size_t pairs_num) {
    if (!pairs_info) return NULL;

    cJSON *pjson = cJSON_CreateObject();
    if (!pjson) return NULL;

    for (size_t i = 0; i < pairs_num; i++) { 
        cJSON_AddStringToObject(pjson, (*pairs_info)[i].key, (*pairs_info)[i].value);
    }

    return pjson;
}
