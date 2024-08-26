#ifndef _FLASH_RW_USR_INFO_H_
#define _FLASH_RW_USR_INFO_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* MAX size of client ID */
#define MAX_SIZE_OF_CLIENT_ID (80)

/* MAX size of product ID */
#define MAX_SIZE_OF_PRODUCT_ID (17)

/* MAX size of product secret */
#define MAX_SIZE_OF_PRODUCT_SECRET (32)

/* MAX size of device name */
#define MAX_SIZE_OF_DEVICE_NAME (48)

/* MAX size of device secret */
#define MAX_SIZE_OF_DEVICE_SECRET (64)

/* MAX size of device cert file name */
#define MAX_SIZE_OF_DEVICE_CERT_FILE_NAME (128)

/* MAX size of device key file name */
#define MAX_SIZE_OF_DEVICE_SECRET_FILE_NAME (128)

#define MAX_SIZE_OF_MAC   (12)

typedef struct _triple_info_ {
    unsigned int magic_header;
    char device_id[MAX_SIZE_OF_PRODUCT_ID + 1];
    char device_secret[MAX_SIZE_OF_DEVICE_SECRET + 1];
    char mac[MAX_SIZE_OF_MAC + 1];
    char product_id[MAX_SIZE_OF_PRODUCT_ID + 1];
    char device_name[MAX_SIZE_OF_DEVICE_NAME + 1];
} sTripleInfo;

typedef struct {
    unsigned int magic_header;

    char device_name[48];

    //
    char wifi_flag;
    char wifi_ssid[33];
    char wifi_key[64];

    //
    char mqtt_host[64];
    int mqtt_port;

    uint8_t bind;
    uint8_t net_cfg;

    //
    uint8_t is_bind;
    uint8_t is_net_cfg;
    uint8_t got_ip;
    uint8_t bind_type;  //0: none, 1: wifi, 2: ble

    //
    uint32_t uart1_baud_rate;

    char country[4];
    int16_t tz;
    int16_t temp;
    int8_t humidity;
    int8_t device_id[17];
    int8_t device_mac[6];
    //
    sTripleInfo tripleInfo;
} DevInfo_t;

int get_dev_info_size(int *olen);


int init_dev_info(DevInfo_t *dev_info);

#endif