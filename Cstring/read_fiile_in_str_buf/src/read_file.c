#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // perror
#include <ctype.h> // isspace

#include "read_file.h"
#include "format_pairs_to_json.h"
#include "read_file_info_app.h"

char *str_trim(char *str) {
    while (isspace((unsigned char)*str)) str++; // 跳过前导空格

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--; // 跳过尾随空格

    *(end + 1) = '\0'; // 截断尾随空格

    return str;
}

int read_file(const char *filepath, char (*key_str_arr)[PARAM_INFO_T_STR_MAX_LEN], param_info_t *info) {
    if (!filepath || !key_str_arr || !info) return -1;

    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) return -1;

    size_t i = 0;
    char line[CONFIG_INFO_LINE_MAX_LEN] = {0};
    while (fgets(line, sizeof(line), fp)) {
        char *pos = strchr(line, '=');
        if (pos != NULL && pos != line && *(pos + 1) != '\0') {
            *pos = '\0';

            char *key = str_trim(line);
            char *value = str_trim(pos + 1);
            value[strcspn(value, "\n")] = '\0';

            if (!strcmp(key, "pid")) {
                strncpy(info->pid, value, sizeof(info->pid));
            } else if (!strcmp(key, "uuid")) {
                strncpy(info->uuid, value, sizeof(info->uuid));
            } else if (!strcmp(key, "token")) {
                strncpy(info->token, value, sizeof(info->token));
            } else if (!strcmp(key, "secret")) {
                strncpy(info->secret, value, sizeof(info->secret));
            } 
            strncpy(key_str_arr[i++], key, PARAM_INFO_T_STR_MAX_LEN - 1);
            key_str_arr[i][PARAM_INFO_T_STR_MAX_LEN - 1] = '\0';
        }
    }
    fclose(fp);
    return 0;
}

int get_app_file_path(char *path) {
    if (!path) return -1;

    char exe_path[FILE_PATH_MAX_LEN];
    ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);

    if (len == -1) {
        perror("get app file path err");
        return -1;
    }

    exe_path[len] = '\0';

    strncpy(path, exe_path, len);
    return 0;
}

int get_config_file_path(char *path) {
    if (!path) return -1;

    int u32Ret = 0;
    char exe_path[FILE_PATH_MAX_LEN] = {0};

    if (0 != (u32Ret = get_app_file_path(exe_path))) 
        return -1;

    char *last_slash = strrchr(exe_path, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';
    } else {
        strcpy(exe_path, ".");
    }

    char *last_but_one_slash = strrchr(exe_path, '/');
    if (last_but_one_slash != NULL) {
        *last_but_one_slash = '\0';
    } else {
        strcpy(exe_path, ".");
    }

    char config_path[FILE_PATH_MAX_LEN] = {0};
    snprintf(config_path, sizeof(config_path), "%s"CONFIG_PATH, exe_path);
    strncpy(path, config_path, sizeof(config_path));

    return 0;
}

int gen_pairs_info(param_info_t *info, const char (*info_arr)[PARAM_INFO_T_STR_MAX_LEN], size_t pairs_num, pairs_info_t *pairs) {
    if (!info || !info_arr || pairs_num == 0 || !pairs) return -1;

    for (size_t i = 0; i < pairs_num; i++) {
        pairs[i].key = strdup(info_arr[i]);

        if (!strcmp(info_arr[i], "pid")) {
            pairs[i].value = strdup(info->pid);
        } else if (!strcmp(info_arr[i], "uuid")) {
            pairs[i].value = strdup(info->uuid);
        } else if (!strcmp(info_arr[i], "secret")) {
            pairs[i].value = strdup(info->secret);
        } else if (!strcmp(info_arr[i], "token")) {
            pairs[i].value = strdup(info->token);
        } else {
            pairs[i].value = NULL;
        }

        if (!pairs[i].key || !pairs[i].value) { // 内存分配失败
            free_pairs_info(pairs, i);
            return -1;
        }
    }

    return 0;
}

int free_pairs_info(pairs_info_t *pairs, size_t pairs_num) {
    for (size_t i = 0; i < pairs_num; i++) {
        if (pairs[i].key) { free(pairs[i].key); pairs[i].key = NULL; }
        if (pairs[i].value) { free(pairs[i].value); pairs[i].value = NULL; }
    }
    free(pairs);
    pairs = NULL;
    return 0;
}