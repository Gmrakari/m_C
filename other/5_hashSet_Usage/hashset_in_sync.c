#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc

#include <bits/types.h>
#include <time.h>

// 生产需求:
// 1. 本地设备数据库存有人脸图片，如果本地设备与Web绑定，需要将本地设备的人脸图片同步到Web
// 2. 原本是一次性上传，因为同步过程中，会出现同步/上传失败，需要重新上传，所以需要加缓存
// 3. 将缓存上传到web，缓存上传成功就更新缓存；一直将缓存更新完毕为止
// 4. 这里用hashset过滤掉已经成功更新到web

typedef struct {
    int *id_list;
    int id_list_len;
} db_param_t;

typedef struct {
    int id_list_cache[0];
    int id_list_cache_len;
    int id_list_succeeful[0];
    int id_list_succeeful_len;
    int id_list_need_upload_list[0];
    int id_list_need_upload_list_len;
} send_op_param_t;

typedef struct {
    int *id_list_cache;
    int id_list_cache_len;
    int *id_upload_succeeful_list;
    int id_upload_succeeful_list_len;
    int *id_list_need_upload_list;
    int id_list_need_upload_list_len;
} send_data_t;

// static db_param_t      db_param      = {0};
// static send_op_param_t send_op_param = {0};
static send_data_t send_data = {NULL, 0, NULL, 0, NULL, 0};


void _hashset_arr_usage(){
    int arr[10] = {0, 1, 2, 3};
    // memset(arr, -1, sizeof(arr));

    int dup[10] = {0, 1, 2, 2, 4, 5, 6, 7, 8, 9};

    // memcpy(arr, dup, sizeof(arr));

    int hash_arr[10] = {-2};
    memset(hash_arr, -2, sizeof(hash_arr));

    int dup_cache_arr[10];
    int idx = 0;

    for (int i = 0;i < 10; i++) {
        int num = arr[i];
        printf("==num arr:%d\r\n", num);
        hash_arr[num] = 1;
    }

    for (int i = 0; i < 10; i++) {
        int num = dup[i];
        printf("num dup:%d\r\n", num);
        // if (hash_arr[num] == 1) {
        //     dup_cache_arr[idx++] = num;
        // }

        if (!(hash_arr[num] == 1)) {
            dup_cache_arr[idx++] = num;
        }
    }

    for (int i = 0; i < idx; i++) {
        printf("dup_cache_arr[%d]:%d\r\n", i, dup_cache_arr[i]);
    }
}

void print_arr(int *arr, int arr_len)
{
    for (int i = 0;i < arr_len; i++) {
        printf("[%d]: %d\r\n", i, arr[i]);
    }
    printf("\r\n");
}

void test() {
    int arr[10] = {0, 1, 2, 3};

    size_t arr_len = sizeof(arr);
    size_t arr_len_2 = sizeof(arr) / sizeof(arr[0]);

    printf("arr_len:%d, arr_len_2:%d\r\n", (int)arr_len, (int)arr_len_2);
    printf("arr len:%ld\r\n", sizeof(arr) / sizeof(int));

    int mem_arr[10] = {0};

    print_arr(arr, arr_len_2);

    // memcpy(mem_arr, arr, arr_len_2 * sizeof(arr[0]));
    memcpy(mem_arr, arr, sizeof(arr));

    print_arr(mem_arr, arr_len_2);

}

int init_db_param(int len)
{
    int ret = 0;
    if (len < 0) {
        ret = -1;
    }

    return ret;
}

db_param_t* create_db_param(int len)
{
    db_param_t *param = malloc(sizeof(db_param_t));
    if (param == NULL) {
        return NULL;
    }

    param->id_list = malloc(len * sizeof(int));
    if (param->id_list == NULL) {
        free(param);
        return NULL;
    }
    param->id_list_len = len;

    return param;
}

void simulate_send_op_func()
{
    db_param_t *db = NULL;
    size_t len = 20;
    db = create_db_param(len);
    if (db == NULL) 
        return ;

    if (db->id_list == NULL)
        return ;

    memset(db->id_list, -1, sizeof(int) * db->id_list_len);

    for (int i = 0; i < db->id_list_len; i++) {
        db->id_list[i] = i;
    }

    print_arr(db->id_list, db->id_list_len);

    if (db->id_list) {
        free(db->id_list);
        db->id_list = NULL;
    }

    if (db) {
        free(db);
        db = NULL;
    }
}



int main()
{
    // test();

    // simulate_send_op_func();
}