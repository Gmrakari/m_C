#include "com_log.h"

#define MAX_CALLBACKS_LEN             (32)
#define ENABLE_OUTPUT_LOG_COLOR       (1)
#define H_M_S_TIME_BUF_LEN            (16)
#define Y_M_D_H_M_S_TIME_BUF_LEN      (64)

typedef struct {
    LogFunction fn;
    void *userdata;
    uint8_t level;
} callback_t;

typedef struct {
    void *userdata;
    LockFunction lock;
    uint8_t level;
    uint8_t quiet;
    callback_t calllbacks[MAX_CALLBACKS_LEN];
} log_t;

static void init_event(log_event_t *event, void *userdata);

static log_t log;

static const uint8_t *level_string[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

#ifdef ENABLE_OUTPUT_LOG_COLOR
static const uint8_t *level_colors[] = {
    "\x1b[94m", "\x1b[36m", "\x1b[32m", "\x1b[33m", "\x1b[31m", "\x1b[35m"
};
#endif

static void stdout_cb(log_event_t *event)
{
    if (event == NULL || event->time == NULL)
        return;

    uint8_t buffer[H_M_S_TIME_BUF_LEN] = {0};
    size_t len = strftime(buffer, sizeof(buffer), "%H:%M:%S", event->time);
    buffer[len] = '\0';

#ifdef ENABLE_OUTPUT_LOG_COLOR
    fprintf(event->userdata, "%s %s%-5s\x1b[0m \x1b[90m%s:%d:\x1b[0m ", 
    buffer, level_colors[event->level], level_string[event->level], event->file, event->line);
#else
    fprintf(event->userdata, "%s %-5s %s:%d \r\n", buffer, level_string[event->level], event->file, event->line);
#endif

    vfprintf(event->userdata, event->format, event->ap);
    fprintf(event->userdata, "\r\n");
    fflush(event->userdata);
}

static void file_cb(log_event_t *event)
{
    if (event == NULL || event->time == NULL)
        return;
    uint8_t buffer[Y_M_D_H_M_S_TIME_BUF_LEN] = {0};
    size_t len = strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", event->time);
    buffer[len] = '\0';
    fprintf(event->userdata, "%s %-5s %s:%d \r\n", buffer, level_string[event->level], event->file, event->line);
    vfprintf(event->userdata, event->format, event->ap);
    fprintf(event->userdata, "\r\n");
    fflush(event->userdata);    
}

static void lock(void)
{
    if (log.lock) 
        log.lock(1, log.userdata);
}

static void unlock(void)
{
    if (log.lock) 
        log.lock(0, log.userdata);
}

/* 
** @ref :设置log的level
** @in  :需要设置的level
** @out :None
*/
void log_set_global_level(uint8_t level)
{
    log.level = level;
    return ;
}

/* 
** @ref :设置log是否开启
** @in  :en:1 开启; en:0 关闭
** @out :None
*/
void log_set_quiet_mode(uint8_t en)
{
    log.quiet = en;
    return;
}

/* 
** @ref :log消息
** @in  :level等级，file:文件，行号，fmt，...
** @out :按照in格式输出内容
*/
void log_msg(uint8_t level, const uint8_t *file, uint32_t line, const uint8_t *fmt, ...)
{
    if (file == NULL || fmt == NULL) return ;
    log_event_t event = {
        .format = fmt,
        .file = file,
        .level = level,
        .line = line,
    };

    lock();

    if ( !log.quiet && level >= event.level) {
        init_event(&event, stderr);
        va_start(event.ap, fmt);
        stdout_cb(&event);
        va_end(event.ap);
    }

    for (uint32_t i = 0; i < MAX_CALLBACKS_LEN && log.calllbacks[i].fn; i++) {
        callback_t *cb = &log.calllbacks[i];
        if (level >= cb->level) {
            init_event(&event, cb->userdata);
            va_start(event.ap, fmt);
            cb->fn(&event);
            va_end(event.ap);
        }
    }

    unlock();

    return ;
}

/* 
** @ref :将对应的level转string
** @in  :level
** @out :level对应的str
*/
const uint8_t *log_level_to_str(uint8_t level)
{
    return level_string[level];
}

/* 
** @ref :日志加锁回调
** @in  :加锁处理的函数，userdata:用户数据
** @out :None
*/
void log_lock_with_cb(LogFunction fn, void *userdata)
{
    log.lock = (LockFunction)fn;
    log.userdata = userdata;
    return ;
}

/* 
** @ref :增加log的回调处理
** @in  :LogFunction fn:回调处理的结构体，userdata:需要回调处理的数据，level等级
** @out :0 成功，其它值失败
*/
uint32_t log_add_cb_handle(LogFunction fn, void *userdata, uint8_t level)
{
    for (uint32_t i = 0; i < MAX_CALLBACKS_LEN; i++) {
        if (!log.calllbacks[i].fn) {
            log.calllbacks[i] = (callback_t) {fn, userdata, level};
            return 0;
        }
    }
    return -1;
}

/* 
** @ref :增加log的文件指针
** @in  :FILE *fp 文件指针, 输出的等级
** @out :0 成功，其它值失败
*/
uint32_t log_add_file_pointer(FILE *fp, uint8_t level)
{
    if (fp == NULL) 
        return -1;
    return log_add_cb_handle(file_cb, fp, level);
}

static void init_event(log_event_t *event, void *userdata)
{
    if (event != NULL && !event->time) {
        time_t t = time(NULL);
        struct tm* result = timestamp_2_tm(&t, TIMEZONE_CN);
        if (result) {
            event->time = result;
            event->userdata = userdata;
        }
    }
}
