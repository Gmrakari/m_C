#ifndef _RECORD_H_
#define _RECORD_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "cb_header.h"

void m_record_func(void);

void mf_record_pass_upload_pic_register_cb(void (*cb)());

#endif // _RECORD_H_
