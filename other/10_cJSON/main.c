#include <stdio.h>

#include "cJSON.h"

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

int main() 
{
    test_1();
    return 0;
}