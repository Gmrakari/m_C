#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> // perror

#include "read_file.h"
#include "format_str_to_json.h"
#include "read_file_info_app.h"

#define CONFIG_INFO_LINE_MAX_LEN (128)

char *str_trim(char *str) {
    while (isspace((unsigned char)*str)) str++; // 跳过前导空格

    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--; // 跳过尾随空格

    *(end + 1) = '\0'; // 截断尾随空格

    return str;
}

int read_file(const char *filepath) {
    if (!filepath) return -1;

    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) return -1;

    char pid[FILE_PATH_MAX_LEN] = {0};
    char uuid[FILE_PATH_MAX_LEN] = {0};
    char token[FILE_PATH_MAX_LEN] = {0};
    char secret[FILE_PATH_MAX_LEN] = {0};

    char line[CONFIG_INFO_LINE_MAX_LEN] = {0};
    while (fgets(line, sizeof(line), fp)) {
        char *pos = strchr(line, '=');
        if (pos != NULL && pos != line && *(pos + 1) != '\0') {
            *pos = '\0';

            char *key = str_trim(line);
            char *value = str_trim(pos + 1);
            value[strcspn(value, "\n")] = '\0';

            if (!strcmp(key, "pid")) {
                strncpy(pid, value, sizeof(pid));
            } else if (!strcmp(key, "uuid")) {
                strncpy(uuid, value, sizeof(uuid));
            } else if (!strcmp(key, "token")) {
                strncpy(token, value, sizeof(token));
            } else if (!strcmp(key, "secret")) {
                strncpy(secret, value, sizeof(secret));
            } 
        }
    }

    fclose(fp);

    printf("pid:%s\r\n", pid);
    printf("uuid:%s\r\n", uuid);
    printf("token:%s\r\n", token);
    printf("secret:%s\r\n", secret);

    const char *str = "111";
    cJSON *json = NULL;

    format_str_to_json(str, json);
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
