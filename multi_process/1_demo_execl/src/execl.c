#include <string.h>
#include "execl.h"

static execl_op_t execl_op_instance = {
    .is_init = 1,
};

execl_op_t *get_execl_instance(void) {
    return &execl_op_instance;
}

void choose_cmd_type(cmd_type_t type) {
    init_execl_instance();
    switch (type)
    {
    case CMD_TYPE_1:
        break;
    default:
        break;
    }
}