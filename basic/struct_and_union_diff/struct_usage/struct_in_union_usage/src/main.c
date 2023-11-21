#include <stdio.h>
#include "struct.h"

#define USE_STRUCT_APP (0)
#define USE_UNION_APP (0)
#define USE_UNION_IN_STRUCT_APP (0)
#define USE_STRUCT_IN_UNION_APP (1)

static void test_app()
{
#if USE_STRUCT_APP
    struct_app();
#endif

#if USE_UNION_APP
    union_app();
#endif

#if USE_UNION_IN_STRUCT_APP
    union_in_struct_app();
#endif

#if USE_STRUCT_IN_UNION_APP
    struct_in_union_app();
#endif 
}

int main() {

    test_app();

    return 0;
}
