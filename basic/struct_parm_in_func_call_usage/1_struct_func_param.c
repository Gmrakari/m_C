#include <stdio.h>
#include <stdint.h> // uint8
#include <string.h> // memcpy
#include <stdlib.h> // free

struct bf1b_wifi_ap_record {
    uint8_t link_status;
    uint8_t bssid[6];
    uint8_t ssid[32 + 1];
    uint8_t channel;
    int8_t rssi;
    uint8_t auth_mode;
    uint8_t cipher;
};

typedef struct {
    int hdr;
    struct bf1b_wifi_ap_record record;
} rnm_sta_link_status_ind_msg_t;

typedef struct {
    uint16_t cmd;
    uint16_t flags;
    uint16_t status;
} rnm_base_msg_t;

typedef struct {
    rnm_base_msg_t cmd;
    void (*free_fn)(void *data);
    void *data;
    uint16_t data_len;
} rnm_msg_t;

void free_func(void *data) {
    if (data == NULL) return ;
    free(data);
}

void rnmc_sta_get_link_status(struct bf1b_wifi_ap_record *status);
void send_cmd_with_pld_rsp(rnm_base_msg_t *msg, int extra_timeout_ms, void **result);
void rnmc_cmd_send(rnm_msg_t *resp, int ms_to_wait);

// rnmc_ret_t rnmc_cmd_send(rnmc_t *rnm, void *cmd, uint16_t cmd_len, rnm_msg_t *resp, int ms_to_wait);

void rnmc_cmd_send(rnm_msg_t *resp, int ms_to_wait) 
{
    rnm_msg_t msg;
    void *msg_copy = NULL;
    void *cmd = 1;

    memset(&msg, 0, sizeof(msg));

    printf("[%s][%d]\r\n", __func__, __LINE__);
    memcpy(&msg.cmd, cmd, sizeof(rnm_base_msg_t));
    printf("[%s][%d]\r\n", __func__, __LINE__);

    msg_copy = malloc(256);
    msg.data = msg_copy;
    msg.free_fn = free_func;
    msg.data_len = 20;
    
    printf("[%s][%d]\r\n", __func__, __LINE__);
 
    return ;
}

void send_cmd_with_pld_rsp(rnm_base_msg_t *msg, int extra_timeout_ms, void **result)
{
    void *copy;
    int ret;
    rnm_msg_t resp;

    ret = resp.cmd.status;

    // copy = malloc(256);
    rnmc_cmd_send(&resp, 0);
    memcpy(copy, resp.data, resp.data_len);
    *result = copy;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    resp.free_fn(resp.data);

    printf("[%s][%d]\r\n", __func__, __LINE__);
    return ;
}

void rnmc_sta_get_link_status(struct bf1b_wifi_ap_record *status)
{
    rnm_base_msg_t msg;
    rnm_sta_link_status_ind_msg_t *result = NULL;
    
    memset(&msg, 0, sizeof(msg));
    msg.cmd = 1;

    send_cmd_with_pld_rsp(&msg, 0, (void **)&result);

    memcpy(status, &result->record, sizeof(*status));
    free(result);
    printf("[%s][%d]\r\n", __func__, __LINE__);

    return ;
}

// struct bf1b_wifi_ap_record {
//     uint8_t link_status;
//     uint8_t bssid[6];
//     uint8_t ssid[32 + 1];
//     uint8_t channel;
//     int8_t rssi;
//     uint8_t auth_mode;
//     uint8_t cipher;
// };

int main() 
{
    struct bf1b_wifi_ap_record status;
    memset(&status, 0, sizeof(status));
    // rnmc_sta_get_link_status(status);
    printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}