#include "usr_api.h"
#include "cJSON.h"
#include "file_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int _gen_cjson_resp(int qos, int *index, int optype, int len)
{
    if (!index) {
        printf("invalid param!");
        return -1;
    }

    int ret = 0;

    cJSON *pwdData = cJSON_CreateObject();
    if (!pwdData) {
        printf("cJSON_CreateObject err!");
        return -1;
    }

    cJSON_AddNumberToObject(pwdData, "index", *index);
    cJSON_AddNumberToObject(pwdData, "type", 8);
    cJSON_AddStringToObject(pwdData, "deviceUserId", "0");
    cJSON_AddNumberToObject(pwdData, "timeType", 1);

    cJSON_AddNullToObject(pwdData, "activeTime");
    cJSON_AddNullToObject(pwdData, "expireTime");
    cJSON_AddNullToObject(pwdData, "startTime");
    cJSON_AddNullToObject(pwdData, "endTime");
    cJSON_AddNullToObject(pwdData, "loops");

    cJSON *data = cJSON_CreateObject();
    if (!data) {
        printf("cJSON_CreateObject err!");
        cJSON_Delete(pwdData);
        return -1;
    }

    cJSON_AddNullToObject(data, "subUuid");
    cJSON_AddNumberToObject(data, "operatorType", optype);
    cJSON_AddItemToObject(data, "pwdData", pwdData);

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        printf("cJSON_CreateObject err!");
        cJSON_Delete(data);
        return -1;
    }

    char tmp[16] = {0};

    cJSON_AddStringToObject(root, "msgId", "123");
    cJSON_AddNumberToObject(root, "ts", time(NULL));

    cJSON_AddItemToObject(root, "data", data);

    // char *string = cJSON_PrintUnformatted(root);
    char *string = cJSON_Print(root);
    if (string) {
        printf("%s\r\n", string);

        const char *path = "../output/a.json";
        ret = write_buffer_to_file(path, string, strlen(string));
        free(string);
    }

    cJSON_Delete(root);

    return ret;
}

int test_tmp_passwd_cjson_api_app(void)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    int index = 2;
    ret = _gen_cjson_resp(0, &index, 2, 2);

    return ret;
}
