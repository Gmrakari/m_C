#include <stdio.h>
#include <string.h>
#include "struct.h"
#include <stdint.h>

// 定义一个struct结构体
typedef struct _tag_person_t{
    char name[20];
    int age;
} tag_person_t;

// 定义一个union联合体
union tag_data_t {
    int num;
    float decimal;
};

union dataPackage {
    int num;
    float score;
    char name[20];
};

typedef struct {
    int dataType;
    union dataPackage data_package;
} tag_info_t;

typedef struct {
    int type;
    union {
        int num_value;
        float score_value;
        char name_value[20];
    } data;
} union_info_t;

typedef struct fw_header {
    union {
        struct {
            uint8_t header[16];

            uint8_t type[4];        // RAW or XZ
            uint32_t len;           // body len
            uint8_t pad0[8];

            uint8_t ver_hardware[16];
            uint8_t ver_software[16];

            uint8_t sha256[32];
        } s;
        uint8_t _pad[512];
    } u;
} fw_header_t;

void struct_app()
{
    // 创建并初始化struct结构体
    tag_person_t person;
    strcpy(person.name, "John");
    person.age = 30;

    // 输出struct结构体的成员变量
    printf("Person: name = %s, age = %d\n", person.name, person.age);
}

void union_app()
{
    // 创建并初始化union联合体
    union tag_data_t data;
    data.num = 10;

    // 在union联合体中赋值新的数据
    data.decimal = 3.14;

    // 输出union联合体的成员变量
    printf("Data: num = %d, decimal = %.2f\n", data.num, data.decimal);
}

void union_in_struct_app()
{
    tag_info_t info = {0};
    int value = 2;
    info.dataType = 1;
    info.data_package.num = value;

    printf("info.data_package.num : %d\r\n", info.data_package.num);
    printf("info.data_package.score : %f\r\n", info.data_package.score);
    printf("info.data_package.name : %s\r\n", info.data_package.name);
}

void struct_in_union_app(void)
{
    union_info_t info = {0};
    int value = 2;

    info.type = 1;

    switch(info.type) {
        case 1:
            info.data.num_value = value;
            break;
        case 2:
            info.data.score_value = 3.14f;
            break;
        case 3:
            snprintf(info.data.name_value, sizeof(info.data.name_value), "Baker Gmrakari"); 
            break;
        default:
            break;
    }

    switch (info.type)
    {
    case 1:
        printf("info.data.num_value:%d\r\n", info.data.num_value);
        break;
    case 2:
        printf("info.data.score_value:%f\r\n", info.data.score_value);
        break;
    case 3:
        printf("info.data.name_value:%s\r\n", info.data.name_value);
        break;
    default:
        break;
    }
}

// 读取数据
static void read_fw_header(const fw_header_t *header) {
    if (header == NULL) {
        printf("Invalid header pointer\n");
        return;
    }

    // 读取结构体数据
    printf("Header: %s\n", header->u.s.header);
    printf("Type: %s\n", header->u.s.type);
    printf("Length: %u\n", header->u.s.len);
    printf("Hardware Version: %s\n", header->u.s.ver_hardware);
    printf("Software Version: %s\n", header->u.s.ver_software);
    printf("SHA256: %s\n", header->u.s.sha256);
}

// 写入数据
static void write_fw_header(fw_header_t *header) {
    if (header == NULL) {
        printf("Invalid header pointer\n");
        return;
    }

    // 设置结构体数据
    strcpy((char *)header->u.s.header, "OTA Header");
    strcpy((char *)header->u.s.type, "XZ");
    header->u.s.len = 1024;
    strcpy((char *)header->u.s.ver_hardware, "HW Version");
    strcpy((char *)header->u.s.ver_software, "SW Version");
    strcpy((char *)header->u.s.sha256, "ABCDEF1234567890");
}

void struct_in_union_app_in_project_demo()
{
    fw_header_t header;

    printf("Before Header:\n");
    read_fw_header(&header);

    // 写入数据
    write_fw_header(&header);

    // 打印写入后的数据
    printf("Written Header:\n");
    read_fw_header(&header);
}