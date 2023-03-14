/**
 * 
 * @filename:pointer_to_pointer_data_test.c
 * @function:
 * @return:
 * @author:Zhanyou Zhou (gmrakari@outlook.com)
 * @date:2023/3/14 23:20
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *ptr;
    int ptr_len;
} tmp_test_header_t;

static void _read_struct_data(void *param);

static tmp_test_header_t tmp_test_header = {0};

static void _data(tmp_test_header_t **info, void *param)
{
    if (info == NULL || *info == NULL) return ;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    _read_struct_data(*info);

    printf("goto modify\r\n");

    char *ptr = (*info)->ptr;

    char cur_str[] = "dlorw olleh";
    int cur_str_len = strlen(cur_str);
    memcpy(ptr, cur_str, cur_str_len);
    ptr[cur_str_len] = '\0';

    _read_struct_data(*info);

    return ;
}

static void _read_struct_data(void *param)
{
    tmp_test_header_t *info = (tmp_test_header_t*)param;

    if (info == NULL) return ;

    printf("data:%s\r\n", info->ptr);
    printf("len:%d\r\n", info->ptr_len);

    return ;
}

static void _test(void)
{
    char str[] = "hello world";
    int str_len = strlen(str);
    tmp_test_header.ptr = NULL;
    tmp_test_header.ptr = malloc(sizeof(char) * str_len);
    if (tmp_test_header.ptr == NULL) {
        printf("malloc mem err\r\n");
        return ;
    }

    memcpy(tmp_test_header.ptr, str, str_len);
    tmp_test_header.ptr[str_len] = '\0';
    tmp_test_header.ptr_len = str_len;

    tmp_test_header_t *info = &tmp_test_header;
    _data(&info, (void*)0);

    if (tmp_test_header.ptr) { free(tmp_test_header.ptr); tmp_test_header.ptr = NULL; }

}

int main()
{
    _test();
}
