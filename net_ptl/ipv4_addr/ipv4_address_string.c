#include <stdio.h>
#include <stdint.h>

#define USE_IPV4_ADDR_FROM_LEFT_TO_RIGHT (0)

typedef struct {
    uint8_t octet[4];
} ipv4_address_t;

void u32_to_u8_ip(const uint32_t ipv4_address, uint8_t *ip_string_arr, size_t ip_string_arr_len) {
    if (!ip_string_arr || ip_string_arr_len == 0) return ;

    ipv4_address_t ipv4 = { .octet[0] = (ipv4_address >> 24) & 0xFF,
                            .octet[1] = (ipv4_address >> 16) & 0xFF,
                            .octet[2] = (ipv4_address >> 8) & 0xFF,
                            .octet[3] = ipv4_address & 0xFF };

    snprintf(ip_string_arr, ip_string_arr_len, "%d.%d.%d.%d", ipv4.octet[0], ipv4.octet[1], ipv4.octet[2], ipv4.octet[3]);

#if USE_IPV4_ADDR_FROM_LEFT_TO_RIGHT
    ipv4_address_t ipv4_v2 = { .octet[0] = ipv4_address & 0xFF,
                            .octet[1] = (ipv4_address >> 8) & 0xFF,
                            .octet[2] = (ipv4_address >> 16) & 0xFF,
                            .octet[3] = (ipv4_address >> 24) & 0xFF };

    uint8_t ip_v4_addr[16] = {0};
    snprintf(ip_v4_addr, sizeof(ip_v4_addr), "%d.%d.%d.%d", ipv4_v2.octet[0], ipv4_v2.octet[1], ipv4_v2.octet[2], ipv4_v2.octet[3]);
    printf("%s\r\n", ip_v4_addr);
#endif

    return ;
}

// 0000 0000 0000 0000 0000 0000 0000 0000
// ptr[0] ptr[1] ptr[2] ptr[3] ptr[4] ptr[5] ptr[6]
// 192    .      168    .      1      .      1

void test() {
    uint32_t addr = 0xC0A80101;
    uint8_t addr_string[16] = {0};

    size_t addr_string_len = sizeof(addr_string) / sizeof(addr_string[0]);

    u32_to_u8_ip(addr, addr_string, addr_string_len);

    printf("%s\r\n", addr_string);

    return ;
}

int main() {
    test();
    printf("hello world\r\n");
}