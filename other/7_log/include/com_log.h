#ifndef __COM_LOG_H
#define __COM_LOG_H

#include <stdio.h>
#include <stdarg.h> // va_list
#include <stdint.h> // uint8/16/32/64..

#include "com_utils.h"

typedef struct {
    va_list ap;
    const uint8_t *format;
    const uint8_t *file;
    struct tm *time;
    void *userdata;
    uint32_t line;
    uint8_t level;
} log_event_t;

typedef void (*LogFunction)(log_event_t *event);
typedef void (*LockFunction)(uint8_t lock, void *userdata);

typedef enum {
    LOG_LEVEL_TRACE = 0,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} log_level_type_t;

#define LOG_TRACE(...) log_msg(LOG_LEVEL_TRACE, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(...) log_msg(LOG_LEVEL_DEBUG, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(...)  log_msg(LOG_LEVEL_INFO, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(...)  log_msg(LOG_LEVEL_WARN, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(...) log_msg(LOG_LEVEL_ERROR, __FILE__, __LINE__, ##__VA_ARGS__)
#define LOG_FATAL(...) log_msg(LOG_LEVEL_FATAL, __FILE__, __LINE__, ##__VA_ARGS__)

/* 
** @ref :设置log的level
** @in  :需要设置的level
** @out :None
*/
void log_set_global_level(uint8_t level);

/* 
** @ref :设置log是否开启
** @in  :en:1 开启; en:0 关闭
** @out :None
*/
void log_set_quiet_mode(uint8_t en);

/* 
** @ref :log消息
** @in  :level等级，file:文件，行号，fmt，...
** @out :按照in格式输出内容
*/
void log_msg(uint8_t level, const uint8_t *file, uint32_t line, const uint8_t *fmt, ...);

/* 
** @ref :将对应的level转string
** @in  :level
** @out :level对应的str
*/
const uint8_t *log_level_to_str(uint8_t level);

/* 
** @ref :日志加锁回调
** @in  :加锁处理的函数，userdata:用户数据
** @out :None
*/
void log_lock_with_cb(LogFunction fn, void *userdata);

/* 
** @ref :增加log的回调处理
** @in  :LogFunction fn:回调处理的结构体，userdata:需要回调处理的数据，level等级
** @out :0 成功，其它值失败
*/
uint32_t log_add_cb_handle(LogFunction fn, void *userdata, uint8_t level);

/* 
** @ref :增加log的文件指针
** @in  :FILE *fp 文件指针, 输出的等级
** @out :0 成功，其它值失败
*/
uint32_t log_add_file_pointer(FILE *fp, uint8_t level);

#endif // __COM_LOG_H