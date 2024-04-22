#include "app_asr_parse_resp.h"

typedef struct {
    int code;
    char *message;
    char *sid;
    struct data {
        char *result;
        int status;
    };
} asr_parse_param_t;

int app_asr_parse_resp(const char *src, const int len, char **out)
{
    const char *comm_key_name[] = {
        "code", "message", "sid", "data"
    };

    const char *data_key_name[] = {
        "result", "status"
    };

    // Step 1: 创建 cJSON 对象
    cJSON *root = cJSON_Parse(src);
    if (root == NULL) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return 1;
    }

    // Step 2: 获取所需字段值
    cJSON *code = cJSON_GetObjectItem(root, "code");
    cJSON *message = cJSON_GetObjectItem(root, "message");
    cJSON *data = cJSON_GetObjectItem(root, "data");

    if (code != NULL) {
        printf("code: %d\n", code->valueint);
    }
    if (message != NULL) {
        printf("message: %s\n", message->valuestring);
    }

    char buff[100] = {0};

    // Step 3: 获取 data 字段中的 ws 数组
    if (data != NULL) {
        cJSON *result = cJSON_GetObjectItem(data, "result");
        if (result != NULL) {
            cJSON *ws = cJSON_GetObjectItem(result, "ws");
            if (ws != NULL && cJSON_IsArray(ws)) {
                // Step 4: 逐个解析 ws 数组中的元素
                int i;
                cJSON *cw, *w;
                cJSON_ArrayForEach(cw, ws) {
                    cJSON *cw_array = cJSON_GetObjectItem(cw, "cw");
                    cJSON_ArrayForEach(w, cw_array) {
                        cJSON *w_str = cJSON_GetObjectItem(w, "w");
                        if (w_str != NULL && cJSON_IsString(w_str)) {
                            printf("w: %s\n", w_str->valuestring);
                            strncat(buff, w_str->valuestring, strlen(w_str->valuestring));
                        }
                    }
                }
            }
        }
    }

    printf("buff: %s\n", buff);

    // Step 5: 释放 cJSON 对象
    cJSON_Delete(root);


    return 0;   
}

int parse_normal_chat_resp_data(const char *in_json_str, const int len, char **out)
{printf("[%s][%d]\r\n", __func__, __LINE__);
    if (!in_json_str || !len) {
        printf("[%s][%d]param err!\r\n", __func__, __LINE__);
        return -1;
    }
printf("[%s][%d]\r\n", __func__, __LINE__);
    int err = 0;

    const char *json_str = in_json_str;
    cJSON *root = cJSON_Parse(json_str);printf("[%s][%d]\r\n", __func__, __LINE__);
    if (root == NULL) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]cJSON_Parse err!\r\n", __func__, __LINE__);
        err = -1;
        return err;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    cJSON *cmd = cJSON_GetObjectItem(root, "cmd");printf("[%s][%d]\r\n", __func__, __LINE__);
    if (cmd == NULL || cmd->valuestring == NULL) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]cJSON_GetObjectItem err!\r\n", __func__, __LINE__);
        cJSON_Delete(root);
        err = -1;
        return err;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    // resp err handle
    if (!strncmp(cmd->valuestring, "error", strlen("error"))) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]resp err!\r\n", __func__, __LINE__);

        cJSON *cmd = cJSON_GetObjectItem(root, "errorCode");
        if (cmd && cmd->valuestring) {printf("[%s][%d]\r\n", __func__, __LINE__);
            printf("[%s][%d]errorCode:%s\r\n", __func__, __LINE__, cmd->valuestring);
        }

        cJSON *msg = cJSON_GetObjectItem(root, "errorMsg");
        if (msg && msg->valuestring) {printf("[%s][%d]\r\n", __func__, __LINE__);
            printf("[%s][%d]errorMsg: %s\r\n", __func__, __LINE__, msg->valuestring);
        }printf("[%s][%d]\r\n", __func__, __LINE__);
        cJSON_Delete(root);
        err = -1;
        return err;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    cJSON *output = cJSON_GetObjectItem(root, "output");
    if (!output || !cJSON_IsArray(output)) {printf("[%s][%d]\r\n", __func__, __LINE__);
        printf("[%s][%d]cJSON_GetObjectItem err!\r\n", __func__, __LINE__);
        cJSON_Delete(root);
        err = -1;
        return err;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    cJSON *data;
    char *str = NULL;printf("[%s][%d]\r\n", __func__, __LINE__);
    int str_len = 0;
    cJSON_ArrayForEach(data, output) {
        cJSON *data_str = cJSON_GetObjectItem(data, "data");
        if (data_str && data_str->valuestring) {//printf("[%s][%d]data:%s\r\n", __func__, __LINE__, data_str->valuestring);
            // str = strdup(data_str->valuestring);
            str_len = strlen(data_str->valuestring + 1);
            str = malloc(str_len);
            if (!str) {
                printf("[%s][%d]str err!\r\n", __func__, __LINE__);
                cJSON_Delete(root);
                err = -1;
                return err;
            }
            strncpy(str, data_str->valuestring, str_len);
            //printf("[%s][%d]str: %s\r\n", __func__, __LINE__, str);
        }
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    cJSON_Delete(root);
printf("[%s][%d]\r\n", __func__, __LINE__);

    if (str) {//printf("[%s][%d]str: %s\r\n", __func__, __LINE__, str);
        *out = str;printf("[%s][%d]\r\n", __func__, __LINE__);
    }

printf("[%s][%d]\r\n", __func__, __LINE__);
    return err;
}

int parse_xf_tts_resp_data(const char *in_json_str, const int len, char **out, int *out_len)
{
    if (!in_json_str || !len) {
        printf("[%s][%d]param err!\r\n", __func__, __LINE__);
        return -1;
    }

    int err = 0;

    cJSON *root = cJSON_Parse(in_json_str);
    if (root == NULL) {
        printf("[%s][%d]cJSON_Parse err!\r\n", __func__, __LINE__);
        err = -1;
        return err;
    }

    cJSON *code = cJSON_GetObjectItem(root, "code");
    cJSON *message = cJSON_GetObjectItem(root, "message");
    cJSON *data = cJSON_GetObjectItem(root, "data");

    if (code == NULL || message == NULL || data == NULL) {
        printf("[%s][%d]cJSON_GetObjectItem err!\r\n", __func__, __LINE__);
        cJSON_Delete(root);
        err = -1;
        return err;
    }

    if (code->valueint != 0) {
        printf("[%s][%d]err message: %s!\r\n", __func__, __LINE__, message->valuestring);
        cJSON_Delete(root);
        err = -1;
        return err;
    }

    cJSON *audio = cJSON_GetObjectItem(data, "audio");
    if (audio == NULL) {
        printf("[%s][%d]cJSON_GetObjectItem err!\r\n", __func__, __LINE__);
        cJSON_Delete(root);
        err = -1;
        return err;
    }

    char *out_str = NULL;
    int out_str_len = 0;
    if (audio->valuestring) {
        out_str = (char *)base64_decode((const unsigned char*)audio->valuestring, strlen(audio->valuestring), (size_t)&out_str_len);
        if (!out_str) {
            printf("[%s][%d]base64_decode err!\r\n", __func__, __LINE__);
            cJSON_Delete(root);
            err = -1;
            return err;
        }
    }

    if (out_str) {
        *out = out_str;
        *out_len = out_str_len;
    }

    return err;
}
