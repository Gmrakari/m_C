#ifndef _STRUCT_IN_ARR_USAGE_H_
#define _STRUCT_IN_ARR_USAGE_H_

#include <stdint.h>

typedef enum
{
    UART_1 = 0,
    UART_2,
    UART_MAX,
} uart_t;

typedef enum
{
    DATA_WIDTH_5BIT,
    DATA_WIDTH_6BIT,
    DATA_WIDTH_7BIT,
    DATA_WIDTH_8BIT
} data_width_t;

typedef enum
{
    PARITY_NO,
    PARITY_ODD,
    PARITY_EVEN,
} parity_t;

typedef enum
{
    STOP_BITS_1,
    STOP_BITS_2,
} stop_bits_t;

typedef enum
{
    FLOW_CTRL_DISABLED,
    FLOW_CTRL_CTS,
    FLOW_CTRL_RTS,
    FLOW_CTRL_RTS_CTS
} flow_control_t;

typedef struct
{
    uint32_t            baud_rate;
    data_width_t        data_width;
    parity_t            parity;
    stop_bits_t         stop_bits;
    flow_control_t      flow_control;
    uint8_t             flags;
} uart_config_t;

typedef enum {
    BAUD_RATE_9600      = 0,
    BAUD_RATE_115200,
    BAUD_RATE_MAX,
} baud_rate_type_t;

typedef struct {
    uart_t port;
    uart_config_t *conf;
    uint8_t index;
} uart_config_info_t;

#define UART_NUM                    (2)

int init();

int deinit();

int struct_in_arr_usage_func();

#endif // _STRUCT_IN_ARR_USAGE_H_