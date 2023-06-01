#include <stdio.h>
#include <string.h>

int i = 0;

void ret(void) {

    i++;
    if (i > 1){
        i = 0;
    }

    printf("i:%d\r\n", i);
}

void get_strlen(void)
{
    // printf("str:%ld\r\n", strlen("84:0D:8E:6C:3F:24"));
    char *str = "84:0D:8E:6C:3F:24";
    printf("strlen:%ld\r\n", strlen(str));
    printf("sizeof:%ld\r\n", sizeof(str));

}

void set_mac(char *mac) {
    char net_mac[6];
    // char net_mac[6] = {0};

    // strcpy(net_mac[0], "84");
    // strcpy(net_mac[1], "0D");
    // strcpy(net_mac[2], "8E");
    // strcpy(net_mac[3], "6C");
    // strcpy(net_mac[4], "3F");
    // strcpy(net_mac[5], "24");

    memset(net_mac, 0, sizeof(net_mac) * 6);

    // strcpy(net_mac[0], '8');
    // strcpy(net_mac[1], '0');
    // strcpy(net_mac[2], '8');
    // strcpy(net_mac[3], '6');
    // strcpy(net_mac[4], '3');
    // strcpy(net_mac[5], '2');



    // strcpy(net_mac[0], 8);
    // strcpy(net_mac[1], 0);
    // strcpy(net_mac[2], 8);
    // strcpy(net_mac[3], 6);
    // strcpy(net_mac[4], 3);
    // strcpy(net_mac[5], 2);

    // 840D8E6C3F24
    memcpy(mac, net_mac, 6);
    return ;
}

void _str_op(void)
{
    char get_device_mac[6] = {0};

    set_mac(get_device_mac);

    printf("get_device_mac:%.2x%.2x%.2x%.2x%.2x%.2x\r\n", get_device_mac[0], get_device_mac[1], get_device_mac[2], get_device_mac[3], get_device_mac[4], get_device_mac[5]);


    // 840D8E6C3F24
}

int main(int argc, char const *argv[]) {
    // ret();
    // ret();
    // ret();

    get_strlen();

    // _str_op();

}
