#ifndef _EXECL_H_
#define _EXECL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

// int execl(const char *pathname, const char *arg, .../* (char  *) NULL */);

#define SYS_SHELL_PATH "/bin/sh"

typedef struct {
    uint8_t is_init;
    int (*execute_cmd)(const char *cmd);
} execl_op_t;

typedef enum {
    CMD_TYPE_1 = 0,
} cmd_type_t;

execl_op_t *get_execl_instance(void);

void init_execl_instance(void);
void choose_cmd_type(cmd_type_t type);

#endif //_EXECL_H_
