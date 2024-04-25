#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char _get_wifi_rssi(const char *ssid)
{
    char c_ssid[] = "WIFI_2.4G";
    char value = 0;
    if (!strcmp(ssid, c_ssid)) {
        value = -10;
    }
    return value;
}

static void _test_01() {
    char ssid[] = "WIFI_2.4G";
    int rssi_value = 0;
    rssi_value = _get_wifi_rssi(ssid);
    printf("rssi_value:%d\r\n", rssi_value);

    int8_t hex_data = (int8_t)rssi_value;
    printf("%d %02X\r\n", hex_data, hex_data);

    int negative_number = -1;

    printf("负数的十进制表示为：%d\n", negative_number);
    printf("负数的十六进制表示为：%02X\n", negative_number);           // %X 格式化输出十六进制数
    printf("负数的十六进制表示(带前缀)为: 0x%X\n", negative_number);   // 带有前缀的十六进制表示

    char wifi_value = -30;
    int8_t send_wifi_value = abs(wifi_value);
    printf("send_wifi_value:%02X, %d\r\n", send_wifi_value, send_wifi_value);

    return ;
}

int main() {
    _test_01();
    return 0;
}
