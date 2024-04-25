/*
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */

#ifndef _GM_BASE64_H
#define _GM_BASE64_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

size_t gm_base64_get_encode_len(size_t slen);
unsigned char *gm_base64_encode(const unsigned char *src, size_t len, size_t *out_len);
unsigned char *gm_base64_decode(const unsigned char *src, size_t len, size_t *out_len);

#endif /* _GM_BASE64_H */
