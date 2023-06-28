#ifndef __STRUCT_H
#define __STRUCT_H

#include <stdio.h>

// 定义一个struct结构体
struct Person {
    char name[20];
    int age;
};

void struct_app(void);

// // 定义一个union联合体
// union Data {
//     int num;
//     float decimal;
// };

#endif