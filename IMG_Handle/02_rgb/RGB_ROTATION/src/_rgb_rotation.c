/*
 * Date:13 May 2023 1:51 PM
 * Filename:_rgb_rotation.c
*/

#include "_rgb_rotation.h"

#define READ_JPEG_FILE_PATHNAME  "../01_input.jpg"
#define WRITE_RGB_FILE_PATHNAME  "../01_output.rgb888"

static uint8_t s_src_img_buffer[320 * 240 * 3] = {0};
static uint8_t s_dest_img_buffer[320 * 240 * 3] = {0};

void _read_img_data_from_fp(image_t *img, const char *filename)
{
    if (img == NULL || filename == NULL) return ;

    FILE *fp = NULL;
    if (NULL == (fp = fopen(filename, "rb"))) {
        printf("fail to open file:%s", filename);
        return ;
    }
    fread(img->addr, sizeof(uint8_t), img->width * img->height * img->pixel, fp);
    fclose(fp);
}

// Rotation 180
void _rgb_img_rotation(image_t *src, image_t *dest)
{
    if (src == NULL || dest == NULL) return ;

    for (int i = 0; i < src->height; i++) {
        for (int j = 0; j < src->width; j++) {
            int src_idx = (i * src->width + j) * src->pixel;
            int dest_idx = ((src->height - 1 - i) * src->width + (src->width - 1 - j)) * src->pixel;
            dest->addr[dest_idx] = src->addr[src_idx];
            dest->addr[dest_idx + 1] = src->addr[src_idx + 1];
            dest->addr[dest_idx + 2] = src->addr[src_idx + 2];
        }
    }
}

// src and dest width, height, pixel are the same
void _rgb_img_rotation_180(uint8_t *src, uint32_t width, uint32_t height, uint32_t pixel, uint8_t *dest)
{
    if (src == NULL || dest == NULL) return ;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int src_idx = (i * width + j) * pixel;
            int dest_idx = ((height - 1 - i) * width + (width - 1 - j)) * pixel;
            dest[dest_idx] = src[src_idx];
            dest[dest_idx + 1] = src[src_idx + 1];
            dest[dest_idx + 2] = src[src_idx + 2];
        }
    }
}

void _save_rgb_img(image_t *img, const char *filename)
{
    if (img == NULL || filename == NULL) return ;

    FILE *fp = NULL;
    if (NULL == (fp = fopen(filename, "wb"))) {
        printf("fail to open file:%s", filename);
        return ;
    }

    fwrite(img->addr, sizeof(uint8_t), img->height * img->width * img->pixel, fp);
    fclose(fp);
}

void app_test()
{
    image_t src_rgb_img = {
            .addr = s_src_img_buffer,
            .width = 320,
            .height = 240,
            .pixel = 3,
    };
    image_t dest_rgb_img = {
            .addr = s_dest_img_buffer,
            .width = 320,
            .height = 240,
            .pixel = 3,
    };

    const char read_img_path[] = READ_JPEG_FILE_PATHNAME;
    const char write_img_path[] = WRITE_RGB_FILE_PATHNAME;

    _read_img_data_from_fp(&src_rgb_img, read_img_path);
    // _rgb_img_rotation(&src_rgb_img, &dest_rgb_img);
    _save_rgb_img(&src_rgb_img, write_img_path);
}
