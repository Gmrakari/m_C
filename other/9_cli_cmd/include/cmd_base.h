#ifndef __CMD_BASE_H
#define __CMD_BASE_H

#include <stdio.h>

#include "cmd_core.h"

#define MAX_CMD_COUNT 1024

struct cli_st
{
    int initialized;
    const struct cli_command *commands[MAX_CMD_COUNT];
    unsigned int num_commands;
};

int cmd_base_init();

void cmd_base_deinit();

void cmd_base_run_cli_loop();

#endif // __CMD_BASE_H
