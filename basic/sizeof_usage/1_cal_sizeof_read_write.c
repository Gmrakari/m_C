#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t *str;
    size_t len;
} strtype_t;

typedef struct {
    uint8_t camera_support                  : 1;
    uint8_t image_upload_via_spi            : 1;
    uint8_t reserved_2                      : 1;
    uint8_t reset_notify_required           : 1;
    uint8_t firmware_upgrade_support        : 1;
    uint8_t deep_sleep_impl_mcu             : 1;
    uint8_t reserved_6                      : 1;
    uint8_t reserved_7                      : 1;
    uint8_t screen_sleep_control_via_serial : 1;
    uint8_t default_into_network_mode       : 1;
} device_cap_t;

typedef struct {
    strtype_t *str;
    device_cap_t dev_cap;
} data_info;

typedef union {
    struct {
        uint16_t cam_support         : 1;
        uint16_t img_upload          : 1;
        uint16_t reserved_2          : 1;
        uint16_t reset_notify        : 1;
        uint16_t fw_auto_update      : 1;
        uint16_t deep_sleep_impl     : 1;
        uint16_t reserved_6_7        : 2;
        uint16_t scr_sleep_ctrl      : 1;
        uint16_t into_net_mode       : 1;
    } b;                                
    uint16_t w;                         
} dev_cap_type_t;

typedef struct {
    uint16_t cap : 9;
} dev_cap_info_t;

static void read_test2(dev_cap_info_t *info);
static void write_test2(dev_cap_info_t *info);

void test()
{
    printf("sizeof(data_info):%ld\r\n", sizeof(data_info));
    printf("sizeof(device_cap_t):%ld\r\n", sizeof(device_cap_t));

    printf("sizeof(data_info) - sizeof(device_cap_t):%ld\r\n", sizeof(data_info) - sizeof(device_cap_t));
}

static void print_bits(uint16_t value, uint8_t *arr) {
    int arr_cnt = 0;

    #if 0
    for (int i = 8; i >= 0; --i) {
        int bit_value = (value >> i) & 1;
        printf("bits: %d value: %d\r\n", i, bit_value);
        arr[arr_cnt++] = bit_value;
    }
    #endif

    for (int i = 0; i <= 8; ++i) {
        int bit_value = (value >> i) & 1;
        printf("bits: %d value: %d\r\n", i + 1, bit_value);
        arr[arr_cnt++] = bit_value;
    }

    printf("\n");
}

static void dev_cap_type_read(dev_cap_type_t *info)
{
    if (!info) return ;

    printf("%02X, %d\r\n", info->w, info->w);
}

static void dev_cap_type_write(dev_cap_type_t *info)
{
    if (!info) return ;

    info->w = 24;

}

void test1()
{
    dev_cap_info_t cap_info = {0};

    printf("%ld\r\n", sizeof(dev_cap_info_t));

    write_test2(&cap_info);

    read_test2(&cap_info);
}

void test2()
{
    dev_cap_type_t info = {0};

    dev_cap_type_read(&info);

    dev_cap_type_write(&info);

    dev_cap_type_read(&info);

    uint16_t value = 24;

    if (memcmp(&value, &info.w, sizeof(uint16_t)) == 0) {
        printf("same value\r\n");
    } else {
        printf("different value\r\n");
    }
}

static void read_test2(dev_cap_info_t *info)
{
    int i = 0;
    uint8_t bits_values[9] = {0};

    print_bits(info->cap, bits_values);

    for (int i = 0; i < sizeof(bits_values); i++) {
        printf("bits : %d value : %d\r\n", i + 1, bits_values[i]);
    }
}

static void write_test2(dev_cap_info_t *info)
{
    if (!info) return;

    info->cap = 24; // 二进制表示，仅示例

    // info->cap = 0b100011000;

    // 获取cap只占用9位的值
    // uint16_t cap_value = info->cap & 0x1FF;

    // uint8_t value = (cap_value << 8 | cap_value >> 8);

    // 打印获取的值
    // printf("cap_value: %02X %d\n", cap_value, cap_value);
    // printf("value: %02X %d\n", value, value);
}

int main()
{
    test2();
}
