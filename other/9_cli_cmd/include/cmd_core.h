#ifndef __CMD_CORE_H
#define __CMD_CORE_H

#include "cmd_base.h"

struct cli_command
{
    /** The name of the CLI command */
    const char *name;
    /** The help text associated with the command */
    const char *help;
    /** The function that should be invoked for this command. */
    void (*function) (char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
};

void cmd_core_func();

#endif // __CMD_CORE_H