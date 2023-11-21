#include <sys/types.h>  // fork
#include <unistd.h>     // fork
#include <stdlib.h>
#include <sys/wait.h>   // waitpid

#include "execl.h"

execl_op_t *execl_cmd_ptr = NULL;

#define DEBUG_LINE() \
do { \
    printf("[%d][%s]\r\n", __LINE__, __func__); \
} while (0); \

static int _execute_cmd(const char *cmd) {
    printf("%s\r\n", cmd);
    pid_t pid = fork();DEBUG_LINE();
    int res = 0;
    if (pid == -1) {DEBUG_LINE();
        perror("fork");
        res = -1;
        return res;
    } else if (pid == 0) {DEBUG_LINE();
        execl(SYS_SHELL_PATH, "sh", "-c", cmd, (char*)0);
        perror("execl");DEBUG_LINE();
        exit(EXIT_FAILURE);
    } else {DEBUG_LINE();

        // 等待子进程结束
        int status;
        waitpid(pid, &status, 0);DEBUG_LINE();
        if (WIFEXITED(status)) {DEBUG_LINE();
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {DEBUG_LINE();
                printf("run son process\r\n");
            } else {DEBUG_LINE();
                printf("run err exit:%d\r\n", exit_status);
                res = exit_status;
            }
        } else {DEBUG_LINE();
            printf("son process execept exit\r\n");
        }
    }DEBUG_LINE();
    return res;
}

void init_execl_instance(void) {
    if (execl_cmd_ptr == NULL) {
        execl_cmd_ptr = get_execl_instance();
        execl_cmd_ptr->execute_cmd = _execute_cmd;
    }
}
