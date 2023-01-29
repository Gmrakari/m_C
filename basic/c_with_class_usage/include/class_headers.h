#ifndef _CLASS_HEADERS_H_
#define _CLASS_HEADERS_H_

#include <stdio.h>

typedef struct {
    void (*init)(void);
    void (*get)(void);

} test_class_t;

typedef enum
{
    TYPE_TEST = 0,
    TYPE_MAX
}type_t;

extern test_class_t test_class;

int type_choose(type_t type);

#endif /* _CLASS_HEADERS_H_ */