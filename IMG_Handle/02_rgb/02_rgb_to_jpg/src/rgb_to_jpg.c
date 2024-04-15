/*
 * Date:11 March 2024 09:50 AM
 * Filename:rgb_to_jpg.c
*/

#include "rgb_to_jpg.h"
#include <stdlib.h>

#define IMG_FILE_PATH "rgb_src.rgb888"

static uint8_t s_src_img_buffer[128 * 128 * 3] = {0};
static uint8_t s_dest_img_buffer[128 * 128 * 3] = {0};

int _rgb_to_jpg(pix_format_t src_format, const image_t *rgb, image_jpeg_t *out)
{
    if (!rgb)
        return -1;
    
    if (src_format == PIX_FORMAT_RGB565) {
        // rgb->data;
        // rgb->height;
        // rgb->width;
        // rgb->pixel;
    }

    return 0;
}

void app_test()
{
    image_t img = {0};
    const char img_path[] = IMG_FILE_PATH;
    // _rgb_to_jpg

    image_jpeg_t jpg = {0};
    _rgb_to_jpg(PIX_FORMAT_RGB888, &img, &jpg);

    printf("[%s][%d]\r\n", __func__, __LINE__);

    int *ptr = malloc(10);

}
