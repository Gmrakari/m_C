#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint8_t data_len;
    uint8_t *data;
} __attribute__((packed)) data_msg_t;

int main() {
    data_msg_t msg = {0};

    uint8_t data_list[] = {0x01, 0x02};

    msg.data_len = sizeof(data_list) / sizeof(data_list[0]);
    msg.data = malloc(sizeof(uint8_t) * msg.data_len);

    if (msg.data == NULL) {
        // Handle memory allocation failure
        return 1;
    }

    memcpy(msg.data, data_list, msg.data_len);

    uint8_t *ptr = (uint8_t*)&msg;
    size_t ptr_len = sizeof(msg.data_len) + msg.data_len;
    for (size_t i = 0; i < ptr_len; i++) {
        printf("%02X ", ptr[i]);
    }

    printf("\n");

    if (msg.data) {
        free(msg.data);
        msg.data = NULL;
    }

    return 0;
}
