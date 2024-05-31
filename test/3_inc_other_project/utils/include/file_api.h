#ifndef _FILE_API_H_
#define _FILE_API_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int write_buffer_to_file(const char *filepath, const char *buffer, int len);

#endif // _FILE_API_H_