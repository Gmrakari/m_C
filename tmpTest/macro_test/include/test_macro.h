#ifndef _TEST_MACRO_H
#define _TEST_MACRO_H

#include <stdio.h>
#include <string.h>

#define STR_BUF_LEN (24)

char *str_func();

#define STR_FUNC() str_func()

#define GET_STR_FUN() ({ \
    char str[STR_BUF_LEN] = {0}; \
    strcat("{macro str func test-", str); \
    strcat()
    
    strncpy(str, __str, sizeof(str)); \

})


// char *__str = "marcro str func test\r\n"; 
// "{macro str func test- "STR_FUNC()"}"

void macro_app();

#endif /* _TEST_MACRO_H */