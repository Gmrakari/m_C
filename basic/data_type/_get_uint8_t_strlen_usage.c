#include <stdio.h>
#include <stdint.h> // uint8
#include <string.h> // memcpy
// #include <stdlib.h> // free

uint8_t *get_mac(uint8_t *mac)
{
    uint8_t *str = "AB:23:CE:10:E0:C0";

    printf("strlen str:%ld\r\n", strlen(str));

    // memcpy(mac, str, strlen(str));
    // mac = str;

    // printf("mac:%s, strlen mac:%ld\r\n", mac, strlen(mac));

    char *src1 = "type";
    char *src2 = "auth";

    char *src3 = "system";

    printf("strlen:%ld %ld %ld\r\n", strlen(src1), strlen(src2), strlen(src3));

    return mac;

}

int main() 
{
    uint8_t *mac;
    get_mac(mac);

    // printf("MAC:%s\r\n", mac);

    return 0;
}