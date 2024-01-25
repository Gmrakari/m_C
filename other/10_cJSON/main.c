#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cJSON.h"

static void test_1();

// #usage:
// gcc main.c cJSON.c

static void test_1() 
{
    //1. 创建cJSON对象
    cJSON* root = cJSON_CreateObject();

    //2. 创建数据
    cJSON_AddStringToObject(root, "text","我是一个字符串数据");
    cJSON_AddNumberToObject(root,"number",666);
    cJSON_AddBoolToObject(root, "state1", cJSON_False);
    cJSON_AddBoolToObject(root, "state2", cJSON_True);
    cJSON_AddNullToObject(root, "state3");

    //3. 打印生成的结果
    char *json_data=cJSON_PrintUnformatted(root);
    printf("%s\n",json_data);

    //4. 释放空间
    cJSON_Delete(root);
}

static void test_2() 
{
    char str[] = {"{\"p\":\"vows1jnkpdpaizrk\",\"v\":\"1.0.0\",\"cap\":24}"};
    
    cJSON *obj = cJSON_Parse(str);

    char *unformat_str = cJSON_PrintUnformatted(obj);

    printf("%s\r\n", unformat_str);

    uint8_t *ptr = (uint8_t *)unformat_str;

    for (int i = 0; ptr[i] != '\0'; i++) {
        printf("%02X", ptr[i]);
    }
    printf("\r\n");

    size_t len = sizeof(cJSON);
    printf("len:%ld\r\n", len);
    uint8_t cJSON_bytes_arr[len];

    memcpy(cJSON_bytes_arr, obj, len);
    uint8_t *cJSON_ptr = (uint8_t*)cJSON_bytes_arr;

    for (int i = 0; i < len; i++) {
        printf("%02X", cJSON_ptr[i]);
    }
    printf("\r\n");

    free(unformat_str);

    cJSON_Delete(obj);
}

static void test_3()
{
    const uint8_t buf[] = {0x7B,0x22,0x70,0x22,0x3A,0x22,0x76,0x6F,0x77,0x73,0x31,0x6A,0x6E,0x6B,0x70,0x64,0x70,0x61,0x69,0x7A,0x72,0x6B,0x22,0x2C,0x22,0x76,0x22,0x3A,0x22,0x31,0x2E,0x30,0x2E,0x30,0x22,0x2C,0x22,0x63,0x61,0x70,0x22,0x3A,0x32,0x34,0x7D};
    int len = sizeof(buf) / sizeof(buf[0]);

    printf("%s\r\n", buf);

    uint8_t *data = buf;
    cJSON *obj = cJSON_Parse(data);
    if (!obj) {
        printf("cJSON_Parse err\r\n");
        return ;
    }
 
    cJSON *sub = cJSON_GetObjectItem(obj, "p");
    if (!sub || !sub->valuestring) {
        printf("get cJSON p info err\r\n");
        return ;
    }

    // char str_buf[] = "vows1jnkpdpaizrk";
    char p_value_str[17] = {0};
    strncpy(p_value_str, sub->valuestring, sizeof(p_value_str));
    printf("p_value_str:%s\r\n", p_value_str);

    char v_value_str[9] = {0};
    sub = cJSON_GetObjectItem(obj, "v");
    if (!sub || !sub->valuestring) {
        printf("get cJSON version info err\r\n");
        return ;
    }
    strncpy(v_value_str, sub->valuestring, sizeof(v_value_str));
    printf("v_value_str:%s\r\n", v_value_str);

    uint16_t cap = 0;
    sub = cJSON_GetObjectItem(obj, "cap");
    // if (!sub || !cJSON_IsNumber(sub) || (int)sub->valueint < 0 || (int)sub->valueint > 0XFFFF ) {
    if (!sub || (int)sub->valuedouble < 0 || (int)sub->valuedouble > 0xFFFF ) {
        printf("get cJSON cap info err\r\n");
        return ;
    }
    cap = sub->valuedouble;

    printf("%04X\r\n", cap);

    uint8_t per_bits[10] = {0};

    uint8_t *bit_ptr = (uint8_t*)&cap;

    for (int i = 0; i < 10; i++) {
        per_bits[i] = ((bit_ptr[i / 8] >> (i % 8)) & 0x01);
    }

    for (int i = 0; i < 10; i++) {
        printf("%02X ", per_bits[i]);
    }
    printf("\r\n");

    cJSON_Delete(obj);
}

int main() 
{
    // test_1();

    // test_2();

    test_3();

    return 0;
}