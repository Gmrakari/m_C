#include "./include/execl.h"
#include <stdio.h>

extern execl_op_t *execl_cmd_ptr;

int main() {
    int res = 0;

    choose_cmd_type(CMD_TYPE_1);

    const uint8_t *cmd_string = "ls";

    if (execl_cmd_ptr != NULL) {
        printf("init status:%d\r\n", execl_cmd_ptr->is_init);
        execl_cmd_ptr->execute_cmd(cmd_string);
    }

    printf("hello world\r\n");
}