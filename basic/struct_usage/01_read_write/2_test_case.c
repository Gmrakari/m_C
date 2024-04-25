#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint8_t dec_type;
    uint8_t start_bits;
} __attribute__((packed)) passwd_t;

typedef struct {
    uint8_t en;
    uint8_t val[5];
} __attribute__((packed)) other_t;

typedef struct {
    passwd_t passwd;
    other_t other;
} __attribute__((packed)) cfg_t;

static cfg_t g_param = {
    .passwd = {0x01, 0x02},
    .other = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05},
};

typedef enum {
    CTLGET_PASSWD = 0,
    CTLSET_PASSWD,
    CTLGET_OTHER,
    CTLSET_OTHER,
    CTLGET_DEFAULT,
} ctl_op_t;

static void read_demo(ctl_op_t type, void *param) {
    // 模拟从某个地方读取数据并将其保存到 param 中
    switch (type)
    {
    case CTLSET_PASSWD:
    {
        *((passwd_t *)param) = g_param.passwd;
        break;
    }
    case CTLGET_OTHER: 
    {
        *((other_t *)param) = g_param.other;
        break;
    }
    default:
        break;
    }
    return ;
}

static void write_demo(ctl_op_t type, void *param) {
    // 模拟将 param 中的数据写入某个地方

    switch (type)
    {
    case CTLSET_PASSWD:
    {
        g_param.passwd = *((passwd_t *)param);
        break;
    }
    case CTLSET_OTHER: 
    {
        g_param.other = *((other_t *)param);
        break;
    }
    
    default:
        break;
    }
}

static void _test_01()
{
    passwd_t passwd_base_pararm;

    // 读取示例
    read_demo(CTLGET_PASSWD, &passwd_base_pararm);
    printf("Dec Type: %d, Start Bits: %d\n", passwd_base_pararm.dec_type, passwd_base_pararm.start_bits);

    passwd_base_pararm.dec_type = 0x03;
    passwd_base_pararm.start_bits = 0x04;

    // 写入示例
    write_demo(CTLSET_PASSWD, &passwd_base_pararm);
    printf("Dec Type: %d, Start Bits: %d\n", passwd_base_pararm.dec_type, passwd_base_pararm.start_bits);

    // 读取示例
    read_demo(CTLGET_PASSWD, &passwd_base_pararm);
    printf("Dec Type: %d, Start Bits: %d\n", passwd_base_pararm.dec_type, passwd_base_pararm.start_bits);


    other_t other;

    // 读取示例
    read_demo(CTLGET_OTHER, &other);
    printf("Dec Type: %d, Start Bits: %d %d %d %d %d\n", other.en, other.val[0], other.val[1], other.val[2], other.val[3], other.val[4]);

    other.en = 0x01;
    other.val[0] = 0x0A;
    other.val[1] = 0x09;
    other.val[2] = 0x08;
    other.val[3] = 0x07;
    other.val[4] = 0x06;

    // 写入示例
    write_demo(CTLSET_OTHER, &other);
    printf("Dec Type: %d, Start Bits: %d %d %d %d %d\n", other.en, other.val[0], other.val[1], other.val[2], other.val[3], other.val[4]);

    // 读取示例
    read_demo(CTLGET_OTHER, &other);
    printf("Dec Type: %d, Start Bits: %d %d %d %d %d\n", other.en, other.val[0], other.val[1], other.val[2], other.val[3], other.val[4]);

}

static void _test_02()
{
    uint16_t a = 0x1000;
    uint16_t b = sizeof(uint16_t);
    printf("%08X\r\n", a - b);
}

int main() {
    _test_02();
    return 0;
}
