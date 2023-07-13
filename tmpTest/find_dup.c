#include <stdio.h>
#include <string.h>
#define ARR_LEN (10)

static int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 1};

static void my_swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static void swap_test()
{
    int a = 10;
    int b = 20;

    printf("before a:%d, b:%d\r\n", a, b);

    my_swap(&a, &b);

    printf("after a:%d, b:%d\r\n", a, b);
}

static int partition(int *arr, int arr_len, int low, int high)
{
    int pv = arr[high];
    while (low < high && arr[low] <= pv) {
        low++;
    }
    my_swap(&arr[low], &arr[high]);
    while (low < high && arr[high] >= pv) {
        high--;
    }
    my_swap(&arr[low], &arr[high]);
    return low;
}

void find_func(int *arr, int len) {
    int visited[ARR_LEN] = {-1};

    for (int i = 0; i < 10; i++) {
        if (visited[arr[i]] != -1) {
            printf("dup value:%d found at index:%d\r\n", arr[i], i);
        } else {
            visited[arr[i]] = i;
            // printf("arr[%d]:%d\r\n", i, arr[i]);
        }
    }
}

void call_test(int *arr, int len) {

    find_func(arr, len);
}

void qs(int *arr, int len)
{

}

// 1 2 3 4 5 6 7 8
// low   pv     high

void idx(int low, int high, int *arr, int len)
{

}

void num_len()
{
    int timestamp = 0;

}

void _print_arr(){
    
    int arr[ARR_LEN] = {-1};
    memset(arr, -1, sizeof(arr));

    for (int i = 0; i < ARR_LEN; i++) {
        printf("arr[%d]:%d\r\n", i,arr[i]);
    }
}

void _print_2d_arr()
{
    int arr_2d[ARR_LEN][ARR_LEN] = {-1};
    memset(arr_2d, -1, sizeof(arr_2d));

    for (int i = 0;i < ARR_LEN; i++) {
        for (int j = 0; j < ARR_LEN; j++) {
            printf("arr_2d[%d][%d]:%d\r\n", i, j, arr_2d[i][j]);
        }
    }
}

void _print_arr_of_arr()
{
    int upload_id_list[ARR_LEN] = {-1};
    int id_is_upload[ARR_LEN] = {-1};

    memset(upload_id_list, -1, sizeof(upload_id_list));
    memset(id_is_upload, -1, sizeof(id_is_upload));

    for (int i = 0; i < ARR_LEN; i++) {
        upload_id_list[i] = i;
    }

}

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


void _tst_pritn()
{
    // _print_arr();
    // _print_2d_arr();
    _hashset_arr_usage();
}

typedef struct {
	int id;
	int is_upload_flag;
	int id_list[10];
} db_param_t;

typedef struct {
    int id_list[10];
} web_recv_t;

typedef struct {
    int need_upload_id_list[10];
    int need_upload_id_list_len;
    int upload_id_list_cache[10];
    int upload_id_list_cache_len;
    int successful_upload_id_list[10];
    int successful_uoload_id_list_len;
    int sync_flag; 
} db_param_upload_sync_data_t;

static db_param_t db_param = {0};
static web_recv_t web_param = {0};
static db_param_upload_sync_data_t upload_sync_param = {0};

void m_send_to_web() {

    for (int i = 0; i < 10; i++) {
        db_param.id = i;
        db_param.id_list[i] = db_param.id;
        upload_sync_param.need_upload_id_list[i] = db_param.id;
    }

    for (int i = 0; i < 10; i++) {
        // db_param send to web
        web_param.id_list[i] = db_param.id_list[i];
        upload_sync_param.successful_upload_id_list[i] = db_param.id_list[i];
    }
}

int main()
{
    // int i = 10;
    // printf("before i:%d\r\n", i);
    // while (i) {
    //     printf("i:%d\r\n", i);
    //     i--;
    // }

    // call_test(arr, 10);
    // swap_test();

    // int cur_num = 0;
    // cur_num = 3;

    // if (cur_num % 50 == 0) {
    //     printf("cur_num:%d\r\n", cur_num);

    // }
    // printf("cur_num%50:%d\r\n", cur_num % 50);

    _tst_pritn();
}