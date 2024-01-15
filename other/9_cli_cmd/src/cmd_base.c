
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "cmd_base.h"

#define USE_CMD_LIST_TYPE (1)

#ifdef USE_CMD_LIST_TYPE
#define CMD_LIST_PARAM (private.cmd_list_ptr)
#else
#define CMD_LIST_PARAM (cmd_list)
#endif

void help_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
void time_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
void test_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
void exit_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv);
int cli_register_commands(const struct cli_command *commands, int num_commands);
int cli_register_command(const struct cli_command *command);

typedef struct {
    uint8_t is_init : 1;
    struct cli_st *pCli;
    const struct cli_command *cmd_list_ptr;
    size_t cmd_list_size;
} cmd_base_private_t;

static const struct cli_command cmd_list[] = {
    {"help", NULL, help_command},
    {"time", "get current timestamp", time_command},
    {"test", "test 0 18 20", test_command},
    {"exit", NULL, exit_command}
};

static cmd_base_private_t private = {.is_init = 0, 
                                     .pCli = NULL, 
                                     .cmd_list_ptr = cmd_list, 
                                     .cmd_list_size = sizeof(cmd_list) / sizeof(cmd_list[0])};

void help_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    int i, n;
    uint32_t cmd_list_count = private.cmd_list_size;

    for (i = 0, n = 0; i < MAX_CMD_COUNT && n < private.pCli->num_commands; i++)
    {
        if (private.pCli->commands[i]->name)
        {
            printf("%s: %s\r\n", private.pCli->commands[i]->name,
                      private.pCli->commands[i]->help ?
                      private.pCli->commands[i]->help : "");
            n++;
        }
    }
}

void time_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    char help[] = "help";

    if (argc == 2 && !strcmp(argv[1], help)) {
        printf("Usage:\r\ntime\r\n");
        return ;
    }

#if 0
    if (argc > 1) {
        char buff[32] = {0};
        char space[] = " ";
        for (int i = 1; i < argc; i++) {
            strcat(buff, argv[i]);
            if (i != argc - 1) {
                strcat(buff, space);
            }
        }

        for (int i = 0; i < private.pCli->num_commands; i++) {
            if (private.pCli->commands[i]->help && !strcmp(buff, private.pCli->commands[i]->help)) {
                printf("help:%s\r\n", private.pCli->commands[i]->help);
            }
        }
    }
#endif

    printf("time:1\r\n");
}

void test_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    uint32_t ret, id, mode, i;
    char cmd0 = 0;
    char cmd1 = 0;
    char cmd;

    char cmd3_1;
    char cmd3_2;
    uint32_t cmd_3_value;

    uint32_t cmd3;

    if(argc == 4)
    {
        cmd = argv[1][0];
        mode = argv[3][0];

        cmd0 = argv[2][0] - 0x30;
        cmd1 = argv[2][1] - 0x30;

        printf("cmd info:%d hex:%02X, transfer:%d hex --:%02X\r\n", cmd, cmd, cmd - 0x30, cmd - 0x30);

        printf("cmd0 info:%d hex:%02x\r\n", cmd0, cmd0);

        id = (uint32_t)(cmd0 * 10 + cmd1);
        printf("---id:%d, hex:%x, mode:%u, hex:%02X----\r\n", id, id, mode, mode);

        cmd3_1 = argv[3][0] - 0x30;
        cmd3_2 = argv[3][1] - 0x30;

        printf("argv[3][0]:%d hex:%02X\r\n", argv[3][0], argv[3][0]);
        printf("argv[3][1]:%d hex %02X\r\n", argv[3][1], argv[3][1]);

        cmd_3_value = (uint32_t)(cmd3_1 * 10 + cmd3_2);
        printf("cmd3_1_bytes:%d hex:%02X\r\n", cmd3_1, cmd3_1);
        printf("cmd3_2_bytes:%d hex:%02X\r\n", cmd3_2, cmd3_2);
        printf("cmd_3_value:%d\r\n", cmd_3_value);

        cmd3 = atoi(argv[3]);
        printf("cmd3:%d\r\n", cmd3);
    }
    else
        printf("cmd param error\r\n");
}



void exit_command(char *pcWriteBuffer, int xWriteBufferLen, int argc, char **argv)
{
    exit(1);
}


int cmd_base_init()
{
    if (private.is_init) return -1;

    private.pCli = (struct cli_st *)malloc(sizeof(struct cli_st));
    if (!private.pCli) return -1;

    memset(private.pCli, 0x00, sizeof(*(private.pCli)));

    if (cli_register_commands(CMD_LIST_PARAM, private.cmd_list_size))
    {
        goto init_err;
    }

    return 0;

init_err:
    if (private.pCli) { free(private.pCli); private.pCli = NULL; }
    return -1;
}

void cmd_base_deinit()
{
    if (private.pCli) { free(private.pCli); private.pCli = NULL; }
    return ;
}

int cli_register_commands(const struct cli_command *commands, int num_commands)
{
    int i;
    for (i = 0; i < num_commands; i++)
        if (cli_register_command(commands++))
            return 1;
    return 0;
}

int cli_register_command(const struct cli_command *command)
{
    int i;
    if (!command->name || !command->function)
        return 1;

    if (private.pCli->num_commands < MAX_CMD_COUNT)
    {
        // 检查是否已经注册
        for (i = 0; i < private.pCli->num_commands; i++)
        {
            if (private.pCli->commands[i] == command)
                return 0;
        }
        private.pCli->commands[private.pCli->num_commands++] = command;
        return 0;
    }

    return 1;
}

void cmd_base_run_cli_loop()
{
    char input_buffer[256];
    int find_cmd_in_list = 0;

    while (1)
    {
        printf("Enter a command: ");
        fgets(input_buffer, sizeof(input_buffer), stdin);

        // 去掉换行符
        input_buffer[strcspn(input_buffer, "\n")] = '\0';

        // printf("input:%s\r\n", input_buffer);

        // 解析命令和参数
        int argc = 0;

        // 假设最多有15个参数
        char *argv[16];

        char *token = strtok(input_buffer, " ");
        while (token != NULL && argc < 15)
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }

        if (argc > 0)
        {
            // 查找命令并执行
            for (int i = 0; i < private.pCli->num_commands; i++)
            {
                if (strcmp(private.pCli->commands[i]->name, argv[0]) == 0)
                {
                    private.pCli->commands[i]->function(NULL, 0, argc, argv);
                    find_cmd_in_list = 0;
                    break;
                } else {
                    find_cmd_in_list++;
                }
            }

            if (find_cmd_in_list == private.pCli->num_commands) {
                find_cmd_in_list = 0;
                printf("\"%s\" Unknow command. Try 'help' for a list of commands.\n", argv[0]);
            }
        }
        else
        {
            printf("Invalid command. Try 'help' for a list of commands.\n");
        }
    }
}
