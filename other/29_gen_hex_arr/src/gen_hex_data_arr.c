#include "gen_hex_data_arr.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_DATA_LENGTH 4096

#define MAX_LINE_LENGTH 16384  // 增加行缓冲区大小
#define OUTPUT_CHUNK_SIZE 1024 // 每次输出的字节数

#define MAX_PER_LINE_OUTPUT_NUM (16)

static int gen_case_x_main() 
{
    FILE *input_file, *output_file;
    char line[MAX_LINE_LENGTH];
    uint8_t data[OUTPUT_CHUNK_SIZE];
    int data_length = 0;
    int total_length = 0;
    char *token;
    int value;
    int line_count = 0;
    int need_comma = 0;
    
    const char *input_filename = "../res/input.txt";     // 输入文件名
    const char *output_filename = "output.h";            // 输出文件名
    const char *array_name = "hex_data";                 // 数组变量名
    const char *length_name = "hex_data_length";         // 长度变量名

    // 打开输入文件
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        perror("无法打开输入文件");
        return 1;
    }

    // 打开输出文件
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("无法打开输出文件");
        return 1;
    }

    // 生成头文件保护宏
    char guard_macro[100];
    for (int i = 0; i < strlen(output_filename); i++) {
        if (isalnum(output_filename[i])) {
            guard_macro[i] = toupper(output_filename[i]);
        } else {
            guard_macro[i] = '_';
        }
    }
    guard_macro[strlen(output_filename)] = '\0';
    
    // 移除文件名中的扩展名部分
    char *dot_pos = strrchr(guard_macro, '.');
    if (dot_pos != NULL) {
        *dot_pos = '\0';
    }

    // 写入头文件内容
    fprintf(output_file, "#ifndef _%s_H\n", guard_macro);
    fprintf(output_file, "#define _%s_H\n\n", guard_macro);
    fprintf(output_file, "#include <stdint.h>\n\n");
    // fprintf(output_file, "// 从 %s 转换而来的十六进制数据\n", input_filename);
    fprintf(output_file, "// 数据\n");
    fprintf(output_file, "uint8_t %s[] = {\n    ", array_name);

    // 逐行读取并处理输入文件
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        line_count++;
        // 移除行末的换行符
        line[strcspn(line, "\n")] = 0;

        // 使用空格分割每行数据
        token = strtok(line, " ");
        while (token != NULL) {
            // 转换十六进制字符串为整数
            if (sscanf(token, "%x", &value) == 1) {
                // 不是第一行的第一个元素，前面需要添加逗号和换行
                if (total_length > 0 && total_length % MAX_PER_LINE_OUTPUT_NUM == 0) {
                    fprintf(output_file, ",\n");
                    fprintf(output_file, "    ");
                }
                // 不是每行的第一个元素，前面需要添加逗号
                else if (total_length % MAX_PER_LINE_OUTPUT_NUM != 0) {
                    fprintf(output_file, ", ");
                }
                
                // 输出当前字节
                fprintf(output_file, "0x%02X", (uint8_t)value);
                total_length++;
            }
            token = strtok(NULL, " ");
        }
    }

    // 写入数据长度和头文件结尾
    fprintf(output_file, "\n};\n\n");
    fprintf(output_file, "// 数据长度\n");
    fprintf(output_file, "uint32_t %s = sizeof(%s);\n\n", length_name, array_name);
    fprintf(output_file, "#endif // %s_H\n", guard_macro);

    fclose(output_file);

    printf("成功生成头文件: %s\n", output_filename);
    printf("数据长度: %d 字节\n", total_length);

    return 0;
}

int start_gen_hex_data_arr(void)
{
    int ret = 0;
    printf("[%s][%d]\r\n", __func__, __LINE__);

    gen_case_x_main();

    return ret;
}
