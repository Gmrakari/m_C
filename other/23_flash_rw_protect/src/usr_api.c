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

static int _flash_rw_get_fd_mem(const char *filepath, int fd, uint8_t **ptr)
{
    if (!filepath) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;
    fd = open(filepath, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        printf("[%s][%d]open err!\r\n", __func__, __LINE__);
        return -1;
    }

    // 确保文件大小与映射内存的大小一致
    if (ftruncate(fd, FLASH_RW_DEFAULT_MEM_SIZE) == -1) {
        perror("ftruncate failed");
        close(fd);
        return -1;
    }

    uint8_t *mem_ptr = NULL;

    mem_ptr = mmap(NULL, FLASH_RW_DEFAULT_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem_ptr == MAP_FAILED) {
        printf("[%s][%d]mmap err!\r\n", __func__, __LINE__);
        close(fd);
        return -1;

    }

    *ptr = mem_ptr;

    return ret;
}

static int _deinit_mem_file(int fd, uint8_t *ptr, int size)
{
    if (!ptr) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    if (munmap(ptr, size) == -1) {
        perror("munmap failed");
        close(fd);
        ret = -1;
    }

    close(fd);

    return ret;
}

static int _init_mem_file(const char *filepath, int fd, int size, uint8_t *ptr)
{
    if (!filepath) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    ret = _flash_rw_get_fd_mem(filepath, fd, &ptr);
    if (ret != 0) {
        printf("[%s][%d]_flash_rw_get_fd_mem failed\r\n", __func__, __LINE__);
        return ret;
    }

    size = FLASH_RW_DEFAULT_MEM_SIZE;

    memset(ptr, 0xff, size);

    if (munmap(ptr, size) == -1) {
        perror("munmap failed");
        close(fd);
        ret = -1;
    }

    close(fd);

    return ret;
}

static int _load_src_mem_sector(const char *filepath)
{

}

uint32_t calculate_crc32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (uint32_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc ^ 0xFFFFFFFF;
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
    int cal_crc32 = 0;
    cal_crc32 = calculate_crc32(data, len);

    printf("[%s][%d]calculate_crc32 val: %u, hex: 0x%08X\r\n", __func__, __LINE__, cal_crc32, cal_crc32);

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
printf("[%s][%d]\r\n", __func__, __LINE__);
    memcpy(src_info.ptr, data, len);
printf("[%s][%d]\r\n", __func__, __LINE__);
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
printf("[%s][%d]\r\n", __func__, __LINE__);
    ret = flash_rw_usr_api_earse(MAIN_SECTOR);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_earse err!\r\n", __func__, __LINE__);
        return -1;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    ret = flash_rw_usr_api_write(MAIN_SECTOR, data, data_len);
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write err!\r\n", __func__, __LINE__);
        return -1;
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

int flash_rw_usr_api_app(void)
{
    int ret = -1;

    const char src_info_filepath[] = "../src_4k_mem_file";
    const char bak_info_filepath[] = "../1_bak_4k_mem_file";

    ret = _init_mem_file(src_info_filepath, src_info.fd, src_info.size, src_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    ret = _init_mem_file(bak_info_filepath, bak1_info.fd, bak1_info.size, bak1_info.ptr);
    if (ret != 0) {
        printf("[%s][%d]_init_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }

    DevInfo_t dev_cfg_info = {0};
    ret = init_dev_info(&dev_cfg_info);
    if (ret != 0) {
        printf("[%s][%d]init_dev_info err!\r\n", __func__, __LINE__);
        return -1;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    ret = flash_rw_usr_api_write_to_main_sector((uint8_t *)&dev_cfg_info, sizeof(dev_cfg_info));
    if (ret != 0) {
        printf("[%s][%d]flash_rw_usr_api_write_to_main_sector err!\r\n", __func__, __LINE__);
        return -1;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    ret = _deinit_mem_file(src_info.fd, src_info.ptr, src_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    ret = _deinit_mem_file(bak1_info.fd, bak1_info.ptr, bak1_info.size);
    if (ret != 0) {
        printf("[%s][%d]_deinit_mem_file err!\r\n", __func__, __LINE__);
        return -1;
    }printf("[%s][%d]\r\n", __func__, __LINE__);

    return ret;
}

