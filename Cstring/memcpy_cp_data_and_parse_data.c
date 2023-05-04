#include <stdio.h>
#include <string.h>
#include <stdint.h> // uint8
#include <stdlib.h>

// typedef struct {
//     uint32_t id;
//     uint32_t number;
// } record_info_t;

typedef struct {
    uint32_t id;
    uint32_t number;
} __attribute__((packed)) record_info_t;

#define DATA_FRAME_SIZE (0xFFFF)

/*
** __attribute__((packed))
** 1. 对结构体进行紧凑排列
** 2. 避免编译器对齐和填充导致的额外空间占用
** 3. 可以确保结构体成员的排列顺序与定义顺序相同，并且成员之间不会有填充字节，从而节省内存空间
** 4. 使用 __attribute__((packed)) 可能会影响结构体成员的访问速度，
**    因为编译器不再对成员进行对齐优化，可能会导致读取成员时需要进行额外的操作。
*/

typedef struct {
    uint16_t head;
    uint16_t len;
    uint16_t check;
    uint8_t cmd;
    // uint8_t data[DATA_FRAME_SIZE - 8];
} ptl_type_t;

/*
typedef struct {
    uint16_t head;
    uint16_t len;
    uint16_t check;
    uint8_t cmd;
    // uint8_t data[DATA_FRAME_SIZE - 8];
} __attribute__((packed)) ptl_type_t;
*/

static void _cp_data(record_info_t *record_info, ptl_type_t *ptl_info, size_t *len, uint8_t *out);
static void _parse_data(uint8_t *in, record_info_t *record_info_out, ptl_type_t *ptl_type_out);

static void _cp_data_test();
static void _test_parse_data();
static void _test();
static void _param_init();

static uint8_t g_record_info_buffer[4 * 2] = {0};
static record_info_t g_s_record_info = {0};
static ptl_type_t g_s_ptl_type = {0};
static uint8_t g_data_buf[4 * 2 + 7] = {0};
static size_t g_data_len = 0;

static void _cp_data(record_info_t *record_info, ptl_type_t *ptl_info, size_t *len, uint8_t *out)
{
    memset(g_data_buf, 0, sizeof(g_data_buf));

    uint8_t *buff = NULL;

    buff = out;

    uint8_t *ptr = buff;
    memcpy(ptr, record_info, sizeof(record_info_t));
    ptr += sizeof(record_info_t);

    memcpy(ptr, ptl_info, sizeof(ptl_info));
    ptr += sizeof(ptl_type_t);

    *len = ptr - buff;

    printf("*len:%d\r\n", (int)*len);
}

static void _record_info_init()
{
    g_s_record_info = (record_info_t){
        .id = 15,
        .number = 30
    };
}

static void _ptl_type_info_init()
{
    g_s_ptl_type = (ptl_type_t) {
        .head = 0x01,
        .len = 0x02,
        .check = 0x03,
        .cmd = 0x04
    };
}

static void _print_record_info(record_info_t *param)
{
    if (param == NULL) return ;

    printf("param->id:%d\r\n", param->id);
    printf("param->number:%d\r\n", param->number);
}

static void _print_ptl_info(ptl_type_t *param)
{
    if (param == NULL) return ;

    printf("param->head:%d\r\n", param->head);
    printf("param->len:%d\r\n", param->len);
    printf("param->check:%d\r\n", param->check);
    printf("param->cmd:%d\r\n", param->cmd);
}

static void _parse_data(uint8_t *in, record_info_t *record_info_out, ptl_type_t *ptl_type_out)
{
    if (in == NULL || record_info_out == NULL || ptl_type_out == NULL)
        return ;

    uint8_t *ptr = NULL;
    ptr = in;

    memcpy(record_info_out, ptr, sizeof(record_info_t));
    ptr += sizeof(record_info_t);

    memcpy(ptl_type_out, ptr, sizeof(ptl_type_t));

    return ;
}

static void _param_init()
{
    _record_info_init();
    _print_record_info(&g_s_record_info);

    printf("\r\n");

    _ptl_type_info_init();
    _print_ptl_info(&g_s_ptl_type);
}

static void _test()
{
    _param_init();
    _cp_data_test();
    _test_parse_data();

}

static void _test_parse_data()
{
    record_info_t parse_record_info = {0};
    ptl_type_t parse_ptl_type_info = {0};

    _parse_data(g_data_buf, &parse_record_info, &parse_ptl_type_info);

    printf("g_data_len:%d\r\n", (int)g_data_len);

    printf("\r\n");

    printf("parse_record_info.id:%d\r\n", parse_record_info.id);
    printf("parse_record_info.number:%d\r\n", parse_record_info.number);

    printf("\r\n");

    printf("parse_ptl_type_info.head:%d\r\n", parse_ptl_type_info.head);
    printf("parse_ptl_type_info.len:%d\r\n", parse_ptl_type_info.len);
    printf("parse_ptl_type_info.check:%d\r\n", parse_ptl_type_info.check);
    printf("parse_ptl_type_info.cmd:%d\r\n", parse_ptl_type_info.cmd);
}

static void _cp_data_test()
{
    printf("sizeof(ptl_type_t):%d\r\n", (int)sizeof(ptl_type_t)); // 
    printf("sizeof(record_info_t):%d\r\n", (int)sizeof(record_info_t));
    printf("g_data_len:%d\r\n", (int)g_data_len);

    _cp_data(&g_s_record_info, &g_s_ptl_type, &g_data_len, g_data_buf);
}

int main()
{
    _test();
    return 0;
}
