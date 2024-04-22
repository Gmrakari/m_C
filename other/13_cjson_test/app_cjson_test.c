
#include "app_cjson_test.h"

cJSON* asr_generate_common_param(asr_common_param_t *param)
{
    if (!param)
        return NULL;

    cJSON *comm = cJSON_CreateObject();
    if (comm == NULL) {
        printf("comm cJSON_CreateObject err!");
        return NULL;
    }

    cJSON_AddStringToObject(comm, "appid", param->appid);

    return comm;
}

cJSON* asr_generate_business_param(asr_business_param_t *param)
{
    if (!param) {
        printf("asr_business_param_t param is null!");
        return NULL;
    }

    cJSON *business = cJSON_CreateObject();
    if (business == NULL) {
        printf("business cJSON_CreateObject err!");
        return NULL;
    }

    const char *key_list[] = {
        "language", "domain", "accent", "vad_eos", 
        "dwa", "pd", "ptt", "rlang", 
        "vinfo", "nunum", "speex_size", "nbest", "wbest"
    };

    cJSON *value_list[] = {
        cJSON_CreateString(param->language),
        cJSON_CreateString(param->domain),
        cJSON_CreateString(param->accent),
        cJSON_CreateNumber(param->vad_eos),
        cJSON_CreateString(param->dwa),
        cJSON_CreateString(param->pd),
        cJSON_CreateNumber(param->ptt),
        cJSON_CreateString(param->rlang),
        cJSON_CreateNumber(param->vinfo),
        cJSON_CreateNumber(param->nunum),
        cJSON_CreateNumber(param->speex_size),
        cJSON_CreateNumber(param->nbest),
        cJSON_CreateNumber(param->wbest)
    };

    for (int i = 0;i < (int)(sizeof(key_list) / sizeof(key_list[0])); i++) {
        cJSON_AddItemToObject(business, key_list[i], value_list[i]);
    }

    return business;
}

cJSON* asr_generate_data_param(asr_data_param_t *param)
{
    if (!param) {
        printf("asr_data_param_t param is null!");
        return NULL;
    }

    cJSON *data = cJSON_CreateObject();
    if (data == NULL) {
        printf("data cJSON_CreateObject err!");
        return NULL;
    }

    const char *key_list[] = {
        "status", "format", "encode", "audio"
    };

    cJSON *value_list[] = {
        cJSON_CreateNumber(param->status),
        cJSON_CreateString(param->format),
        cJSON_CreateString(param->encode),
        cJSON_CreateString(param->audio)
    };

    for (int i = 0;i < (int)(sizeof(key_list) / sizeof(key_list[0])); i++) {
        cJSON_AddItemToObject(data, key_list[i], value_list[i]);
    }

    return data;
}

cJSON* asr_generate_root(cJSON *comm, cJSON *business, cJSON *data)
{
    if (!comm || !business || !data) {
        printf("comm || business data param is null!");
        return NULL;
    }

    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        printf("root cJSON_CreateObject err!");
        return NULL;
    }

    const char *key_list[] = {
        "common", "business", "data"
    };

    cJSON *value_list[] = {
        comm, business, data
    };

    for (int i = 0;i < (int)(sizeof(key_list) / sizeof(key_list[0])); i++) {
        cJSON_AddItemToObject(root, key_list[i], value_list[i]);
    }

    return root;
}
