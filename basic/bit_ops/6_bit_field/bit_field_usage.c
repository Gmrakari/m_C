#include <stdio.h>
#include <stdint.h>

typedef enum {
    CAMERA_SUPPORT = 0,
    IMAGE_UPLOAD_VIA_SPI,
    RESERVED_2,
    RESET_NOTIFY_REQUIRED,
    FIRMWARE_UPGRADE,
    DEEP_SLEEP_IMPL_MCU,
    RESERVED_6,
    RESERVED_7,
    SCREEN_SLEEP_CONTROL_VIA_SERIAL,
    DEFAULT_INTO_NETWORK_MODE,
    OP_TYPE_MAX
} uratp_info_op_type_t;

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
} DeviceCapability_t;

typedef struct {
    unsigned int magic_header;
    DeviceCapability_t dev_cap;
} GmInFo_t;

typedef enum {
    CTLGET_MAGIC_HEADER,
    CTLGET_CAMERA_SUPPORT,
    CTLSET_CAMERA_SUPPORT,
} uartp_control_type_t;

static int read_info(GmInFo_t *param);
static int write_info(GmInFo_t *param);
static int cmd_info(int cmd, ...);

static GmInFo_t info = {.magic_header = 0x9529, .dev_cap = {0}};

static void test()
{
    write_info(&info);

    read_info(&info);

    uint32_t magic_header = 0x00;

    cmd_info(CTLGET_MAGIC_HEADER, &magic_header);
    printf("magic header:%04X\r\n", magic_header);

    uint8_t get_camera_support = 0;

    cmd_info(CTLGET_CAMERA_SUPPORT, &get_camera_support);
    printf("get_camera_support:%d\r\n", get_camera_support);

    uint8_t set_camer_suport = 0;

    if (get_camera_support) {
        cmd_info(CTLSET_CAMERA_SUPPORT, &set_camer_suport);
        printf("set_camer_suport:%d\r\n", set_camer_suport);

        cmd_info(CTLGET_CAMERA_SUPPORT, &get_camera_support);
        printf("get_camera_support:%d\r\n", get_camera_support);
    }

}

static int write_info(GmInFo_t *param)
{
    if (!param) return -1;

    uint8_t value[OP_TYPE_MAX] = {1, 1, 0, 1, 1, 1, 0, 0, 1, 1};

    for (int i = 0; i < OP_TYPE_MAX; i++) {
        switch (i)
        {
        case CAMERA_SUPPORT:
            param->dev_cap.camera_support = value[i];
            break;
        case IMAGE_UPLOAD_VIA_SPI:
            param->dev_cap.image_upload_via_spi = value[i];
            break;
        case RESERVED_2:
            param->dev_cap.reserved_2 = value[i];
            break;
        case RESET_NOTIFY_REQUIRED:
            param->dev_cap.reset_notify_required = value[i];
            break;
        case FIRMWARE_UPGRADE:
            param->dev_cap.firmware_upgrade_support = value[i];
            break;
        case DEEP_SLEEP_IMPL_MCU:
            param->dev_cap.deep_sleep_impl_mcu = value[i];
            break;
        case RESERVED_6:
            param->dev_cap.reserved_6 = value[i];
            break;
        case RESERVED_7:
            param->dev_cap.reserved_7 = value[i];
            break;
        case SCREEN_SLEEP_CONTROL_VIA_SERIAL:
            param->dev_cap.screen_sleep_control_via_serial = value[i];
            break;
        case DEFAULT_INTO_NETWORK_MODE:
            param->dev_cap.default_into_network_mode = value[i];
            break;
        default:
            break;
        }
    }

    return 0;
}

static void print_dev_cap_info(DeviceCapability_t *dev_cap_info)
{
    if (!dev_cap_info) return;

    printf("camera_support:%02X\r\n", dev_cap_info->camera_support);
    printf("image_upload_via_spi:%02X\r\n", dev_cap_info->image_upload_via_spi);
    printf("reserved_2:%02X\r\n", dev_cap_info->reserved_2);
    printf("reset_notify_required:%02X\r\n", dev_cap_info->reset_notify_required);
    printf("firmware_upgrade_support:%02X\r\n", dev_cap_info->firmware_upgrade_support);
    printf("deep_sleep_impl_mcu:%02X\r\n", dev_cap_info->deep_sleep_impl_mcu);
    printf("reserved_6:%02X\r\n", dev_cap_info->reserved_6);
    printf("reserved_7:%02X\r\n", dev_cap_info->reserved_7);
    printf("screen_sleep_control_via_serial:%02X\r\n", dev_cap_info->screen_sleep_control_via_serial);
    printf("default_into_network_mode:%02X\r\n", dev_cap_info->default_into_network_mode);

}

static void print_bits(uint8_t byte)
{
    for (int i = 7; i >= 0; i--) {
        printf("%d", (byte >> i) & 0x01);
    }
}

static int read_info(GmInFo_t *param)
{
    if (!param) return -1;

    // print_dev_cap_info(&param->dev_cap);

    uint8_t value = 0;
    uint8_t sum = 0;

    // uint16_t caps = *((uint16_t *)&param->dev_cap);
    // printf("%04X\r\n", caps);

    // // 获取bit0值 
    // uint8_t camera_support = caps & (1 << 0);
    // printf("camera_support:%02X\r\n", camera_support);

    // // 获取bit1值
    // uint8_t image_upload_spi = (caps >> 1) & 1;  
    // printf("image_upload_spi:%02X\r\n", image_upload_spi);

    // // 获取bit5值
    // uint8_t deep_sleep_mcu = (caps >> 5) & 1; 
    // printf("deep_sleep_mcu:%02X\r\n", deep_sleep_mcu);

    // uint8_t bit_1 = (caps >> CAMERA_SUPPORT) & 1;
    // printf("bit_1:%02X\r\n", bit_1);

    // uint16_t bits[OP_TYPE_MAX] = {0};
    // for (int i = CAMERA_SUPPORT; i < OP_TYPE_MAX; i++) {
    //     bits[i] =  (caps >> i) & 0x01;
    // }

    // for (int i = 0; i < OP_TYPE_MAX;i++) {
    //     printf("bits[%d]:%02X\r\n", i, bits[i]);
    // }

    // uint8_t caps = *((uint8_t *)&param->dev_cap);
    // printf("%02X\r\n", caps);

    // for (int i = CAMERA_SUPPORT; i < OP_TYPE_MAX; i++) {
    //     uint8_t bit_value = (caps >> i) & 0x01;
    //     printf("bits[%d]:%02X\r\n", i, bit_value);
    // }


    uint8_t *caps_ptr = (uint8_t *)&param->dev_cap;
    printf("%02X%02X\r\n", caps_ptr[0], caps_ptr[1]);

    printf("byte 0:\r\n");
    print_bits(caps_ptr[0]);
    printf("\r\n");

    printf("byte 1:\r\n");
    print_bits(caps_ptr[1]);
    printf("\r\n");

    for (int i = CAMERA_SUPPORT; i < OP_TYPE_MAX; i++) {
        uint8_t bit_value = (caps_ptr[i / 8] >> (i % 8)) & 0x01;
        printf("bits[%d]:%02X\r\n", i, bit_value);
    }

    return 0;
}

#include <stdarg.h>
static int cmd_info(int cmd, ...)
{
    va_list ap;

    va_start(ap, cmd);
    switch (cmd)
    {
    case CTLGET_MAGIC_HEADER:
        uint32_t *magic_header = va_arg(ap, uint32_t *);
        *magic_header = info.magic_header;
        break;

    case CTLGET_CAMERA_SUPPORT:
        uint8_t *get_camera_support_value = va_arg(ap, uint8_t *);
        *get_camera_support_value = info.dev_cap.camera_support;
        break;

    case CTLSET_CAMERA_SUPPORT:
        uint8_t *set_camera_support_value = va_arg(ap, uint8_t *);
        info.dev_cap.camera_support = *set_camera_support_value;
        break;

    default:
        break;
    }

    va_end(ap);

    return 0;
}

int main()
{
    test();
}