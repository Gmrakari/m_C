#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    uint16_t header;
    uint8_t type;
    uint8_t arr[3];
    uint16_t end;
} __attribute__((packed)) test_member_st_t;

static void _print_mem(test_member_st_t *data)
{
    if (!data) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return ;
    }

    printf("header: %04X\r\n", data->header);
    printf("type: %02X\r\n", data->type);

    printf("arr:\r\n");
    for (int i = 0; i < sizeof(data->arr) - 1; i++) {
        printf("%02X", data->arr[i]);
        if (i != sizeof(data->arr) - 1) {
            printf(" ");
        }
    }
    printf("\r\n");

    printf("end: %04X\r\n", data->end);

    return ;
}

static void _serialize_data_use_ptr(test_member_st_t *data, uint8_t **out, uint16_t *out_len)
{
    if (!data) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return ;
    }

    size_t buflen = sizeof(test_member_st_t);
    uint8_t *buffer = malloc(buflen);
    if (!buffer) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return ;
    }

    memset(buffer, 0x00, buflen);
    uint8_t *ptr = buffer;
    uint16_t offset = 0;

    *(uint16_t *)ptr = data->header;
    ptr += sizeof(uint16_t);

    *ptr = data->type;
    ptr += sizeof(uint8_t);

    // for (int i = 0; i < sizeof(data->arr); i++) {
    //     *ptr = data->arr[i];
    //     ptr += sizeof(uint8_t);
    // }

    memcpy(ptr, data->arr, sizeof(data->arr));
    ptr += sizeof(data->arr);

    *(uint16_t *)ptr = data->end;
    ptr += sizeof(uint16_t);

    offset = ptr - buffer;

    *out = buffer;
    *out_len = offset;

    return ;
}

static void _deserialize_data_use_ptr(const uint8_t *buffer, uint16_t buffer_len, test_member_st_t **out_data)
{
    if (!buffer || !buffer_len) {
        printf("[%s][%d]invalid param\r\n", __func__, __LINE__);
        return ;
    }

    uint16_t offset = 0;

    uint16_t st_mem_len = sizeof(test_member_st_t);
    test_member_st_t *st_mem = malloc(st_mem_len);
    if (!st_mem) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return ;
    }

    memset(st_mem, 0x00, st_mem_len);

    const uint8_t *ptr = buffer;

    while (offset < buffer_len) {
        st_mem->header = *(uint16_t *)(ptr + offset);
        offset += sizeof(uint16_t);

        st_mem->type = *(ptr + offset);
        offset += sizeof(uint8_t);

        // memcpy(st_mem->arr, ptr + offset, sizeof(st_mem->arr));
        // offset += sizeof(st_mem->arr);

        for (int i = 0; i < sizeof(st_mem->arr); i++) {
            st_mem->arr[i] = *(ptr + offset);
            offset += sizeof(uint8_t);
        }

        st_mem->end = *(uint16_t *)(ptr + offset);
        offset += sizeof(uint16_t);
    }

    *out_data = st_mem;

    return ;
}

static test_member_st_t* _init_mem(void)
{
    test_member_st_t *mem1 = malloc(sizeof(test_member_st_t));
    if (!mem1) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return NULL;
    }

    mem1->header = 0x1234;
    mem1->type = 1;
    strncpy(mem1->arr, "12", sizeof(mem1->arr));
    mem1->end = 0x5678;

    return mem1;
}

int main() 
{
    test_member_st_t *mem1 = _init_mem();
    if (!mem1) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    _print_mem(mem1);

    uint8_t *serial_buf = NULL;
    uint16_t serial_buf_len = 0;

    _serialize_data_use_ptr(mem1, &serial_buf, &serial_buf_len);

    if (mem1) {
        free(mem1);
        mem1 = NULL;
    }

    test_member_st_t *mem2 = NULL;

    _deserialize_data_use_ptr(serial_buf, serial_buf_len, &mem2);

    if (serial_buf) {
        free(serial_buf);
        serial_buf = NULL;
    }

    _print_mem(mem2);

    if (mem2) {
        free(mem2);
        mem2 = NULL;
    }

    return 0;
}
