#include "flash_rw_usr_info.h"

int get_dev_info_size(int *olen)
{
    if (!olen) {
        return -1;
    }

    *olen = sizeof(DevInfo_t);
    return *olen;
}

int init_dev_info(DevInfo_t *dev_info)
{
    if (!dev_info) {
        printf("[%s][%d]invalid in param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;
    DevInfo_t devInfo;
    memset(&devInfo, 0, sizeof(devInfo)); // Initialize the structure with zeros

    // Setting values for sTripleInfo
    devInfo.tripleInfo.magic_header = 0x12345678;
    strncpy(devInfo.tripleInfo.device_id, "12345678901234567", MAX_SIZE_OF_PRODUCT_ID);
    strncpy(devInfo.tripleInfo.device_secret, "secret123456789012345678901234567890", MAX_SIZE_OF_DEVICE_SECRET);
    strncpy(devInfo.tripleInfo.mac, "01:23:45:67:89:AB", MAX_SIZE_OF_MAC);
    strncpy(devInfo.tripleInfo.product_id, "prod1234", MAX_SIZE_OF_PRODUCT_ID);
    strncpy(devInfo.tripleInfo.device_name, "DeviceName123", MAX_SIZE_OF_DEVICE_NAME);

    // Setting values for DevInfo_t
    devInfo.magic_header = 0x87654321;
    strncpy(devInfo.device_name, "MyDevice123456789", sizeof(devInfo.device_name) - 1);
    
    devInfo.wifi_flag = 1; // Assume 1 means enabled
    strncpy(devInfo.wifi_ssid, "MyNetworkSSID", sizeof(devInfo.wifi_ssid) - 1);
    strncpy(devInfo.wifi_key, "MySecurePassword12345", sizeof(devInfo.wifi_key) - 1);
    
    strncpy(devInfo.mqtt_host, "mqtt.example.com", sizeof(devInfo.mqtt_host) - 1);
    devInfo.mqtt_port = 1883; // Default MQTT port

    devInfo.bind = 1; // Assume 1 means bound
    devInfo.net_cfg = 1; // Assume 1 means configured
    
    devInfo.is_bind = 1;
    devInfo.is_net_cfg = 1;
    devInfo.got_ip = 1;
    devInfo.bind_type = 1; // Assume 1 means wifi
    
    devInfo.uart1_baud_rate = 115200; // Typical baud rate
    
    strncpy(devInfo.country, "TW", sizeof(devInfo.country) - 1);
    devInfo.tz = 8; // Example timezone offset
    devInfo.temp = 22; // Example temperature
    devInfo.humidity = 50; // Example humidity
    
    strncpy((char*)devInfo.device_id, "DeviceID1234567890", sizeof(devInfo.device_id) - 1);
    // memcpy(devInfo.device_mac, "\x01\x23\x45\x67\x89\xAB", sizeof(devInfo.device_mac));
    memcpy(devInfo.device_mac, "\x01\x23\x45\x67\x89\xAB", sizeof(devInfo.device_mac));
    
    #if 0
    // Print some values to verify
    printf("magic_header: %08X\n", devInfo.magic_header);
    printf("Device Name: %s\n", devInfo.device_name);
    printf("wifi_flag: %d\n", devInfo.wifi_flag);
    printf("WiFi SSID: %s\n", devInfo.wifi_ssid);
    printf("WiFi Key: %s\n", devInfo.wifi_key);
    printf("MQTT Host: %s\n", devInfo.mqtt_host);
    printf("MQTT Port: %d\n", devInfo.mqtt_port);
    printf("Device bind: %d\n", devInfo.bind);
    printf("Device net_cfg: %d\n", devInfo.net_cfg);
    printf("Device is_bind: %d\n", devInfo.is_bind);
    printf("Device is_net_cfg: %d\n", devInfo.is_net_cfg);
    printf("Device got_ip: %d\n", devInfo.got_ip);
    printf("Device bind_type: %d\n", devInfo.bind_type);

    printf("UART Baud Rate: %u\n", devInfo.uart1_baud_rate);
    printf("Device country: %s\n", devInfo.country);
    printf("Device tz: %04X\n", devInfo.tz);
    printf("Device temp: %04X\n", devInfo.temp);
    printf("Device humidity: %d\n", devInfo.humidity);
    printf("Device device_id: %s\n", devInfo.device_id);

    printf("Device device_mac: %02X%02X%02X%02X%02X%02X\n", devInfo.device_mac[0] & 0xff, devInfo.device_mac[1] & 0xff, devInfo.device_mac[2] & 0xff, devInfo.device_mac[3] & 0xff, devInfo.device_mac[4] & 0xff, devInfo.device_mac[5] & 0xff);

    printf("Device tripleInfo device_id: %s\n", devInfo.tripleInfo.device_id);
    printf("Device tripleInfo device_secret: %s\n", devInfo.tripleInfo.device_secret);
    printf("Device tripleInfo mac: %s\n", devInfo.tripleInfo.mac);
    printf("Device tripleInfo product_id: %s\n", devInfo.tripleInfo.product_id);
    printf("Device tripleInfo device_name: %s\n", devInfo.tripleInfo.device_name);

    #endif

    memcpy(dev_info, &devInfo, sizeof(DevInfo_t));

    return ret;
}