
#include <stdio.h>
#include <stdint.h>

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
} cap_type_t;

typedef struct {
    uint8_t dec_type;
    uint8_t start_bits;
} setting_param_t;

typedef struct {
    uint8_t short_keep_alive_time;      /* range: 10 ~ 180 seconds */
    uint8_t deep_sleep_status;          /* 0x00 保留; 0x01 锁定深度睡眠; 0x02 解除深度休眠*/
    uint8_t reserved[8];                /* 保留段 */
} hbn_param_t;

// 填充
// typedef struct {
//     unsigned int magic_header;          // 4
//     cap_type_t dev_cap;                 // 2
//     hbn_param_t hbn_param;              // 10
//     setting_param_t passwd_base_pararm; // 2
// } __attribute__((packed)) info_t;

typedef struct {
    unsigned int magic_header;          // 4
    cap_type_t dev_cap;                 // 2
    hbn_param_t hbn_param;              // 10
    setting_param_t passwd_base_pararm; // 2
} info_t;

int main() {
    printf("sizeof(info_t):%ld\r\n", sizeof(info_t));               // 18
    printf("sizeof(unsigned int):%ld\r\n", sizeof(unsigned int));
    printf("sizeof(cap_type_t):%ld\r\n", sizeof(cap_type_t));
    printf("sizeof(hbn_param_t):%ld\r\n", sizeof(hbn_param_t));
    printf("sizeof(setting_param_t):%ld\r\n", sizeof(setting_param_t));

    return 0;
}

// typedef struct {
//     unsigned int magic_header;// 4
//     cap_type_t dev_cap;   // 2
//     hbn_param_t hbn_param;//10
//     setting_param_t passwd_base_pararm;//2
// } __attribute__((packed)) UARTPInfo_t;
