#ifndef __LIBJPEG_H
#define __LIBJPEG_H

#include <stdint.h>

#include "./include/cdjpeg.h"
#include "./include/jversion.h"

typedef struct {
    unsigned int width;   // jpg width
    unsigned int height;  // jpg height
    unsigned char bpp;    // bits per pixel 
    unsigned char *data;  // jpg data
} image_jpeg_t;

int libjpeg_compress(image_jpeg_t *img, unsigned char quality, unsigned char **jpeg_buf, unsigned long int *jpeg_len);

int libjpeg_decompress(image_jpeg_t *jpeg, unsigned char *jpeg_buf, unsigned int jpeg_buf_len);

void libjpeg_decompress_free(image_jpeg_t *jpeg);

#endif /* __LIBJPEG_H */
