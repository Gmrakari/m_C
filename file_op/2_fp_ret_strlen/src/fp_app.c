#include <stdio.h>
#include <string.h> // strlen

#include "fp_app.h"

#define CONFIG_FILENAME "conf.ini"
#define CONFIG_FILEPATH "../res/%s"
#define CONFIG_PATH_STR_LEN (128)
#define READ_BUF_LEN        (1024)

static size_t _get_file_len(void)
{
    char filepath_buf[CONFIG_PATH_STR_LEN] = {0};
    snprintf(filepath_buf, sizeof(filepath_buf), CONFIG_FILEPATH, CONFIG_FILENAME);

    const char *filepath = filepath_buf;
    printf("filepath:%s\r\n", filepath);

    FILE *fp = fopen(filepath, "r");
    if (!fp) 
        return 0;

    char line[READ_BUF_LEN] = {0};
    size_t len = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        len += strlen(line);
    }

    fclose(fp);
 
    return len;

}

void fp_app(void) 
{
    size_t len = _get_file_len();
    printf("len:%ld\r\n", len);
    return ;
}
