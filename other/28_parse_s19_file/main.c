#include <stdio.h>
#include "parse_s19_api.h"

#define DEMO_FILEPAH "../res/"


int main()
{
    const char filepath[] = DEMO_FILEPAH;
    test_parse_s19_file(filepath);
    return 0;
}
