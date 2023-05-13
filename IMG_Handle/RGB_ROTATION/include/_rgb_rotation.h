/*
 * Date:13 May 2023 1:51 PM
 * Filename:_rgb_rotation.h
*/

#ifndef _RGB_ROTATION_H
#define _RGB_ROTATION_H

#include <stdio.h>
#include <bits/stdint-uintn.h>

typedef struct {
    uint8_t *addr;
    uint32_t width;
    uint32_t height;
    uint32_t pixel;
} image_t;

void _read_img_data_from_fp(image_t *img, const char *filename);
// Rotation 180
void _rgb_img_rotation(image_t *src, image_t *dest);
// src and dest width, height, pixel are the same
void _rgb_img_rotation_180(uint8_t *src, uint32_t width, uint32_t height, uint32_t pixel, uint8_t *dest);

void _save_rgb_img(image_t *img, const char *filename);

void app_test();

#endif // _RGB_ROTATION_H
