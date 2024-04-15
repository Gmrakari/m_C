/*
 * Date:11 March 2024 09:50 AM
 * Filename:rgb_to_jpg.h
*/

#ifndef _RGB_TO_JPG_H
#define _RGB_TO_JPG_H

#include <stdio.h>
#include <bits/stdint-uintn.h>

static const char * TAG  = "rgb_utils";

typedef enum {
    PIX_FORMAT_RGB444 = 0,
    PIX_FORMAT_RGB555,
    PIX_FORMAT_RGB565,
    PIX_FORMAT_RGB888,
    PIX_FORMAT_YUV422,
    PIX_FORMAT_YUV420,
    PIX_FORMAT_RAW,
    PIX_FORMAT_JEPG,
} pix_format_t;

typedef struct {
    unsigned short int width;   // jpg width
    unsigned short int height;  // jpg height
    unsigned char bpp;          // bits per pixel 
    unsigned char *data;        // jpg data
} image_jpeg_t;

typedef struct {
    unsigned char *data;        // img data
    unsigned short int width;   // img width
    unsigned short int height;  // img height
    unsigned char pixel;        // img pixel
} image_t;

/**
 * @brief rgb 转 jpg
 * @details
 * @param[in]  src_format            原格式
 * @param[out] jpg                   jpg
 * @return 转换成功，返回:0; 转换失败，返回:-1
 */
// int _rgb_to_jpg(pix_format_t src_format, const unsigned char *in_src, image_jpeg_t *out);
int _rgb_to_jpg(pix_format_t src_format, const image_t *rgb, image_jpeg_t *out);

void app_test();

#endif // _RGB_TO_JPG_H
