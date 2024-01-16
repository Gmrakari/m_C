#include <stdio.h>
#include <string.h> // memcpy
#include <stdlib.h> // free

#include "struct_in_arr_usage.h"

static void print(uart_config_info_t *info, baud_rate_type_t type);
static void get_config_info(uart_config_t *config);

static uart_config_info_t config = {0};

static void print(uart_config_info_t *info, baud_rate_type_t type)
{
    if (!info) return ;

    printf("info->conf[%d].baud_rate:%d\r\n", type, info->conf[type].baud_rate);
    printf("info->conf[%d].data_width:%d\r\n", type, info->conf[type].data_width);
    printf("info->conf[%d].flags:%d\r\n", type, info->conf[type].flags);
    printf("info->conf[%d].flow_control:%d\r\n", type, info->conf[type].flow_control);
    printf("info->conf[%d].parity:%d\r\n", type, info->conf[type].parity);
    printf("info->conf[%d].stop_bits:%d\r\n", type, info->conf[type].stop_bits);
}

static void get_config_info(uart_config_t *config)
{
    if (!config) return ;

    uart_config_t *ptr = config;

    printf("ptr->baud_rate:%d\r\n", ptr->baud_rate);
    printf("ptr->data_width:%d\r\n", ptr->data_width);
    printf("ptr->flags:%d\r\n", ptr->flags);
    printf("ptr->flow_control:%d\r\n", ptr->flow_control);
    printf("ptr->parity:%d\r\n", ptr->parity);
    printf("ptr->stop_bits:%d\r\n", ptr->stop_bits);

    return ;
}

int init()
{
    printf("[%s][%d]\r\n", __func__, __LINE__);
    const uart_config_t conf_arr[] = {
            [0] =
            {
                .baud_rate      = 9600,
                .data_width     = DATA_WIDTH_8BIT,
                .parity         = PARITY_NO,
                .stop_bits      = STOP_BITS_1,
                .flow_control   = FLOW_CTRL_DISABLED,
                .flags          = 0,
            },
            [1] =
            {
                .baud_rate      = 115200,
                .data_width     = DATA_WIDTH_8BIT,
                .parity         = PARITY_NO,
                .stop_bits      = STOP_BITS_1,
                .flow_control   = FLOW_CTRL_DISABLED,
                .flags          = 0,
            },
    };

    uart_config_t *uart_config_ptr = (uart_config_t *)malloc(sizeof(uart_config_t) * UART_NUM);
    if (!uart_config_ptr) return -1;
    memset(uart_config_ptr, 0x00, sizeof(uart_config_ptr) * UART_NUM);

    memcpy((void *)uart_config_ptr, (const void*)conf_arr, sizeof(conf_arr));

    config.port     = UART_1;
    config.conf     = uart_config_ptr;
    config.index    = BAUD_RATE_115200;

    print(&config, config.index);

    get_config_info(&config.conf[config.index]);

    return 0;
}

int deinit()
{
    if (config.conf) { free(config.conf); config.conf = NULL; }
    return 0;
}

int struct_in_arr_usage_func()
{
    int ret = 0;
    if (0 != (ret = init()))
        printf("init err");

    if (0 != (ret = deinit()))
        printf("deinit err");

    return ret;
}
