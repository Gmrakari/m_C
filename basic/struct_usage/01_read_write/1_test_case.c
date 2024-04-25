#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

typedef enum {
    CTL_READ_BLE_CFG = 0,
    CTL_WRITE_BLE_CFG,
    CTL_READ_WIFI_CFG,
    CTL_WRITE_WIFI_CFG,
    CTL_DEFAULT,
} cfg_op_type_t;

typedef struct {
    uint8_t en;
    uint8_t val;
} __attribute__((packed)) ble_cfg_t;

typedef struct {
    uint8_t ssid[8];
    uint8_t passwd[8];
} __attribute__((packed)) wifi_cfg_t;

typedef struct {
    uint8_t ssid[8];
    uint8_t passwd[8];
} __attribute__((packed)) wifi_cfg_t;

typedef struct {
    uint16_t header;
    ble_cfg_t ble_cfg;
    wifi_cfg_t wifi_cfg;
} __attribute__((packed)) cfg_t;

static int _read_cfg(cfg_op_type_t type, void *param)
{
    uint16_t offset = 0;

    uint16_t header;
    ble_cfg_t ble_cfg;
    wifi_cfg_t wifi_cfg;

}

static int _write_cfg(cfg_op_type_t type, void *param)
{
    uint16_t offset = 0;

    uint16_t header;
    ble_cfg_t ble_cfg;
    wifi_cfg_t wifi_cfg;

}

static int _ctl_cfg(int cmd, ...)
{
    int ret = 0;
    va_list ap;

    va_start(ap, cmd);

    switch (cmd) {
        case CTL_READ_BLE_CFG:
        {
            uint16_t *header = va_arg(ap, uint16_t *);
            if (header) {
                // ret = _read_cfg(, header);
            } else {
                ret = -1;
            }
            break;
        }
        case CTL_WRITE_BLE_CFG:
        {
            _write_cfg(CTL_WRITE_BLE_CFG, )
        }
        case CTL_READ_WIFI_CFG:
        {
            _read_cfg(CTL_READ_WIFI_CFG, )
        }
        case CTL_WRITE_WIFI_CFG:
        {

        }
    }

    va_end(ap);

    return ret;
}

static int test()
{

    return 0;
}

int main()
{
    test();
}
