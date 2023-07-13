#include <stdio.h>
#include <stdint.h> // uint8
#include <string.h>

#define UARTP_FRAME_SIZE (0xFFFF)

typedef struct
{
    uint16_t head;
    uint16_t len;
    uint16_t crc;
    uint8_t cmd;
    uint8_t data[UARTP_FRAME_SIZE - 7];
}__attribute__((packed)) mfhex_ptl_t;

typedef struct {
    uint16_t id;
}__attribute__((packed)) req_t;

static void test_type_func()
{
    uint8_t data[] = "0x1FFF";
    mfhex_ptl_t ptl_buf = {0};

    printf("data:%s\r\n", data);
    printf("Hex data:%02x\r\n", data);
    printf("\r\n");

    strncpy(ptl_buf.data, data, sizeof(data));

    printf("ptl_buf.data:%s\r\n", ptl_buf.data);
    printf("Hex:ptl_buf.data:%02x\r\n", ptl_buf.data);
    printf("\r\n");

    req_t *req = (req_t *)ptl_buf.data;

    uint16_t person_id = req->id;
    printf("req->id:%d\r\n", req->id);
    printf("Hex: req->id:%02x\r\n", req->id);
    printf("person id:%d\r\n", person_id);
    printf("Hex: person id:%02x\r\n", person_id);
    printf("\r\n");

    if (person_id == 0x1FFF) {
        printf("0x1fff\r\n");
    }
}

int main()
{
    test_type_func();
}
