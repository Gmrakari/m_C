#ifndef _APP_ASR_PASRE_RESP_H
#define _APP_ASR_PARSE_RESP_H

#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
// #include <string.h>

#include "base64.h"

// unsigned char g_resp_json_arr[] = "{\"code\":0,\"message\":\"success\",\"sid\":\"iat000d020a@gz18e8db0451246fa802\",\"data\":{\"result\":{\"sn\":1,\"ls\":false,\"bg\":0,\"ed\":0,\"ws\":[{\"bg\":60,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":116,\"cw\":[{\"sc\":0,\"w\":\"听写\"}]},{\"bg\":204,\"cw\":[{\"sc\":0,\"w\":\"可以\"}]},{\"bg\":248,\"cw\":[{\"sc\":0,\"w\":\"将\"}]},{\"bg\":284,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":324,\"cw\":[{\"sc\":0,\"w\":\"转为\"}]},{\"cw\":[{\"w\":\"文字\",\"sc\":0}],\"bg\":376}]},\"status\":0}}";
// unsigned int g_resp_json_arr_len = sizeof(g_resp_json_arr) / sizeof(g_resp_json_arr[0]);

int app_asr_parse_resp(const char *src, const int len, char **out);

int parse_normal_chat_resp_data(const char *in_json_str, const int len, char **out);

int parse_xf_tts_resp_data(const char *in_json_str, const int len, char **out, int *out_len);

#endif // 