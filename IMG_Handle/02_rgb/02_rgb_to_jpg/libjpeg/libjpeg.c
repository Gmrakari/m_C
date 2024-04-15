#include "libjpeg.h"

int libjpeg_compress(image_jpeg_t *img, unsigned char quality, unsigned char **jpeg_buf, unsigned long int *jpeg_len)
{
    unsigned int img_width = img->width;
    unsigned int img_height = img->height;
    unsigned int img_pixels = img->bpp;
    unsigned char *img_data = (unsigned char*)(img->data);

    unsigned int old = (unsigned int)(*jpeg_buf);

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);
    cinfo.image_width = img_width;
    cinfo.image_height = img_height;
    cinfo.input_components = img_pixels;
    cinfo.in_color_space = JCS_RGB;
    #if 0
    printf("cinfo.image_width: %d,cinfo.image_height: %d, cinfo.input_components: %d\r\n",
            cinfo.image_width,cinfo.image_height, cinfo.input_components);
    #endif

    jpeg_mem_dest(&cinfo, jpeg_buf, (unsigned long *)jpeg_len);
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &img_data[cinfo.next_scanline * img_width * 3];
        (void)jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    if((unsigned int)*jpeg_buf != old) {
        printf("memory oveflow\r\n");
        free(*jpeg_buf);
        return 1;
    }

    return (cinfo.err->msg_code != 0);
}

int libjpeg_decompress(image_jpeg_t *jpeg, unsigned char *jpeg_buf, unsigned int jpeg_buf_len)
{
    if (!jpeg || !jpeg_buf || !jpeg_buf_len)
        return -1;

    // 1.初始化 libjpeg 解码器
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPARRAY buffer;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 2.指定输入文件
    jpeg_mem_src(&cinfo, jpeg_buf, jpeg_buf_len);

    // 3.读取 JPG 文件头
    jpeg_read_header(&cinfo, TRUE);

    // 4.启动压缩
    jpeg_start_decompress(&cinfo);

    memset(jpeg, 0x00, sizeof(image_jpeg_t));

    // 5.获取图像宽度和高度
    jpeg->width = cinfo.output_width;
    jpeg->height = cinfo.output_height;
    jpeg->bpp = cinfo.output_components;

    if (jpeg->data) {
        free(jpeg->data);
        jpeg->data = NULL;
    }

    jpeg->data = malloc(sizeof(unsigned char) * (jpeg->width * jpeg->height * jpeg->bpp));
    if (!jpeg->data) {
        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        return -1;
    }
    memset(jpeg->data, 0x00, sizeof(unsigned char) * (jpeg->width * jpeg->height * jpeg->bpp));

    unsigned int row_size = jpeg->width * jpeg->bpp;
    unsigned char *point = jpeg->data;
    
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_size, 1);

    while (cinfo.output_scanline < jpeg->height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(point, *buffer, row_size);
        point += row_size;
    }

    // 6.清理资源
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return (cinfo.err->msg_code != JTRC_EOI);
}

void libjpeg_decompress_free(image_jpeg_t *jpeg);