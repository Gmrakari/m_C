#ifndef _NORMAL_LINKLIST_H
#define _NORMAL_LINKLIST_H

#include "linklist.h"
#include <stdio.h>

typedef struct src_msg_t {
    char *buf;
    size_t buf_len;
} src_msg;

typedef struct dest_msg_t {
    char *buf;
    size_t buf_len;
} dest_msg;

typedef struct status_msg_t {
    char *buf;
    size_t buf_len;
} status_msg;

typedef struct package_header_data_t {
    src_msg *src_msg_str;
    dest_msg *dest_msg_str;
    long timestamp;
    status_msg *status_msg_str;
    void *arg;
    void (*fn)(src_msg *src_msg_str, dest_msg *dest_msg_str, void *);
} package_header_data;

typedef struct tag_user_info_t {
    LinkListNode *node;
    package_header_data *data;
} user_info;

#endif // _NORMAL_LINKLIST_H
