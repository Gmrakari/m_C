#include <stdio.h>
#include <stdint.h>

int main() 
{
    uint16_t _desc_str[32 + 1] = {0};

    uint32_t chr_count = 0;

    uint8_t tud_network_mac_addr[6] = {0xA1, 0x02, 0x96, 0x00, 0xE4, 0xB8};

    for (unsigned i = 0; i < sizeof(tud_network_mac_addr); i++) {
        _desc_str[1 + chr_count++] = "0123456789ABCDEF"[(tud_network_mac_addr[i] >> 4) & 0xf];
        printf("%04X", _desc_str[1 + chr_count]);

        _desc_str[1 + chr_count++] = "0123456789ABCDEF"[(tud_network_mac_addr[i] >> 0) & 0xf];
        printf("%04X", _desc_str[1 + chr_count]);
        printf("\r\n");
    }

    uint8_t *ptr = (uint8_t *)_desc_str;
    int len = sizeof(tud_network_mac_addr) + 1;
    for (uint16_t i = 0; i < len; i++) {
        printf("%02X", ptr[i]);
        if (i != sizeof(_desc_str) - 1) 
            printf(" ");
    }
    printf("\r\n");

    return 0;
}
