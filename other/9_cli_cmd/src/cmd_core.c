#include "cmd_core.h"

extern void cmd_base_run_cli_loop();

void cmd_core_func() {
    cmd_base_init();
    cmd_base_run_cli_loop();
    return ;
}
