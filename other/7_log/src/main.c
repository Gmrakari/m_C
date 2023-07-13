#include "com_log.h"
#include <stddef.h>
/*
** Usage:
** log_trace(const char *fmt, ...);
** log_debug(const char *fmt, ...);
** log_info(const char *fmt, ...);
** log_warn(const char *fmt, ...);
** log_error(const char *fmt, ...);
** log_fatal(const char *fmt, ...);
**
*/

static void test_case1()
{
    const char buf[] = "hello world";

    LOG_TRACE(buf);
    LOG_DEBUG(buf);
    LOG_INFO(buf);
    LOG_WARN(buf);
    LOG_ERROR(buf);
    LOG_FATAL(buf);
}

int main()
{
    test_case1();
}
