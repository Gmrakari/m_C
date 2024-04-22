#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

static void _ptl_send(uint8_t cmd, uint8_t *data, uint16_t len);
static void gen_dy_passwd(uint8_t *password, size_t password_len, uint32_t current_time);

static void gen_dy_passwd(uint8_t *password, size_t password_len, uint32_t current_time)
{
    char buf[] = "7057349464";
    memcpy(password, buf, sizeof(buf));
    password[password_len] = '\0';
    printf("password:%s\n", password);
}

#if 0
static int cb_cmd_req_cmp_algorithm_passwd(uint8_t cmd, uint8_t *data, uint16_t len)
{
    if (!data || !len) return -1;

    int ret = 0;

    typedef struct
    {
        uint8_t gmt[6];                 
        uint8_t passwd_len;             
        uint8_t *passwd;                
    } __attribute__((packed)) res_t;

    struct {
        uint8_t result;                 
        uint8_t type;                   
        uint8_t decode_len;             
        uint8_t *decode_data;           
    } __attribute__((packed)) rsp;

    res_t *res = malloc(sizeof(res_t));
    if (!res) {
        ret = -1;
        printf("res malloc err\r\n");
        goto _cmp_passwd_exit;
    }
    memset(res, 0x00, sizeof(res_t));

    size_t offset = 0;
    memcpy(res->gmt, data, sizeof(res->gmt));
    offset += sizeof(res->gmt);

    memcpy(&(res->passwd_len), data + offset, sizeof(res->passwd_len));
    offset += sizeof(res->passwd_len);
    if (res->passwd_len == 0) {
        ret = 0;
        goto _cmp_passwd_exit;
    }

    size_t passwd_str_len = res->passwd_len + 1;
    res->passwd = malloc(passwd_str_len);
    if (!res->passwd) {
        printf("res->passwd malloc err\r\n");
        ret = -1;
        goto _cmp_passwd_exit;
    }

    memset(res->passwd, 0x00, passwd_str_len);
    memcpy(res->passwd, data + offset, res->passwd_len);
    offset += res->passwd_len;

    printf("res->gmt:%02X%02X%02X%02X%02X%02X\r\n", res->gmt[0],res->gmt[1],res->gmt[2],res->gmt[3],res->gmt[4],res->gmt[5]);
    printf("res->passwd_len: %d\r\n", res->passwd_len);
    
    for (int i = 0;i < passwd_str_len - 1; i++) {
        printf("%02X", res->passwd[i]);
    }

    uint8_t *passwd_str = malloc(passwd_str_len);
    if (!passwd_str) {
        printf("passwd_str malloc err\r\n");
        ret = -1;

        if (res->passwd) {
            free(res->passwd);
            res->passwd = NULL;
        }
        goto _cmp_passwd_exit;
    }

    memset(passwd_str, 0x00, passwd_str_len);
    int passwd_str_idx = 0;
    
    for (int i = 0; i < res->passwd_len; i++) {
        passwd_str_idx += snprintf(&passwd_str[passwd_str_idx], passwd_str_len - passwd_str_idx, "%d", res->passwd[i]);
        printf("%c\r\n", passwd_str[passwd_str_idx]);
        printf("passwd_str_idx:%d\r\n", passwd_str_idx);
        printf("passwd_str_len - passwd_str_idx:%d\r\n", (int)passwd_str_len - passwd_str_idx);
    }

    passwd_str[passwd_str_idx] = '\0';
    printf("passwd_str:%s\r\n", passwd_str);

    if (res->passwd) {
        free(res->passwd);
        res->passwd = NULL;
    }

    #if 1
    uint32_t timestamp = 1410838387;
    #endif

    printf("timestamp: %d\n", timestamp);

    size_t gen_dy_passwd_str_len = passwd_str_len; 
    uint8_t *gen_dy_passwd_str = malloc(sizeof(uint8_t) * gen_dy_passwd_str_len);
    if (!gen_dy_passwd_str) {
        if (passwd_str) {
            free(passwd_str);
            passwd_str = NULL;
        }
        printf("gen_dy_passwd_str malloc err\r\n");
        ret = -1;
        goto _cmp_passwd_exit;
    }
    memset(gen_dy_passwd_str, 0x00, gen_dy_passwd_str_len);
    #if 1
    gen_dy_passwd(gen_dy_passwd_str, res->passwd_len, timestamp);
    #endif 

    gen_dy_passwd_str[gen_dy_passwd_str_len - 1] = '\0';

    printf("request_password: %s, generated_password: %s\n", passwd_str, gen_dy_passwd_str);

    rsp.result = strcmp(passwd_str, gen_dy_passwd_str) == 0 ? 0x00 : 0x01;

    if (passwd_str) {
        free(passwd_str);
        passwd_str = NULL;
    }

    // if (rsp.result) {
    //     if (gen_dy_passwd_str) {
    //         free(gen_dy_passwd_str);
    //         gen_dy_passwd_str = NULL;
    //     }
    //     goto _cmp_passwd_exit;
    // }

    rsp.decode_len = gen_dy_passwd_str_len - 1;
    rsp.decode_data = malloc(rsp.decode_len);
    if (!rsp.decode_data) {
        printf("rsp.decode_data malloc err\r\n");
        ret = -1;

        if (gen_dy_passwd_str) {
            free(gen_dy_passwd_str);
            gen_dy_passwd_str = NULL;
        }
        goto _cmp_passwd_exit;
    }
    
    memset(rsp.decode_data, 0x00, rsp.decode_len);
    memcpy(rsp.decode_data, gen_dy_passwd_str, rsp.decode_len);

    printf("gen_dy_passwd_str:\r\n");
    for (int i = 0; i < rsp.decode_len; i++) {
        printf("%02X", gen_dy_passwd_str[i]);
    }
    printf("\r\n");

    printf("decode_data:\r\n");
    for (int i = 0; i < rsp.decode_len; i++) {
        printf("%02X", rsp.decode_data[i]);
    }
    printf("\r\n");

    if (gen_dy_passwd_str) {
        free(gen_dy_passwd_str);
        gen_dy_passwd_str = NULL;
    }

    rsp.type = 0x03;

    uint16_t rsp_len = sizeof(rsp.result) + sizeof(rsp.type) + sizeof(rsp.decode_len) + rsp.decode_len;

    uint8_t *rsp_ptr = (uint8_t *)&rsp;

    printf("rsp_ptr:\r\n");
    for (int i = 0; i < rsp_len; i++) 
        printf("%02X ", rsp_ptr[i]); 

    _ptl_send(cmd, (uint8_t *)&rsp, rsp_len);

    if (rsp.decode_data) {
        free(rsp.decode_data);
        rsp.decode_data = NULL;
    }

    if (res) {
        free(res);
        res = NULL;
    }

    return ret;

_cmp_passwd_exit:
    rsp.result = 0x01;
    _ptl_send(cmd, (uint8_t *)&rsp, sizeof(rsp.result));

    if (res) { 
        free(res);
        res = NULL;
    }

    return ret;
}
#endif

#if 1
static int cb_cmd_req_cmp_algorithm_passwd1(uint8_t cmd, uint8_t *data, uint16_t len)
{
    if (!data || !len) return -1;

    int ret = 0;

    struct {
        uint8_t result;                 /* 对比结果 */
    } __attribute__((packed)) error_handle_rsp;

    uint8_t *recv_passwd_data     = NULL;
    uint8_t *passwd_str           = NULL;
    uint8_t *gen_dy_passwd_str    = NULL;

    uint8_t gmt[6] = {0};
    size_t offset = 0;
    memcpy(gmt, data, sizeof(gmt));
    offset += sizeof(gmt);

    uint8_t recv_paasswd_len = 0; 
    memcpy(&recv_paasswd_len, data + offset, sizeof(recv_paasswd_len));
    offset += sizeof(recv_paasswd_len);
    if (recv_paasswd_len == 0) {
        ret = 0;
        goto _cmp_passwd_exit;
    }

    recv_passwd_data = malloc(recv_paasswd_len);
    if (!recv_passwd_data) {
        printf("recv_passwd_data malloc err\r\n");
        ret = -1;
        goto _cmp_passwd_exit;
    }
    memset(recv_passwd_data, 0x00, recv_paasswd_len);
    memcpy(recv_passwd_data, data + offset, recv_paasswd_len);
    // offset += recv_paasswd_len;

    printf("gmt:%02X%02X%02X%02X%02X%02X\r\n", gmt[0], gmt[1], gmt[2], gmt[3], gmt[4], gmt[5]);
    printf("recv_paasswd_len: %d\r\n", recv_paasswd_len);

    size_t passwd_str_len = recv_paasswd_len + 1;
    passwd_str = malloc(passwd_str_len);
    if (!passwd_str) {
        printf("passwd_str malloc err\r\n");
        ret = -1;

        if (recv_passwd_data) {
            free(recv_passwd_data);
            recv_passwd_data = NULL;
        }
        goto _cmp_passwd_exit;
    }

    memset(passwd_str, 0x00, passwd_str_len);
    int passwd_str_idx = 0;

    for (int i = 0; i < recv_paasswd_len; i++) {
        passwd_str_idx += snprintf(&passwd_str[passwd_str_idx], passwd_str_len - passwd_str_idx, "%d", recv_passwd_data[i]);
        printf("%c\r\n", passwd_str[passwd_str_idx]);
        printf("passwd_str_idx:%d\r\n", passwd_str_idx);
        printf("passwd_str_len - passwd_str_idx:%d\r\n", (int)passwd_str_len - passwd_str_idx);
    }

    passwd_str[passwd_str_idx] = '\0';
    printf("passwd_str:%s\r\n", passwd_str);

    if (recv_passwd_data) {
        free(recv_passwd_data);
        recv_passwd_data = NULL;
    }

    #if 0
    uint32_t timestamp = convert_gmt_to_timestamp(gmt);
    #endif

    #if 1
    uint32_t timestamp = 1410838387;
    #endif

    printf("timestamp: %d\n", timestamp);

    size_t gen_dy_passwd_str_len = passwd_str_len; 
    gen_dy_passwd_str = malloc(sizeof(uint8_t) * gen_dy_passwd_str_len);
    if (!gen_dy_passwd_str) {
        if (passwd_str) {
            free(passwd_str);
            passwd_str = NULL;
        }
        printf("gen_dy_passwd_str malloc err\r\n");
        ret = -1;
        goto _cmp_passwd_exit;
    }
    memset(gen_dy_passwd_str, 0x00, gen_dy_passwd_str_len);
    #if 1
    // generate_dynamic_password(gen_dy_passwd_str, recv_paasswd_len, timestamp);
    gen_dy_passwd(gen_dy_passwd_str, recv_paasswd_len, timestamp);
    #endif 

    #if 0
    uint8_t passwd[5] = {1};
    strncpy(gen_dy_passwd_str, passwd, sizeof(gen_dy_passwd_str));
    #endif
    gen_dy_passwd_str[gen_dy_passwd_str_len - 1] = '\0';

    printf("request_password: %s, generated_password: %s\n", passwd_str, gen_dy_passwd_str);

    /*
    * result说明:
    * 0x00：正确
    * 其他：错误（无后续数据）
    */
    error_handle_rsp.result = strcmp(passwd_str, gen_dy_passwd_str) == 0 ? 0x00 : 0x01;

    if (passwd_str) {
        free(passwd_str);
        passwd_str = NULL;
    }

    // 1.对比失败
    // if (error_handle_rsp.result) {
    //     if (gen_dy_passwd_str) {
    //         free(gen_dy_passwd_str);
    //         gen_dy_passwd_str = NULL;
    //     }
    //     goto _cmp_passwd_exit;
    // }

    // 1B 对比结果 + 1B 离线密码类型 + 1B 解密后的数据长度 + NB 解密后的数据

    uint16_t rsp_len = sizeof(uint8_t) * 3 + gen_dy_passwd_str_len - 1;
    uint8_t *rsp = malloc(rsp_len);
    if (!rsp) {
        if (gen_dy_passwd_str) {
            free(gen_dy_passwd_str);
            gen_dy_passwd_str = NULL;
        }
        goto _cmp_passwd_exit;
    }

    /*
    * type说明:
    * 0x00：限时开门离线密码
    * 0x01：单次开门离线密码
    * 0x02：清除离线密码（单个）
    * 0x03：动态密码
    * 0x04：清除离线密码（所有)
    */
    uint8_t type = 0x03;
    uint8_t decode_data_len = gen_dy_passwd_str_len - 1;
    // 2.对比成功，发送动态密码数据

    offset = 0;
    memcpy(rsp, &(error_handle_rsp.result), sizeof(error_handle_rsp));
    offset += sizeof(error_handle_rsp);

    memcpy(rsp + offset, &type, sizeof(type));
    offset += sizeof(type);

    memcpy(rsp + offset, &decode_data_len, sizeof(decode_data_len));
    offset += sizeof(decode_data_len);

    memcpy(rsp + offset, gen_dy_passwd_str, gen_dy_passwd_str_len - 1);
    offset += (gen_dy_passwd_str_len - 1);

    if (gen_dy_passwd_str) {
        free(gen_dy_passwd_str);
        gen_dy_passwd_str = NULL;
    }

    _ptl_send(cmd, (uint8_t *)rsp, offset);

    if (rsp) {
        free(rsp);
        rsp = NULL;
    }

    return ret;

_cmp_passwd_exit:
    error_handle_rsp.result = 0x01;
    _ptl_send(cmd, (uint8_t *)&error_handle_rsp, sizeof(error_handle_rsp));

    return ret;
}
#endif

static void _ptl_send(uint8_t cmd, uint8_t *data, uint16_t len)
{
    if (!data || !len) {
        printf("no data\r\n");
        return ;
    }
    printf("len: %d, data:\r\n", len);
    uint8_t *ptr = data;
    for (size_t i = 0;i < len; i++) {
        printf("%02X ", ptr[i]);
    }
    printf("\r\n\r\n");
}

static int _test_app(void)
{
    // uint8_t data[] = {0x55,0xAA,0x00,0x16,0x00,0x11,0x14,0x09,0x16,0x03,0x2D,0x07,0x0A,0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};
    // uint8_t data[] = {0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};
    uint8_t data[] = {0x14,0x09,0x16,0x03,0x2D,0x07,0x0A,0x04,0x01,0x08,0x03,0x03,0x08,0x03,0x02,0x03,0x03};

    uint16_t data_len = sizeof(data) / sizeof(data[0]);

    uint8_t cmd = 0x16;

    int ret = 0;
    // ret = cb_cmd_req_cmp_algorithm_passwd(cmd, data, data_len);
    ret = cb_cmd_req_cmp_algorithm_passwd1(cmd, data, data_len);
    printf("ret:%d\r\n", ret);

    return 0;
}

static int _test_01()
{
    char c;
    printf("Press Enter to execute or 'q' to quit.\n");

    while (1) {
        c = getchar();  // 等待用户输入

        if (c == '\n') {
            _test_app();  // 按下回车时执行测试函数
            printf("Press Enter to execute or 'q' to quit.\n");
        } else if (c == 'q') {
            break;  // 输入 'q' 退出循环
        }
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    _test_01();
    return 0;
}
