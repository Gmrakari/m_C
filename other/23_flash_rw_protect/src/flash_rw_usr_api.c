#include "flash_rw_usr_api.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "flash_rw_usr_info.h"

#define FLASH_RW_DEFAULT_MEM_SIZE (0x1000)

typedef struct {
    void *handle;
    int fd;
    uint8_t *ptr;
    int size;
} flash_rw_info_t;

typedef enum {
    MAIN_SECTOR = 0,
    BAK_SECTOR
} flash_type_t;

static flash_rw_info_t src_info = {.handle = NULL, .fd = 0, .ptr = NULL, .size = 0};
static flash_rw_info_t bak1_info = {.handle = NULL, .fd = 0, .ptr = NULL, .size = 0};
static flash_rw_info_t bak2_info = {.handle = NULL, .fd = 0, .ptr = NULL, .size = 0};

static void _print_dev_info_val(const DevInfo_t *devInfo)
{
    if (!devInfo) 
        return ;

    printf("magic_header: %08X\n", devInfo->magic_header);
    printf("Device Name: %s\n", devInfo->device_name);
    printf("wifi_flag: %d\n", devInfo->wifi_flag);
    printf("WiFi SSID: %s\n", devInfo->wifi_ssid);
    printf("WiFi Key: %s\n", devInfo->wifi_key);
    printf("MQTT Host: %s\n", devInfo->mqtt_host);
    printf("MQTT Port: %d\n", devInfo->mqtt_port);
    printf("Device bind: %d\n", devInfo->bind);
    printf("Device net_cfg: %d\n", devInfo->net_cfg);
    printf("Device is_bind: %d\n", devInfo->is_bind);
    printf("Device is_net_cfg: %d\n", devInfo->is_net_cfg);
    printf("Device got_ip: %d\n", devInfo->got_ip);
    printf("Device bind_type: %d\n", devInfo->bind_type);

    printf("UART Baud Rate: %u\n", devInfo->uart1_baud_rate);
    printf("Device country: %s\n", devInfo->country);
    printf("Device tz: %04X\n", devInfo->tz);
    printf("Device temp: %04X\n", devInfo->temp);
    printf("Device humidity: %d\n", devInfo->humidity);
    printf("Device device_id: %s\n", devInfo->device_id);

    printf("Device device_mac: %02X%02X%02X%02X%02X%02X\n", devInfo->device_mac[0] & 0xff, devInfo->device_mac[1] & 0xff, devInfo->device_mac[2] & 0xff, devInfo->device_mac[3] & 0xff, devInfo->device_mac[4] & 0xff, devInfo->device_mac[5] & 0xff);

    printf("Device tripleInfo device_id: %s\n", devInfo->tripleInfo.device_id);
    printf("Device tripleInfo device_secret: %s\n", devInfo->tripleInfo.device_secret);
    printf("Device tripleInfo mac: %s\n", devInfo->tripleInfo.mac);
    printf("Device tripleInfo product_id: %s\n", devInfo->tripleInfo.product_id);
    printf("Device tripleInfo device_name: %s\n", devInfo->tripleInfo.device_name);
    printf("Device crc: 0x%08x\n", devInfo->crc_32);

    return ;
}

static int _flash_rw_get_fd_mem(const char *filepath, int *fd, uint8_t **ptr)
{
    if (!filepath || !fd) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;
    *fd = open(filepath, O_RDWR | O_CREAT, 0644);
    if (*fd == -1) {
        printf("[%s][%d]open err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 确保文件大小与映射内存的大小一致
    if (ftruncate(*fd, FLASH_RW_DEFAULT_MEM_SIZE) == -1) {
        perror("ftruncate failed");
        close(*fd);
        return -1;
    }

    uint8_t *mem_ptr = NULL;

    mem_ptr = mmap(NULL, FLASH_RW_DEFAULT_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (mem_ptr == MAP_FAILED) {
        printf("[%s][%d]mmap err!\r\n", __func__, __LINE__);
        close(*fd);
        return -1;

    }

    *ptr = mem_ptr;

    return ret;
}

static int _deinit_mem_file(int *fd, uint8_t **ptr, int *size)
{
    if (!*ptr || !size) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    if (munmap(*ptr, *size) == -1) {
        perror("munmap failed");
        close(*fd);
        ret = -1;
    }

    close(*fd);

    return ret;
}

static int _init_mem_file(const char *filepath, int *fd, int *size, uint8_t **ptr)
{
    if (!filepath || !fd) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = _flash_rw_get_fd_mem(filepath, fd, ptr);
    if (ret != 0) {
        printf("[%s][%d]_flash_rw_get_fd_mem failed\r\n", __func__, __LINE__);
        return ret;
    }

    if (!*ptr) {
        printf("[%s][%d]ptr is null!\r\n", __func__, __LINE__);
        return -1;
    }

    *size = FLASH_RW_DEFAULT_MEM_SIZE;

#if 1
    memset(*ptr, 0xff, *size);
#endif
    return ret;
}

static int _load_src_mem_sector(const char *filepath)
{

}

uint16_t crc16_xmodem(const uint8_t *buffer, uint32_t buffer_length)
{
    uint8_t c, treat, bcrc;
    uint16_t wcrc = 0;

    for(uint32_t i = 0; i < buffer_length; i++)
    {
        c = buffer[i];
        for(uint8_t j = 0; j < 8; j++)
        {
            treat = c & 0x80;
            c <<= 1;
            bcrc = (wcrc >> 8) & 0x80;
            wcrc <<= 1;
            if(treat != bcrc)
                wcrc ^= 0x1021;
        }
    }
    return wcrc;
}

uint16_t crc16(const uint8_t *data, uint32_t length) {
    uint16_t crc = 0xFFFF;
    for (uint32_t i = 0; i < length; i++) {
        crc ^= (uint16_t)data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

static int _cal_diff_crc(uint8_t *data, int len)
{
    int ret = 0;
    int crc_32 = 0;
    ret = cal_crc32(data, len, &crc_32);

    printf("[%s][%d]crc_32 val: %u, hex: 0x%08X\r\n", __func__, __LINE__, crc_32, crc_32);

    int cal_crc16 = 0;
    cal_crc16 = crc16_xmodem(data, len);

    printf("[%s][%d]crc16_xmodem val: %u, hex: 0x%08X\r\n", __func__, __LINE__, cal_crc16, cal_crc16);

    int rino_cal_crc16 = 0;
    rino_cal_crc16 = crc16(data, len);

    printf("[%s][%d]crc16 val: %u, hex: 0x%08X\r\n", __func__, __LINE__, rino_cal_crc16, rino_cal_crc16);

    return 0;
}

static int _print_cal_diff_data_crc_info()
{
    uint8_t data0[] = {0x00};
    uint8_t data1[] = {0x00, 0x00};
    uint8_t data2[] = {0x00, 0x00, 0x00};
    uint8_t data3[] = {0x00, 0x00, 0x00, 0x00};
    uint8_t data4[] = {0x00, 0x00, 0x00, 0x00, 0x00};

    uint8_t data5[] = {0xff};
    uint8_t data6[] = {0xff, 0xff};
    uint8_t data7[] = {0xff, 0xff, 0xff};
    uint8_t data8[] = {0xff, 0xff, 0xff, 0xff};
    uint8_t data9[] = {0xff, 0xff, 0xff, 0xff, 0xff};

    uint8_t data10[4096] = {0};
    uint8_t data11[4096] = {0};
    memset(data10, 0x00, 4096);
    memset(data11, 0xff, 4096);

    uint32_t len0 = sizeof(data0) / sizeof(data0[0]);
    uint32_t len1 = sizeof(data1) / sizeof(data1[0]);
    uint32_t len2 = sizeof(data2) / sizeof(data2[0]);
    uint32_t len3 = sizeof(data3) / sizeof(data3[0]);
    uint32_t len4 = sizeof(data4) / sizeof(data4[0]);

    uint32_t len5 = sizeof(data5) / sizeof(data5[0]);
    uint32_t len6 = sizeof(data6) / sizeof(data6[0]);
    uint32_t len7 = sizeof(data7) / sizeof(data7[0]);
    uint32_t len8 = sizeof(data8) / sizeof(data8[0]);
    uint32_t len9 = sizeof(data9) / sizeof(data9[0]);

    uint32_t len10 = sizeof(data10) / sizeof(data10[0]);
    uint32_t len11 = sizeof(data11) / sizeof(data11[0]);

    uint8_t *data_list[] = {data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11};
    int len_list[] = {len0, len1, len2, len3, len4, len5, len6, len7, len8, len9, len10, len11};

    int size = sizeof(data_list) / sizeof(data_list[0]);

    for (int i = 0; i < size; i++) {
        printf("i:%d\r\n", i);
        if (i == 10 || i == 11) {
            goto _no_print;
        } else {
            goto _go_print;

        }

        _go_print:
            for (int j = 0; j < len_list[i]; j++) {
                printf("%02X", data_list[i][j]);
                if (j != len_list[i] - 1) {
                    printf(" ");
                }
            }
            printf("\r\n");

        _no_print:

        _cal_diff_crc(data_list[i], len_list[i]);

    }

    return 0;
}

int flash_rw_usr_api_get_crc_val(uint8_t *addr, int len, uint32_t *ocrc)
{
    if (!addr || !len || !ocrc) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }


    return 0;
}

int flash_rw_usr_api_earse(int type)
{
    int ret = 0;
    switch (type)
    {
    case MAIN_SECTOR:
        memset(src_info.ptr, 0xff, src_info.size);
        break;
    case BAK_SECTOR:
        memset(bak1_info.ptr, 0xff, bak1_info.size);
        break;
    default:
        break;
    }

    return ret;
}

int flash_rw_usr_api_read_from_main(uint8_t **out, int *olen)
{
    int buf_len = sizeof(DevInfo_t);
    uint8_t *buf = malloc(buf_len);
    if (!buf) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }
    memset(buf, 0x00, buf_len);

    memcpy(buf, src_info.ptr, buf_len);

    *out = buf;
    *olen = buf_len;

    return 0;
}

int flash_rw_usr_api_read_from_bak(uint8_t **out, int *olen)
{
    int buf_len = sizeof(DevInfo_t);
    uint8_t *buf = malloc(buf_len);
    if (!buf) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }
    memset(buf, 0x00, buf_len);

    memcpy(buf, bak1_info.ptr, buf_len);

    *out = buf;
    *olen = buf_len;

    return 0;
}

int flash_rw_usr_api_write_to_main(uint8_t *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    if (!src_info.ptr) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    memcpy(src_info.ptr, data, len);

    return ret;
}

int flash_rw_usr_api_write_to_bak(uint8_t *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    memcpy(bak1_info.ptr, data, len);

    return ret;
}

int flash_rw_usr_api_check_valid(uint8_t *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;


    return ret;    
}

int flash_rw_usr_api_write_to_main_sector(uint8_t *data, int data_len)
{
    if (!data || !data_len) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = flash_rw_usr_api_earse(MAIN_SECTOR);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_earse err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = flash_rw_usr_api_write(MAIN_SECTOR, data, data_len);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write err!\r\n", __func__, __LINE__);
        return -1;
    }

    return ret;
}

int flash_rw_usr_api_read(int type, uint8_t **out, int *olen)
{
    int ret = 0;

    switch (type)
    {
    case MAIN_SECTOR:
        flash_rw_usr_api_read_from_main(out, olen);
        break;
    case BAK_SECTOR:
        flash_rw_usr_api_read_from_bak(out, olen);
        break;
    default:
        break;
    }

    return ret;
}

int flash_rw_usr_api_write(int type, uint8_t *data, int len)
{
    if (!data || !len) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    switch (type)
    {
    case MAIN_SECTOR:
        flash_rw_usr_api_write_to_main(data, len);
        break;
    case BAK_SECTOR:
        flash_rw_usr_api_write_to_bak(data, len);
        break;
    default:
        break;
    }

    return ret;
}

static int _test_1_on_power_data_valid(void)
{
    int ret = 0;
    const char src_info_filepath[] = "../src_4k_mem_file";

    // 加载4k分区，拿到内存
    ret = _init_mem_file(src_info_filepath, &src_info.fd, &src_info.size, &src_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 模拟构造的数据
    DevInfo_t dev_cfg_info = {0};
    ret = init_dev_info(&dev_cfg_info);
    if (ret != 0) {
        printf("[%s][%d]init_dev_info err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 写到主扇区（先擦除，后写入）
    ret = flash_rw_usr_api_write_to_main_sector((uint8_t *)&dev_cfg_info, sizeof(dev_cfg_info));
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write_to_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 读取主数据区，检查crc校验码
    uint8_t *buf = NULL;
    int buflen = 0;
    ret = flash_rw_usr_api_read_from_main_sector(&buf, &buflen);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_read_from_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    DevInfo_t tmp_dev_info = {0};

    memcpy(&tmp_dev_info, buf, sizeof(DevInfo_t));

    if (buf) {
        free(buf);
        buf = NULL;
    }

    _print_dev_info_val(&tmp_dev_info);

    uint32_t get_crc = 0;
    ret = get_dev_info_crc(&tmp_dev_info, &get_crc);
    if (ret != 0) {
        printf("[%s][%d]get_dev_info_crc err!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("[%s][%d]tmp_dev_info->crc32: 0x%08x\r\n", __func__, __LINE__, get_crc);

    uint32_t expect_crc = 0;
    ret = cal_dev_info_crc32(&tmp_dev_info, &expect_crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (expect_crc != get_crc) {
        printf("[%s][%d]check data failed!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("check data pass!\r\n");

    ret = _deinit_mem_file(&src_info.fd, &src_info.ptr, &src_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    return ret;
}

static int _test_2_recover_data_from_bak(void)
{
    int ret = 0;

    const char src_info_filepath[] = "../src_4k_mem_file";
    const char bak_info_filepath[] = "../1_bak_4k_mem_file";

    // 加载4k分区，拿到内存
    ret = _init_mem_file(src_info_filepath, &src_info.fd, &src_info.size, &src_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = _init_mem_file(bak_info_filepath, &bak1_info.fd, &bak1_info.size, &bak1_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    uint8_t *buf = NULL;
    int blen = 0;
    ret = flash_rw_usr_api_read_from_bak_sector(&buf, &blen);
    if (ret != 0 || !buf || !blen) {
        printf("[%s][%d]flash_rw_usr_api_read_from_bak_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    DevInfo_t tmp_dev_info = {0};

    memcpy(&tmp_dev_info, buf, sizeof(DevInfo_t));

    if (buf) {
        free(buf);
        buf = NULL;
    }

    uint32_t get_crc = 0;
    ret = get_dev_info_crc(&tmp_dev_info, &get_crc);
    if (ret != 0) {
        printf("[%s][%d]get_dev_info_crc err!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("[%s][%d]tmp_dev_info->crc32: 0x%08x\r\n", __func__, __LINE__, get_crc);

    uint32_t expect_crc = 0;
    ret = cal_dev_info_crc32(&tmp_dev_info, &expect_crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (expect_crc != get_crc) {
        printf("[%s][%d]check data failed!\r\n", __func__, __LINE__);
        // 备份区的数据校验不通过，直接将主分区，恢复默认设置
        printf("[%s][%d]start to reset main sector\r\n", __func__, __LINE__);
        goto _reset_src_sector;
    }

    // 备份区数据校验通过，进行备份恢复
    ret = flash_rw_usr_api_recover_from_bak((uint8_t*)&tmp_dev_info, sizeof(DevInfo_t));
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_recover_from_bak err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = _deinit_mem_file(&bak1_info.fd, &bak1_info.ptr, &bak1_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = _deinit_mem_file(&src_info.fd, &src_info.ptr, &src_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    return ret;

_reset_src_sector:
    ret = flash_rw_usr_api_reset_to_main_sector();
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_reset_to_main_sector err!\r\n", __func__, __LINE__);
        return ret;
    }

    return ret;
}

static int _test_3_reset_bak_sector(void)
{
    int ret = 0;

    const char src_info_filepath[] = "../src_4k_mem_file";

    // 加载4k分区，拿到内存
    ret = _init_mem_file(src_info_filepath, &src_info.fd, &src_info.size, &src_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 模拟构造的数据
    DevInfo_t dev_cfg_info = {0};
    memset(&dev_cfg_info, 0x00, sizeof(DevInfo_t));

    uint32_t crc = 0;
    ret = cal_dev_info_crc32(&dev_cfg_info, &crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return ret;
    }

    dev_cfg_info.crc_32 = crc;

    // 写到主扇区（先擦除，后写入）
    ret = flash_rw_usr_api_write_to_main_sector((uint8_t *)&dev_cfg_info, sizeof(dev_cfg_info));
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write_to_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 读取主数据区，检查crc校验码
    uint8_t *buf = NULL;
    int buflen = 0;
    ret = flash_rw_usr_api_read_from_main_sector(&buf, &buflen);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_read_from_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    memcpy(&dev_cfg_info, buf, sizeof(DevInfo_t));

    if (buf) {
        free(buf);
        buf = NULL;
    }

    _print_dev_info_val(&dev_cfg_info);

    uint32_t get_crc = 0;
    ret = get_dev_info_crc(&dev_cfg_info, &get_crc);
    if (ret != 0) {
        printf("[%s][%d]get_dev_info_crc err!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("[%s][%d]get_crc: 0x%08x\r\n", __func__, __LINE__, get_crc);

    uint32_t expect_crc = 0;
    ret = cal_dev_info_crc32(&dev_cfg_info, &expect_crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("[%s][%d]expect_crc: 0x%08x\r\n", __func__, __LINE__, expect_crc);

    if (expect_crc != get_crc) {
        printf("[%s][%d]check data failed!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = _deinit_mem_file(&src_info.fd, &src_info.ptr, &src_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    return ret; 
}

int flash_rw_usr_api_app(void)
{
    int ret = -1;

#if 0

    // ret = _test_1_on_power_data_valid();

    ret = _test_2_recover_data_from_bak();
#endif

    ret = _test_3_reset_bak_sector();

    return ret;
}

int flash_rw_usr_api_read_from_main_sector(uint8_t **out, int *olen)
{
    int ret = 0;
    ret = flash_rw_usr_api_read(MAIN_SECTOR, out, olen);
    return ret;
}

int flash_rw_usr_api_read_from_bak_sector(uint8_t **out, int *olen)
{
    int ret = 0;
    ret = flash_rw_usr_api_read(BAK_SECTOR, out, olen);
    return ret;
}

int flash_rw_usr_api_recover_from_bak(uint8_t *data, int dlen)
{
    if (!data || !dlen) {
        printf("[%s][%d]invalid input, check param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = flash_rw_usr_api_earse(MAIN_SECTOR);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_earse err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = flash_rw_usr_api_write_to_main(data, dlen);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write_to_main err!\r\n", __func__, __LINE__);
        return -1;
    }

    uint8_t *obuf = NULL;
    int obuflen = 0;
    ret = flash_rw_usr_api_read_from_main_sector(&obuf, &obuflen);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_read_from_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }

    DevInfo_t *info = (DevInfo_t*)obuf;
    
    uint32_t crc = 0;
    ret = get_dev_info_crc(info, &crc);
    if (ret != 0) {
        printf("[%s][%d]get_dev_info_crc err!\r\n", __func__, __LINE__);
        return -1;
    }

    uint32_t expect_crc = 0;
    ret = cal_dev_info_crc32(info, &expect_crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (expect_crc != crc) {
        printf("[%s][%d]check data err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 恢复数据成功
    printf("[%s][%d]recover data succeeful~!\r\n", __func__, __LINE__);

    return ret;
}

int flash_rw_usr_api_reset_to_main_sector(void)
{
    int ret = 0;

    ret = flash_rw_usr_api_earse(MAIN_SECTOR);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_earse err!\r\n", __func__, __LINE__);
        return -1;
    }

    DevInfo_t info;
    memset(&info, 0x00, sizeof(DevInfo_t));

    uint32_t crc = 0;

    ret = cal_dev_info_crc32(&info, &crc);
    if (ret != 0) {
        printf("[%s][%d]cal_dev_info_crc32 err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = set_dev_info_crc(&info, crc);
    if (ret != 0) {
        printf("[%s][%d]set_dev_info_crc err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = flash_rw_usr_api_write_to_main((uint8_t*)&info, sizeof(DevInfo_t));
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write_to_main err!\r\n", __func__, __LINE__);
        return -1;
    }

    return ret;
}