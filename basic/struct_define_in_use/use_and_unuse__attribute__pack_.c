#include <stdio.h>
#include <stdint.h> // uint8

// __attribute__((packed))的作用:
// 告诉编译器不要对结构体进行字节对齐，即取消默认的对齐方式。
// 结构体的字段按照定义的顺序依次排列，不会在字段之间添加任何填充字节。
// 这样可以确保结构体的大小与字段的实际占用空间一致，没有额外的内存浪费。
typedef struct  {
    uint8_t link_status;    // 1
    uint8_t bssid[6];       // 1 * 6 = 6
    uint8_t ssid[32 + 1];   // 1 * 33 = 33
    uint8_t channel;        // 1
    int8_t rssi;            // 1
    uint8_t auth_mode;      // 1
    uint8_t cipher;         // 1
}__attribute__((packed)) use_wifi_ap_record_t;  // 1 + 6 + 33 + 1 + 1 + 1 + 1 = 44

// 没有使用任何修饰符，因此采用了默认的对齐方式。
// 默认情况下，编译器会根据平台的要求对结构体进行字节对齐，以提高访问效率。
// 这意味着在字段之间可能会添加一些填充字节，以保证字段在内存中的对齐
typedef struct  {
    uint8_t link_status;
    uint8_t bssid[6];
    uint8_t ssid[32 + 1];
    uint8_t channel;
    int8_t rssi;
    uint8_t auth_mode;
    uint8_t cipher;
} unuse_wifi_ap_record_t;

static use_wifi_ap_record_t use_att_record;
static unuse_wifi_ap_record_t unuse_att_record;

void test_case()
{
    printf("sizeof use_att_record:%ld\r\n", sizeof(use_att_record));
    printf("sizeof unuse_att_record:%ld\r\n", sizeof(unuse_att_record));
}

// 打印结果一致 44
int main()
{
    test_case();
}