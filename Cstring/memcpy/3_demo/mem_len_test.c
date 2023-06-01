#include <stdio.h>
#include <string.h>
#include <stdint.h> // uint8
#include <stdlib.h>

static void _str_get(char *data);
static void _oringin_data();
static void _test();

static void _str_gen(uint8_t *data, uint16_t len)
{
    char *in_data = (char*)malloc(sizeof(char) * len);
    memcpy(in_data, data, len);
    in_data[len] = '\0';

    _str_get(in_data);

    printf("in_data:%s\r\n", in_data);

    free(in_data);

    return ;
}


static void _str_get(char *data)
{
    if (data == NULL) return ;
    printf("data:%s\r\n", data);
    return ;
}

static void _oringin_data()
{
    char str[10] = "132456789";
    uint16_t str_size = strlen(str);
    printf("str_size:%d\r\n", str_size);

    _str_gen(str, str_size);
}

static void _test()
{
    _oringin_data();
}

int main()
{
    _test();
    return 0;
}

