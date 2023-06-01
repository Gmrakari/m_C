#include <stdio.h>
// #include <bits/types.h>
#include <stdint.h>
#include <string.h>

static int g_arr_data1[5] = {0};
static int g_arr_data2[5] = {0};
static int g_arr_all[10] = {0};

static void _arr_data_init(int *arr1, int arr1_len, int *arr2, int arr2_len);
static void _arr_data_print(int *arr, int arr_len);
static void m_memcpy(void);

void ret(void) {
    uint8_t *wifi_ssid = "abcasda";
    uint8_t *wifi_passwd = "1234568787";

    char ssid[32] = {0}, passwd[32] = {0};

    // memcpy(ssid, wifi_ssid, sizeof(wifi_ssid));
    // memcpy(passwd, wifi_passwd, sizeof(wifi_passwd));

    strncpy(ssid, wifi_ssid, sizeof(wifi_ssid));
    strncpy(passwd, wifi_passwd, sizeof(wifi_passwd));

    printf("u8_ssid:%s, u8_passwd:%s\r\n", wifi_ssid, wifi_passwd);
    printf("ssid:%s, passwd:%s\r\n", ssid, passwd);

}

void strcmp_test() {
    char *text1 = "abc";
    char *txt2 = "123";

    if (!strcmp(text1, "abc") && !strcmp(txt2, "123")) {
        printf("same\r\n");
    } else {
        printf("2\r\n");
    }
}

static void m_memcpy(void)
{

    size_t arr1_len = sizeof(g_arr_data1) / sizeof(g_arr_data1[0]);
    size_t arr2_len = sizeof(g_arr_data2) / sizeof(g_arr_data2[0]);

    _arr_data_init(g_arr_data1, arr1_len, g_arr_data2, arr2_len);

    _arr_data_print(g_arr_data1, arr1_len);
    _arr_data_print(g_arr_data2, arr2_len);


    int *data = g_arr_all;
    int data_len = 0;
    memcpy(data, g_arr_data1, sizeof(g_arr_data1));
    // data += sizeof(g_arr_data1);
    data += arr1_len;
    // data_len += sizeof(g_arr_data1);

    memcpy(data, g_arr_data2, sizeof(g_arr_data2));
    // data += sizeof(g_arr_data2);
    // data_len += sizeof(g_arr_data2);


    size_t len = sizeof(g_arr_all) / sizeof(g_arr_all[0]);

    _arr_data_print(g_arr_all, len);
}

static void _arr_data_init(int *arr1, int arr1_len, int *arr2, int arr2_len)
{
    int start_num1 = 1;
    for (int i = 0; i < arr1_len; i++) {
        arr1[i] = start_num1++;
    }

    printf("\r\n");

    int start_num2 = arr2_len;
    for (int i = 0; i < arr2_len; i++) {
        arr2[i] = start_num2++;
    }
    
}

static void _arr_data_print(int *arr, int arr_len)
{
    for (int i = 0; i < arr_len;i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

void _test_memcpy_arr(void)
{
    m_memcpy();
}

int main(int argc, char const *argv[]) {
    // ret();
    // strcmp_test();

    _test_memcpy_arr();
}
