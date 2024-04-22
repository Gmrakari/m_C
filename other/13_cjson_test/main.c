#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cJSON.h"

#include "app_cjson_test.h"

#include "app_asr_parse_resp.h"

#include "base64.h"

static void test_1()
{
    int appid_len = 4;
    char *appid = malloc(appid_len);
    if (!appid) {
        printf("malloc err\r\n");
        return ;
    }
    memset(appid, 0x00, appid_len);
    char a[] = "abc";
    strncpy(appid, a, appid_len);
    asr_common_param_t comm = {
        .appid = appid,
        .appid_len = appid_len
    };

    cJSON *comm_json = asr_generate_common_param(&comm);
    if (!comm_json) {
        printf("comm_json is null");
        if (comm.appid) {
            free(comm.appid);
            comm.appid = NULL;
        }
        return ;
    }

    if (comm.appid) {
        free(comm.appid);
        comm.appid = NULL;
    }

    char *comm_json_format_data = cJSON_PrintUnformatted(comm_json);
    if (comm_json_format_data) {
        printf("comm_json_format_data:%s\r\n", comm_json_format_data);
        free(comm_json_format_data);
        comm_json_format_data = NULL;
        cJSON_Delete(comm_json);
    }

    asr_business_param_t business = {
        .language = "en",
        .domain = "test_doma",
        .accent = "cnn",
        .vad_eos = 1,
        .dwa = "dwa_v",
        .pd = "pd_v",
        .ptt = 2,
        .rlang = "rlan_v",
        .vinfo = 3,
        .nunum = 4,
        .speex_size = 5,
        .nbest = 6,
        .wbest = 7
    };

    cJSON *business_json = asr_generate_business_param(&business);
    if (!business_json) {
        printf("business_json is null");
        cJSON_Delete(comm_json);
        return ;
    }

    char *business_json_format_data = cJSON_PrintUnformatted(business_json);
    if (business_json_format_data) {
        printf("business_json_format_data:%s\r\n", business_json_format_data);
        free(business_json_format_data);
        business_json_format_data = NULL;
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
    }

    int audio_data_base64_len = 10;
    char *audio_data_base64 = malloc(audio_data_base64_len);
    if (!audio_data_base64) {
        printf("malloc err\r\n");
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
        return ;
    }
    memset(audio_data_base64, 0x00, audio_data_base64_len);

    char a_audio_data_base64[] = "base64";
    strncpy(audio_data_base64, a_audio_data_base64, audio_data_base64_len);

    asr_data_param_t data = {
        .status = 1,
        .format = "abc1",
        .encode = "enc",
        .audio = NULL,
    };

    data.audio_len = audio_data_base64_len;
    data.audio = malloc(data.audio_len);
    if (!data.audio) {
        free(audio_data_base64);
        audio_data_base64 = NULL;
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
    }
    memset(data.audio, 0x00, data.audio_len);
    memcpy(data.audio, audio_data_base64, data.audio_len);

    if (audio_data_base64) {
        free(audio_data_base64);
        audio_data_base64 = NULL;
    }

    cJSON* data_json = asr_generate_data_param(&data);
    if (!data_json) {
        printf("data_json is null");

        if (data.audio) {
            free(data.audio);
            data.audio = NULL;
        }
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
        return ;
    }

    if (data.audio) {
        free(data.audio);
        data.audio = NULL;
    }

    char *data_json_format_data = cJSON_PrintUnformatted(data_json);
    if (data_json_format_data) {
        printf("data_json_format_data:%s\r\n", data_json_format_data);
        free(data_json_format_data);
        data_json_format_data = NULL;
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
        cJSON_Delete(data_json);
    }

    cJSON *root = asr_generate_root(comm_json, business_json, data_json);
    if (!root) {
        cJSON_Delete(comm_json);
        cJSON_Delete(business_json);
        cJSON_Delete(data_json);
    }

    cJSON_Delete(comm_json);
    cJSON_Delete(business_json);
    cJSON_Delete(data_json);

    char *print_str_data = cJSON_PrintUnformatted(root);
    if (print_str_data == NULL) {
        cJSON_Delete(root);
    }

    printf("print_str_data:%s\r\n", print_str_data);

    cJSON_Delete(root);

    if (print_str_data) {
        free(print_str_data);
        print_str_data = NULL;
    }
}

static int _gen_request_root(cJSON *root, const char *name, cJSON *sub)
{
    if (!root || !sub) {
        printf("_gen_request_root err!\r\n");
        return -1;
    }

    cJSON_AddItemToObject(root, name, sub);

    return 0;
}

static void test_2()
{
    //1. 创建cJSON对象
    cJSON* root = cJSON_CreateObject();

    //2. 创建数据
    cJSON_AddStringToObject(root, "text","test_val");
    cJSON_AddNumberToObject(root,"number",666);
    cJSON_AddBoolToObject(root, "state1", cJSON_False);
    cJSON_AddBoolToObject(root, "state2", cJSON_True);
    // cJSON_AddNullToObject(root, "state3");

    cJSON* sub = cJSON_CreateObject();
    cJSON_AddStringToObject(sub, "text","abc");

    const char sub_name[] = "sub";
    _gen_request_root(root, sub_name, sub);

    // cJSON_Delete(sub);

    //3. 打印生成的结果
    char *json_data=cJSON_PrintUnformatted(root);
    printf("%s\n",json_data);

    if (json_data) {
        free(json_data);
        json_data = NULL;
    }

    //4. 释放空间
    cJSON_Delete(root);
}

static int test_3()
{
    // static char arr_val[] = "";
    // char *ptr = &arr_val;
    // 

    // if (ptr) {
    //     free(ptr);
    //     ptr = NULL;
    // }
    // 


    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int len = sizeof(arr) / sizeof(arr[0]);
    printf("\r\n");
    for (int i = 0; i < (int)(sizeof(arr) / sizeof(arr[0])); i++) {
        printf("%02X", arr[i]);
        if ((i ^ (len - 1))) {
            printf(" ");
        }
    }
printf("\r\n");
    int *ptr = malloc(sizeof(int) * len);
    memcpy(ptr, arr + 2, sizeof(int) * (len - 2));
    for (int i = 0; i < (int)(sizeof(arr) / sizeof(arr[0])); i++) {
        printf("%02X", ptr[i]);
        if ((i ^ (len - 1))) {
            printf(" ");
        }
    }

    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
    printf("\r\n");
}

static void _test_4()
{
    char buff[] = "{\"code\":0,\"message\":\"success\",\"sid\":\"iat000e2806@gz18e611ba2de46fd802\",\"data\":{\"result\":{\"ed\":0,\"ws\":[{\"bg\":60,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":116,\"cw\":[{\"sc\":0,\"w\":\"听写\"}]},{\"bg\":204,\"cw\":[{\"sc\":0,\"w\":\"可以\"}]},{\"bg\":248,\"cw\":[{\"sc\":0,\"w\":\"将\"}]},{\"bg\":284,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":324,\"cw\":[{\"sc\":0,\"w\":\"转为\"}]},{\"bg\":376,\"cw\":[{\"sc\":0,\"w\":\"文字\"}]}],\"sn\":1,\"ls\":false,\"bg\":0},\"status\":0}}";
    printf("buf:%s\r\n", buff);

    cJSON *obj = cJSON_Parse(buff);
    if (obj == NULL) {
        printf("parse err!\r\n");
        return ;
    }

    cJSON *ws = cJSON_GetObjectItem(obj, "data");

    char cn_buff[1024] = {0};

    int i = 0;
    for (i = 0; i < cJSON_GetArraySize(ws); i++) {
        cJSON *item = cJSON_GetArrayItem(ws, i);
        if (item) {
            char *format_item = cJSON_PrintUnformatted(item);
            if (format_item) {
                printf("format_item:%s\r\n", format_item);
                free(format_item);
                format_item = NULL;
            }
        }

        const char *w = cJSON_GetObjectItem(item, "w")->valuestring;
        printf("w:%s\r\n", w);
        if (w) {
            strcat(cn_buff, w);
        }
    }

    printf("cn_buf:%s\r\n", cn_buff);
    cJSON_Delete(obj);
    return ;
}

typedef enum {
    FIELD_TYPE_NUMBER = 0,
    FIELD_TYPE_STRING,
} field_type_t;

typedef cJSON* (*json_adder_func)(cJSON*, const char*, void*);

json_adder_func adders[] = {
    (json_adder_func)cJSON_AddNumberToObject,
    (json_adder_func)cJSON_AddStringToObject,
};

cJSON* create_json_obj(const char* filed_name[], void* field_values[], field_type_t field_types[], int num_fields)
{
    if (!filed_name || !field_values || !field_types || num_fields <= 0) 
        return NULL;

    cJSON *obj = cJSON_CreateObject();
    if (!obj)
        return NULL;

    cJSON *err;
    for (int i = 0;i < num_fields; i++) {
        err = adders[field_types[i]](obj, filed_name[i], field_values[i]);
        if (err == NULL) {
            printf("addres add err!\r\n");
        }
    }

    return obj;
}

static void _test_5()
{
    const char* field_names[] = {"age", "name", "is_student"};
    void* field_values[] = {(void*)25, (void*)"john", (void*)1};
    field_type_t field_types[] = {FIELD_TYPE_NUMBER, FIELD_TYPE_STRING, FIELD_TYPE_NUMBER};
    int num_field = sizeof(field_names) / sizeof(field_names[0]);

    cJSON *obj = create_json_obj(field_names, field_values, field_types, num_field);
    if (obj) {
        char *json_string = cJSON_Print(obj);
        if (json_string) {
            printf("json_string:%s\r\n", json_string);
            free(json_string);
            json_string = NULL;
        }
        cJSON_Delete(obj);
    }
    return ;
}

#include <stdbool.h>
static int _test_6()
{
    // 创建一个 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 添加字符串键值对
    cJSON_AddStringToObject(root, "cmd", "request");
    cJSON_AddStringToObject(root, "gen_type", "chat");
    cJSON_AddStringToObject(root, "mode", "gemini-pro");

    // 添加布尔值键值对
    cJSON_AddBoolToObject(root, "stream", true);

    // 创建一个 JSON 数组
    cJSON *input_array = cJSON_CreateArray();

    // 添加文本输入对象到数组
    cJSON *text_input = cJSON_CreateObject();
    cJSON_AddStringToObject(text_input, "type", "text");
    cJSON_AddStringToObject(text_input, "data", "abc");
    cJSON_AddItemToArray(input_array, text_input);

    // 添加图片输入对象到数组
    cJSON *image_input = cJSON_CreateObject();
    cJSON_AddStringToObject(image_input, "type", "image");
    cJSON_AddStringToObject(image_input, "data", "");
    cJSON_AddStringToObject(image_input, "inlineText", "");
    cJSON_AddItemToArray(input_array, image_input);

    // 将数组添加到根对象
    cJSON_AddItemToObject(root, "input", input_array);

    // 生成 JSON 字符串
    char *json_str = cJSON_Print(root);

    // 打印 JSON 字符串
    printf("%s\n", json_str);

    // 释放 JSON 内存
    cJSON_Delete(root);
    free(json_str);    
}

static int _test_7()
{
    char buf[10] = {0};
    int idx = 0;

    char value[] = "abc";
    int ret = 0;
    ret = snprintf(buf, sizeof(buf), "123%s", value);
    printf("ret:%d\r\n", ret);

    char *ml_buf = malloc(sizeof(char) * (ret + 1));
    if (!ml_buf) {
        return 0;
    }

    memset(ml_buf, 0x00, sizeof(char) * (ret + 1));
    // memcpy(ml_buf, buf, sizeof(char) * (ret + 1));
    strncpy(ml_buf, buf, ret);
    printf("ml_buf:%s\r\n", ml_buf);

    if (ml_buf) {
        free(ml_buf);
        ml_buf = NULL;
    }
}

static void _test_08()
{
    cJSON_bool val = 0;
    cJSON* json = cJSON_CreateObject();
    cJSON* sub = cJSON_CreateBool(val);

    cJSON_AddItemToObject(json, "val", sub);

    char *ptr = cJSON_PrintUnformatted(json);
    if (ptr) {
        printf("ptr:%s\r\n", ptr);
        free(ptr);
        ptr = NULL;
        cJSON_Delete(json);
    }

}

static int _filt_word(const char* str, const int len)
{
    if (!str)
        return -1;

    char *ptr = malloc(len);
    if (!ptr)
        return -1;

    memset(ptr, 0x00, len);
    int cnt = 0;
    while (*str++ != '\0') {
        if (*str == '`' && *(str+1) == '`' && *(str + 2) == '`') {
            str += 3;
            while (1) {
                if (*str == '`' && *(str + 1) == '`' && *(str + 2) == '`')
                {
                    str += 3;
                    break;
                }
                str++;
            }
        }
        if (*str != '*' && *str != '\n' && *str != ' ') 
            ptr[cnt++] = *str;

    }

    ptr[cnt] = '\0';
    printf("conver ptr: %s\r\n", ptr);

    free(ptr);
    ptr = NULL;

    return 0;
}

static int _filt_word2(const char* str, const int len, char* out_str) {
    if (!str || !out_str)
        return -1;

    int in_code_block = 0;
    int out_idx = 0;

    while (*str != '\0') {
        if (*str == '`' && *(str + 1) == '`' && *(str + 2) == '`') {
            in_code_block = !in_code_block;
            str += 3;
            continue;
        }

        if (!in_code_block && *str != '*' && *str != '\n' && *str != ' ')
            out_str[out_idx++] = *str;

        str++;
    }

    out_str[out_idx] = '\0';

    return 0;
}

static int _filt_word_3(char* str) {
    if (!str)
        return -1;

    int in_code_block = 0;
    int str_idx = 0;

    while (*str != '\0') {
        if (*str == '`' && *(str + 1) == '`' && *(str + 2) == '`') {
            in_code_block = !in_code_block;
            str += 3;
            continue;
        }

        if (!in_code_block) {
            str[str_idx++] = *str;
        }

        str++;
    }

    str[str_idx] = '\0';

    return 0;
}

static int _filt_word_4(char* str) {
    if (!str)
        return -1;

    int in_code_block = 0;
    int str_idx = 0;

    while (*str++ != '\0') {
        if (*str == '`' && *(str + 1) == '`' && *(str + 2) == '`') {
            in_code_block = !in_code_block;
            str += 3;
            continue;
        }

        if (!in_code_block) {
            // 判断是否是中文
            if (*str >= 0x80) {
                // 中文字符需要判断两个字节
                if (*(str + 1) >= 0x80) {
                    str_idx += 2;
                    str += 2;
                } else {
                    // 只包含一个字节的中文字符，视为非法字符
                    return -1;
                }
            } else {
                // 英文或其他非中文字符
                str_idx++;
                str++;
            }
        }
    }

    str[str_idx] = '\0';

    return 0;
}

static int test_09()
{
    char buf[] = "**实现语音转文字的步骤：**\n\n1. **选择语音识别引擎：**选择一个满足您需求的引擎，例如 Google Cloud Speech-to-Text、Amazon Transcribe 或 Microsoft Azure Speech-to-Text。\n2. **集成语音识别引擎：**按照引擎提供的文档将其集成到您的应用程序中。这通常涉及设置凭据和配置 API 调用。\n3. **准备音频文件：**确保音频文件格式符合引擎支持的格式（例如 WAV、MP3）。\n4. **发送音频数据：**使用引擎提供的 API 将音频文件发送到语音识别引擎。\n5. **处理识别结果：**引擎将返回识别的文本。解析并显示或存储此文本。\n6. **优化：**根据需要，调整引擎参数或优化音频质量以提高准确性。\n\n**示例代码（使用 C# 和 Google Cloud Speech-to-Text API）：**\n\n```csharp\nusing Google.Cloud.Speech.V1;\n\n// 创建语音识别客户端\nvar client = SpeechClient.Create();\n\n// 打开音频文件\nvar audio = File.ReadAllBytes(\"audio.wav\");\n\n// 发送音频数据到 Speech-to-Text\nvar response = client.Recognize(new RecognizeRequest\n{\n    Config = new RecognitionConfig\n    {\n        Encoding = AudioEncoding.Linear16,\n        SampleRateHertz = 16000,\n        LanguageCode = \"en-US\"\n    },\n    Audio = new RecognitionAudio { Content = Google.Protobuf.ByteString.CopyFrom(audio) }\n});\n\n// 打印识别的文本\nforeach (var result in response.Results)\n{\n    foreach (var alternative in result.Alternatives)\n    {\n        Console.WriteLine(alternative.Transcript);\n    }\n}\n```\n\n**提示：**\n\n* 使用高质量音频可以提高识别精度。\n* 考虑使用语言模型以提高特定语言的精度。\n* 校对语音转文字输出，因为它可能包含错误。";

    // printf("buf:%s\r\n", buf);

    // char buf[] = ":```csharpusing Google.Cloud.Speech.V1;t);    }}```prot";

    // _filt_word(buf, sizeof(buf));
    // printf("buf:%s\r\n", buf);

    printf("\r\n\r\n");
#if 0
    char *ptr = malloc(sizeof(buf));
    memset(ptr, 0x00, sizeof(buf));
    _filt_word2(buf, sizeof(buf), ptr);

    printf("ptr:%s\r\n", ptr);
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }
#endif

    _filt_word_4(buf);
    printf("buf:%s\r\n", buf);

}

#define DEFAULT "https://www.baidu.com"

static int test_10()
{
    // char buf[100];
    int url_len = 100;
    char *url = malloc(url_len);
    if (!url) {
        return 0;
    }
    memset(url, 0x00, url_len);

    char buf[] = "signpath";
    
    snprintf(url, url_len, "host: "DEFAULT"'\n'date:%s", buf);

    printf("url:%s\r\n", url);

    free(url);
    url = NULL;

    int err = 0;
    char api_key[] = "api_key__abc";
    int signature_base64_len = 100;
    char *signature_base64 = malloc(signature_base64_len);
    char signature_base64_buf[] = "signature_base64==1231";
    strncpy(signature_base64, signature_base64_buf, signature_base64_len);
    signature_base64[signature_base64_len - 1] = '\0';

    int authorization_len = strlen("api_key=") + strlen("\"") + strlen(api_key) + strlen("\", ")
                          + strlen("algorithm=\"hmac-sha256\"") + strlen("\", ")
                          + strlen("headers=\"host date request-line\"") + strlen("\", ")
                          + strlen("signature=\"") + strlen(signature_base64) + strlen("\"") + 1;

    char *authorization = malloc(authorization_len);
    if (!authorization) {
        printf("[%s][%d]authorization malloc err!\r\n", __func__, __LINE__);
        if (signature_base64) {
            free(signature_base64);
            signature_base64 = NULL;
        }
        err = -1;
        return err;
    }

    snprintf(authorization, authorization_len, 
            "api_key=\"%s\", algorithm=\"hmac-sha256\", headers=\"host date request-line\", signature=\"%s\"", 
            api_key, signature_base64);

    printf("[%s][%d]authorization: %s\r\n", __func__, __LINE__, authorization);

    if (authorization) {
        free(authorization);
        authorization = NULL;
    }

    return 0;
}

typedef enum {
    ENUM_TASK_VAL = 0x01,
    ENUM_TASK_VAL_2 = 0x02,
    ENUM_TASK_VAL_3 = 0x03,
    ENUM_TASK_VAL_4 = ENUM_TASK_VAL_2 | ENUM_TASK_VAL_3,
} enum_task_val_t;

#define XF_TTS_API_KEY               "1436723e155d4e3a636bc2c1306bd3e0"

// extern unsigned char g_resp_json_arr[];

unsigned char g_resp_json_arr[] = "{\"code\":0,\"message\":\"success\",\"sid\":\"iat000d020a@gz18e8db0451246fa802\",\"data\":{\"result\":{\"sn\":1,\"ls\":false,\"bg\":0,\"ed\":0,\"ws\":[{\"bg\":60,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":116,\"cw\":[{\"sc\":0,\"w\":\"听写\"}]},{\"bg\":204,\"cw\":[{\"sc\":0,\"w\":\"可以\"}]},{\"bg\":248,\"cw\":[{\"sc\":0,\"w\":\"将\"}]},{\"bg\":284,\"cw\":[{\"sc\":0,\"w\":\"语音\"}]},{\"bg\":324,\"cw\":[{\"sc\":0,\"w\":\"转为\"}]},{\"cw\":[{\"w\":\"文字\",\"sc\":0}],\"bg\":376}]},\"status\":0}}";
unsigned int g_resp_json_arr_len = sizeof(g_resp_json_arr) / sizeof(g_resp_json_arr[0]);

static int test_11()
{
    int err = 0;

    char *str = g_resp_json_arr;
    int len = g_resp_json_arr_len;

    char *out = NULL;
    err = app_asr_parse_resp(str, len, &out);
    if (err != 0) {
        printf("[%s][%d]app_asr_parse_resp err!\r\n", __func__, __LINE__);
        return err;
    }

    return err;
}


static int test_12()
{
    int err = 0;

    char *str = g_resp_chat_arr;
    int len = g_resp_chat_arr_len;

    char *out = NULL;
    err = parse_normal_chat_resp_data(str, len, &out);
    if (err != 0) {
        printf("[%s][%d]parse_normal_chat_resp_data err!\r\n", __func__, __LINE__);

        // if (out) {
        //     free(out);
        //     out = NULL;
        // }
        return err;
    }

    if (out) {
        // printf("out: %s\r\n", out);
        free(out);
        out = NULL;
    }

    return err;
}

unsigned char g_resp_tts_arr[] = "{\"code\":0,\"message\":\"success\",\"sid\":\"tts00047027902\",\"data\":{\"audio\":\"/////AAAAAPAAA\",\"status\":1,\"ced\":\"27\"}}";
unsigned int g_resp_tts_arr_len = sizeof(g_resp_tts_arr) / sizeof(g_resp_tts_arr[0]);

static int test_13()
{
    int err = 0;

    char *str = g_resp_tts_arr;
    int len = g_resp_tts_arr_len;

    char *out = NULL;
    int out_len = 0;
    err = parse_xf_tts_resp_data(str, len, &out, &out_len);
    if (err != 0) {
        printf("[%s][%d]parse_xf_tts_resp_data err!\r\n", __func__, __LINE__);

        // if (out) {
        //     free(out);
        //     out = NULL;
        // }
        return err;
    }

    if (out) {
        printf("out_len: %d\r\n", out_len);
        unsigned char *ptr = out;
        
        for (int i = 0; i < out_len; i++) {
            printf("%02X", ptr[i]);
            if (i ^ (out_len - 1)) 
                printf(" ");
        }
        printf("\r\n");
        
        free(out);
        out = NULL;
    }

    return err;  
}

// #usage:
// gcc main.c cJSON.c

unsigned char g_base64_data[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

unsigned int g_base64_data_len = sizeof(g_base64_data) / sizeof(g_base64_data[0]);

static int _test_14()
{
    int err = 0;

    // unsigned char *ptr = NULL;

    unsigned char *str = NULL;
    unsigned int str_len = 0;
    unsigned int base64_ptr_len = 0;

    unsigned char *base64_ptr = NULL;

    base64_ptr = g_base64_data;
    base64_ptr_len = g_base64_data_len;

    str = base64_decode(base64_ptr, base64_ptr_len, &str_len);

    char output_filename[] = "01_audio.pcm";
    if (str) {

        // for (int i = 0; i < str_len; i++) {
        //     printf("%02X", )
        // }

        FILE *fp = fopen(output_filename, "wb+");
        if (fp) { 
            fwrite(str, 1, str_len, fp);
            fclose(fp);
        }

        free(str);
        str = NULL;
    }


    return 0;
}

#include "main.h"
static int _test_15()
{
    int err = 0;

    // unsigned char *ptr = NULL;

    unsigned char *str = NULL;
    unsigned int str_len = 0;
    unsigned int base64_ptr_len = 0;

    unsigned char *base64_ptr = NULL;

    // base64_ptr = g_base64_data_2;
    // base64_ptr_len = g_base64_data_2_len;

    // base64_ptr = g_base64_data_3;
    // base64_ptr_len = g_base64_data_3_len;


    base64_ptr = g_base64_data_4;
    base64_ptr_len = g_base64_data_4_len;


    str = base64_decode(base64_ptr, base64_ptr_len, &str_len);

    // char output_filename[] = "02_audio.pcm";
    char output_filename[] = "04_audio.pcm";
    if (str) {
        FILE *fp = fopen(output_filename, "wb+");
        if (fp) { 
            fwrite(str, 1, str_len, fp);
            fclose(fp);
        }

        free(str);
        str = NULL;
    }

    return 0;
}

static int _test_16()
{
    int err = 0;

    unsigned char *ptr = NULL;
    size_t ptr_len = 0;

    extern unsigned char g_05_todo_parse_base64_to_data[];
    extern unsigned int g_05_todo_parse_base64_to_data_len;

    ptr = base64_decode(g_05_todo_parse_base64_to_data, g_05_todo_parse_base64_to_data_len, &ptr_len);
    if (!ptr)
        return -1;

    char output_filename[] = "05_audio.pcm";
    

    FILE *fp = fopen(output_filename, "wb+");
    if (fp) { 
        fwrite(ptr, 1, ptr_len, fp);
        fclose(fp);
    }

    if (ptr) {
        free(ptr);
        ptr = NULL;
    }

    return 0;
}

int main() 
{
    // test_1();

    // test_2();

    // test_3();

    // _test_4();

    // _test_5();

    unsigned char index = 0;

    printf("index:%d\r\n", index);

    // _test_6();

    // _test_7();

    // _test_08();

    // test_09();

    // test_10();

    // enum_task_val_t val = ENUM_TASK_VAL;

    // val = ENUM_TASK_VAL_4;

    // printf("val:%d\r\n", val);

    // int len = (int)strlen(XF_TTS_API_KEY);
    // printf("len:%d\r\n", len);

    // test_11();

    // test_12();

    // test_13();

    // _test_14();

    // _test_15();

    _test_16();

    return 0;
}
