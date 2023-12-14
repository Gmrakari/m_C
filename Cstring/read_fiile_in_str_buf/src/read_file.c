#include "read_file.h"
#include "format_str_to_json.h"

int read_file(const char *filepath) {
    if (!filepath) return -1;

    const char *str = "111";
    cJSON *json = NULL;

    format_str_to_json(str, json);

    return 0;
}

