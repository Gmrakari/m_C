#include <stdio.h>
#include "time.h"

char *func_version_handle() {
    static char *send_data = "lcd->h";

    time_t t = time(0);
    char buffer[256];
    // strftime(buffer, 256, "%F %T", localtime(&t));
    strftime(buffer, 256, "%F %T", localtime(&t));

    // strftime(buffer, 256, "%F %T", localtime(&t));

    printf("format time:%s\r\n", buffer);

    return send_data;
}

void cla_date_time() {
    char date_format[] = "2023-01-03 18:17:12";
}

int main(int argc, char const *argv[]) {
    char *get_send_data = NULL;
    get_send_data = func_version_handle();

    printf("get_send_data:%s\r\n", get_send_data);

}
