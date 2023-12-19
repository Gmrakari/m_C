#include <stdio.h>
#include <stdlib.h> // malloc

#include "read_file_info_app.h"
#include "read_file.h"
#include "format_pairs_to_json.h"

int read_file_info_app() {
    int u32Ret = 0;
    char path[FILE_PATH_MAX_LEN] = {0};
    if (0 != (u32Ret = get_config_file_path(path))) 
        return -1;

    param_info_t info = {0};
    char key_name_arr[PARAM_INFO_T_NUM_ELEMENTS][PARAM_INFO_T_STR_MAX_LEN] = {0};
    if (0 != (u32Ret = read_file(path, key_name_arr, &info)))
        return -1;

    size_t pairs_num = PARAM_INFO_T_NUM_ELEMENTS;
    pairs_info_t *pairs = (pairs_info_t *)malloc(sizeof(pairs_info_t) * pairs_num) ;
    if (!pairs) return -1;

    if (0 != (u32Ret = gen_pairs_info(&info, key_name_arr, pairs_num, pairs))) {
        free_pairs_info(pairs, pairs_num);
        return -1;
    }

    cJSON *obj = format_pairs_to_json(pairs, pairs_num);
    if (!obj) {
        free_pairs_info(pairs, pairs_num);
        return -1;
    }

    free_pairs_info(pairs, pairs_num);

    char *str = cJSON_PrintUnformatted(obj);
    if (str) {
        printf("json data:%s\r\n", str);
        free(str);
        str = NULL;
    }

    cJSON_Delete(obj);

    return 0;
}
