#include <stdio.h>
#include <string.h>
#include "struct.h"

typedef struct Person Person_t;

static Person_t g_s_person;

void struct_app()
{
    // 创建并初始化struct结构体
    // struct Person person;
    strcpy(g_s_person.name, "John");
    g_s_person.age = 30;

    // // 创建并初始化union联合体
    // union Data data;
    // data.num = 10;

    // // 在union联合体中赋值新的数据
    // data.decimal = 3.14;

    // 输出struct结构体的成员变量
    printf("Person: name = %s, age = %d\n", g_s_person.name, g_s_person.age);

    // 输出union联合体的成员变量
    // printf("Data: num = %d, decimal = %.2f\n", data.num, data.decimal);
}