/*
 * Date:11 March 2024 03:12 PM
 * Filename:img_utils.c
*/

#include "img_utils.h"
#include "../libjpeg/libjpeg.h"

#define TEST_RGB565_TO_RGB888   1
#define TEST_RGB565_TO_JPG      1

#define TEST_RGB888_TO_RGB565   1
#define TEST_RGB888_TO_JPG      1

#define TEST_JPG_TO_RGB565      1
#define TEST_JPG_TO_RGB888      1

#define READ_JPEG_FILE_PATH                 "../01_input.jpg"
#define RGB888_FILE_PATH                    "../02_output_888.rgb"
#define WRITE_RGB565_FILE_PATHNAME          "../03_output_565.rgb"
#define WRITE_RGBX_FILE_PATHNAME            "../05_output_888_x.rgb"
#define WRITE_RGB565_JPG_FILE_PATHNAME      "../06_output_rgb565_2_jpg.jpg"
#define WRITE_RGB888_TO_JPG_FILE_PATHNAME   "../07_output_rgb888_2_jpg.jpg"
#define WRITE_RGB565_IMG_PATHNAME           "../08_output_rgb565.rgb"
#define TEST_RGB565_TO_RGB888_FILE_PATH     "../09_rgb565_to_rgb888.rgb"
#define TEST_JPG_TO_RGB565_FILE_PATH        "../10_jpg_to_rgb565.rgb"

static size_t _get_file_size(const char *filename)
{
    if (!filename)
        return 0;

    int ret = 0;
    FILE *fp = NULL;
    if (NULL == (fp = fopen(filename, "r"))) {
        LOGD("fail to open file:%s", filename);
        return 0;
    }

    fseek(fp, 0, SEEK_END); 
    size_t file_size = ftell(fp);

    fclose(fp);

    return file_size;
}

// 内部申请内存
static int _read_file_to_buffer(const char *filepath, unsigned char **out)
{
    if (!filepath)
        return -1;
    
    int ret = 0;

    size_t len = _get_file_size(filepath);
    if (len == 0) 
        return -1;

    unsigned char *buff = malloc(sizeof(unsigned char) * len);
    if (!buff) {
        LOGD("malloc buff err\r\n");
        ret = -1;
        return ret ;
    }
    memset(buff, 0x00, sizeof(unsigned char) * len);

    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        ret = -1;
        return ret;
    }
    fread(buff, len, 1, fp);

    fclose(fp);

    *out = buff;

    return ret;
}

static int _get_jpg_info(image_jpeg_t *jpeg, unsigned char *buff, size_t buff_len)
{
    if (!jpeg || !buff || !buff_len)
        return -1;

    // 1.初始化 libjpeg 解码器
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 2.指定输入文件
    jpeg_mem_src(&cinfo, buff, buff_len);

    // 3.读取 JPG 文件头
    jpeg_read_header(&cinfo, TRUE);

    // 4.启动压缩
    jpeg_start_decompress(&cinfo);

    // 获取图像宽度和高度
    jpeg->width = cinfo.output_width;
    jpeg->height = cinfo.output_height;
    jpeg->bpp = cinfo.output_components;
    printf("width:%d height:%d bpp:%d\r\n", jpeg->width, jpeg->height, jpeg->bpp);

    // 清理资源
    jpeg_destroy_decompress(&cinfo);

    return 0;
}

static int _save_to_file(unsigned char *data, size_t len, const char *filepath)
{
    if (!data || !filepath || !len)
        return -1;

    FILE *fp = NULL;
    if (NULL == (fp = fopen(filepath, "wb"))) {
        printf("fail to open file:%s", filepath);
        return -1;
    }

    fwrite(data, sizeof(unsigned char), len, fp);
    fclose(fp);

    return 0;
}

static int _rgb888_to_rgb565(const void * psrc, int w, int h, void * pdst)  
{
    #define UpAlign4(n) (((n) + 3) & ~3)
    int srclinesize = UpAlign4(w * 3);  
    int dstlinesize = UpAlign4(w * 2);  
      
    const unsigned char * psrcline;  
    const unsigned char * psrcdot;  
    unsigned char  * pdstline;  
    unsigned short * pdstdot;  
      
    int i,j;  
      
    if (!psrc || !pdst || w <= 0 || h <= 0) {  
        printf("rgb888_to_rgb565 : parameter error\n");  
        return -1;  
    }  
  
    psrcline = (const unsigned char *)psrc;  
    pdstline = (unsigned char *)pdst;  
    for (i=0; i<h; i++) {  
        psrcdot = psrcline;  
        pdstdot = (unsigned short *)pdstline;  
        for (j=0; j<w; j++) {  
            //888 r|g|b -> 565 b|g|r  
            *pdstdot =  (((psrcdot[0] >> 3) & 0x1F) << 0)//r  
                        |(((psrcdot[1] >> 2) & 0x3F) << 5)//g  
                        |(((psrcdot[2] >> 3) & 0x1F) << 11);//b  
            psrcdot += 3;  
            pdstdot++;  
        }  
        psrcline += srclinesize;  
        pdstline += dstlinesize;  
    }  
  
    return 0;  
}

static int _rgb565_to_rgb888(const void * psrc, int w, int h, void * pdst)  
{
    #define UpAlign4(n) (((n) + 3) & ~3)
    int srclinesize = UpAlign4(w * 2);  
    int dstlinesize = UpAlign4(w * 3);  
  
    const unsigned char  * psrcline;  
    const unsigned short * psrcdot;  
    unsigned char  * pdstline;  
    unsigned char  * pdstdot;  
  
    int i,j;  
  
    if (!psrc || !pdst || w <= 0 || h <= 0) {  
        printf("rgb565_to_rgb888 : parameter error\n");  
        return -1;  
    }  
  
    psrcline = (const unsigned char *)psrc;  
    pdstline = (unsigned char *)pdst;  
    for (i=0; i<h; i++) {  
        psrcdot = (const unsigned short *)psrcline;  
        pdstdot = pdstline;  
        for (j=0; j<w; j++) {  
            //565 b|g|r -> 888 r|g|b  
            *pdstdot++ = (unsigned char)(((*psrcdot) >> 0 ) << 3);  
            *pdstdot++ = (unsigned char)(((*psrcdot) >> 5 ) << 2);  
            *pdstdot++ = (unsigned char)(((*psrcdot) >> 11) << 3);  
            psrcdot++;  
        }  
        psrcline += srclinesize;  
        pdstline += dstlinesize;  
    }  
  
    return 0;  
} 

// test ok
static int _jpg_to_rgb888(unsigned int *out_w, unsigned int *out_h, unsigned int *out_ch)
{
    if (!out_w || !out_h || !out_ch)
        return -1;

    int ret = 0;

    const char read_img_path[] = READ_JPEG_FILE_PATH;
    const char write_img_path[] = RGB888_FILE_PATH;

    int width = 0;
    int height = 0;
    int ch = 0;

    size_t len = _get_file_size(read_img_path);
    if (len == 0)
        return 0;

    unsigned char *buff = NULL;
    if (0 != (ret = _read_file_to_buffer(read_img_path, &buff))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    image_jpeg_t jpeg = {0};
    if (0 != (ret = libjpeg_decompress(&jpeg, buff, len))) {
        LOGD("libjpeg_decompress err\r\n");
        if (buff) {
            free(buff);
            buff = NULL;
        }
        ret = -1;
        return ret ;
    }

    if (buff) {
        free(buff);
        buff = NULL;
    }

    LOGD("w:%d h:%d bpp:%d\r\n", jpeg.width, jpeg.height, jpeg.bpp);

    width = jpeg.width;
    height = jpeg.height;
    ch = jpeg.bpp;

    *out_w = width;
    *out_h = height;
    *out_ch = ch;

    size_t jpeg_len = 0;
    jpeg_len = width * height * ch;
    if (!jpeg.data) {
        ret = -1;
        return ret;
    }

    LOGD("jpeg_len:%ld\r\n", jpeg_len);

    // save rgb888 to file
    if (0 != (ret = _save_to_file(jpeg.data, jpeg_len, write_img_path))) {
        LOGD("_save_to_file err\r\n");
        ret = -1;

        if (jpeg.data) {
            free(jpeg.data);
            jpeg.data = NULL;
        }
        return ret ;
    }

    if (jpeg.data) {
        free(jpeg.data);
        jpeg.data = NULL;
    }

    return ret;
}


static int _jpg_to_rgb565()
{
    int ret = 0;

    const char read_img_path[] = READ_JPEG_FILE_PATH;
    const char write_img_path[] = TEST_JPG_TO_RGB565_FILE_PATH;

    int width = 0;
    int height = 0;
    int ch = 0;

    size_t len = _get_file_size(read_img_path);
    if (len == 0)
        return 0;

    unsigned char *buff = NULL;
    if (0 != (ret = _read_file_to_buffer(read_img_path, &buff))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    image_jpeg_t jpeg = {0};
    if (0 != (ret = libjpeg_decompress(&jpeg, buff, len))) {
        LOGD("libjpeg_decompress err\r\n");
        if (buff) {
            free(buff);
            buff = NULL;
        }
        ret = -1;
        return ret ;
    }

    if (buff) {
        free(buff);
        buff = NULL;
    }

    LOGD("w:%d h:%d bpp:%d\r\n", jpeg.width, jpeg.height, jpeg.bpp);

    width = jpeg.width;
    height = jpeg.height;
    ch = jpeg.bpp;

    size_t jpeg_len = 0;
    jpeg_len = width * height * ch;
    if (!jpeg.data) {
        ret = -1;
        return ret;
    }

    unsigned char *rgb565 = malloc(sizeof(unsigned char) * (width * height * (ch - 1)));
    if (!rgb565) {
        LOGD("rgb565 malloc err\r\n");
        if (jpeg.data) {
            free(jpeg.data);
            jpeg.data = NULL;
        }

        ret = -1;
        return ret;
    }
    memset(rgb565, 0x00, sizeof(unsigned char) * (width * height * (ch - 1)));

    if (0 != (ret = _rgb888_to_rgb565(jpeg.data, width, height, rgb565))) {
        LOGD("_rgb888_to_rgb565 err\r\n");
        if (jpeg.data) {
            free(jpeg.data);
            jpeg.data = NULL;
        }

        ret = -1;
        return ret;
    }

    if (jpeg.data) {
        free(jpeg.data);
        jpeg.data = NULL;
    }

    // save rgb565 to file
    if (0 != (ret = _save_to_file(rgb565, (width * height * (ch - 1)), write_img_path))) {
        LOGD("rgb565 _save_to_file err\r\n");
        ret = -1;

        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }
        return ret;
    }

    if (rgb565) {
        free(rgb565);
        rgb565 = NULL;
    }

    return ret;
}

// test ok
static int _rgb888_to_rgb565_test(unsigned int width, unsigned int height, unsigned int ch)
{
    int ret = 0;
    const char read_rgb888_img_path[] = RGB888_FILE_PATH;
    const char write_rgb565_img_path[] = WRITE_RGB565_FILE_PATHNAME;

    size_t len = _get_file_size(read_rgb888_img_path);
    if (len == 0)
        return 0;

    unsigned char *rgb888 = NULL;
    if (0 != (ret = _read_file_to_buffer(read_rgb888_img_path, &rgb888))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    size_t rgb565_len = width * height * (ch - 1);
    // LOGD("rgb565_len:%ld\r\n", rgb565_len);
    unsigned char *rgb565 = malloc(sizeof(unsigned char) * rgb565_len);
    if (!rgb565) {
        LOGD("rgb565 malloc err\r\n");
        ret = -1;
        return ret;
    }

    if (0 != (ret = _rgb888_to_rgb565(rgb888, width, height, rgb565))) {
        LOGD("_rgb888_to_rgb565 err\r\n");

        if (rgb888) {
            free(rgb888);
            rgb888 = NULL;
        }

        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }
    }

    if (rgb888) {
        free(rgb888);
        rgb888 = NULL;
    }

    // save rgb565 to file
    if (0 != (ret = _save_to_file(rgb565, rgb565_len, write_rgb565_img_path))) {
        LOGD("rgb565 _save_to_file err\r\n");
        ret = -1;

        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }
        return ret ;
    }

    if (rgb565) {
        free(rgb565);
        rgb565 = NULL;
    }

    return ret ;
}

// todo test
static int _rgb565_to_rgb888_test(unsigned int width, unsigned int height, unsigned int ch)
{
    int ret = 0;

    const char read_rgb565_img_path[] = WRITE_RGB565_IMG_PATHNAME;
    const char write_rgb888_img_path[] = TEST_RGB565_TO_RGB888_FILE_PATH;

    size_t len = _get_file_size(read_rgb565_img_path);
    if (len == 0)
        return 0;

    unsigned char *rgb565 = NULL;
    if (0 != (ret = _read_file_to_buffer(read_rgb565_img_path, &rgb565))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    size_t rgb888_len = width * height * ch;
    // LOGD("rgb888_len:%ld\r\n", rgb888_len);
    unsigned char *rgb888 = malloc(sizeof(unsigned char) * rgb888_len);
    if (!rgb888) {
        LOGD("rgb888 malloc err\r\n");
        ret = -1;
        return ret;
    }

    if (0 != (ret = _rgb565_to_rgb888(rgb565, width, height, rgb888))) {
        LOGD("_rgb565_to_rgb888 err\r\n");

        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }

        if (rgb888) {
            free(rgb888);
            rgb888 = NULL;
        }
    }

    if (rgb565) {
        free(rgb565);
        rgb565 = NULL;
    }

    // save rgb888 to file
    if (0 != (ret = _save_to_file(rgb888, rgb888_len, write_rgb888_img_path))) {
        LOGD("rgb888 _save_to_file err\r\n");
        ret = -1;

        if (rgb888) {
            free(rgb888);
            rgb888 = NULL;
        }
        return ret ;
    }

    if (rgb888) {
        free(rgb888);
        rgb888 = NULL;
    }

    return ret;
}

// 
static int _rgb565_to_jpg_test(unsigned int width, unsigned int height, unsigned int ch)
{
    int ret = 0;
    const char read_rgb565_img_path[] = WRITE_RGB565_FILE_PATHNAME;
    const char write_rgb565_to_jpg_path[] = WRITE_RGB565_JPG_FILE_PATHNAME;

    size_t len = _get_file_size(read_rgb565_img_path);
    if (len == 0)
        return 0;

    unsigned char *rgb565 = NULL;
    if (0 != (ret = _read_file_to_buffer(read_rgb565_img_path, &rgb565))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    unsigned char *rgb888 = malloc(sizeof(unsigned char) * (width * height * ch));
    if (!rgb888) {
        LOGD("rgb888 malloc err\r\n");
        ret = -1;
        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }
        return ret ;
    }
    memset(rgb888, 0x00, sizeof(unsigned char) * (width * height * ch));
    
    if (0 != (ret = _rgb565_to_rgb888(rgb565, width, height, rgb888))) {
        LOGD("_rgb565_to_rgb888 err\r\n");
        ret = -1;

        if (rgb565) {
            free(rgb565);
            rgb565 = NULL;
        }

        if (rgb888) {
            free(rgb888);
            rgb888 = NULL;
        }
        return ret;
    }

    if (rgb565) {
        free(rgb565);
        rgb565 = NULL;
    }

    int quality = 80;
    unsigned char *jpg = malloc(sizeof(unsigned char) * (width * height * ch));
    if (!jpg) {
        LOGD("jpg malloc err\r\n");
        ret = -1;
        if (rgb888) {
            free(rgb888);
            rgb888 = NULL;
        }
        return ret ;
    }

    size_t jpg_len = sizeof(unsigned char) * (width * height * ch);
    image_jpeg_t img = {
        .data = rgb888,
        .height = height,
        .width = height,
        .bpp = ch,
    };
    ret = libjpeg_compress(&img, quality, &jpg, &jpg_len);
    if (ret != 0) {
        LOGD("libjpeg_compress err\r\n");
        ret = -1;

        if (img.data) {
            free(img.data);
            img.data = NULL;
        }

        if (jpg) {
            free(jpg);
            jpg = NULL;
        }
        return ret;
    }

    if (img.data) {
        free(img.data);
        img.data = NULL;
    }

    // write jpg to file
    if (0 != (ret = _save_to_file(jpg, jpg_len, write_rgb565_to_jpg_path))) {
        LOGD("write_rgb565_to_jpg_path _save_to_file err\r\n");
        ret = -1;

        if (jpg) {
            free(jpg);
            jpg = NULL;
        }

        return ret ;
    }

    if (jpg) {
        free(jpg);
        jpg = NULL;
    }

    return ret;
}

// test ok
static int _rgb888_to_jpg(unsigned int width, unsigned int height, unsigned int ch)
{
    int ret = 0;
    const char read_rgb888_img_path[] = RGB888_FILE_PATH;
    const char write_rgb888_to_jpg_path[] = WRITE_RGB888_TO_JPG_FILE_PATHNAME;

    size_t len = _get_file_size(read_rgb888_img_path);
    if (len == 0)
        return 0;

    unsigned char *rgb888 = NULL;
    if (0 != (ret = _read_file_to_buffer(read_rgb888_img_path, &rgb888))) {
        LOGD("_read_file_to_buffer err\r\n");
        ret = -1;
        return ret ;
    }

    // rgb888 -> jpg
    image_jpeg_t img = {
        .data = NULL,
        .height = height,
        .width = width,
        .bpp = ch,
    };

    if (img.data) {
        free(img.data);
        img.data = NULL;
    }

    img.data = malloc(sizeof(unsigned char) * img.height * img.width * img.bpp);
    if (!img.data) {
        printf("img.data malloc overflow!\r\n");
        ret = -1;
        return ret;
    }
    memset(img.data, 0x00, sizeof(unsigned char) * img.height * img.width * img.bpp);
    memcpy(img.data, rgb888, sizeof(unsigned char) * img.height * img.width * img.bpp);

    if (rgb888) {
        free(rgb888);
        rgb888 = NULL;
    }

    int quality = 80;
    unsigned char *jpg = malloc(sizeof(unsigned char) * img.height * img.width * img.bpp);
    size_t jpg_len = sizeof(unsigned char) * img.height * img.width * img.bpp;
    ret = libjpeg_compress(&img, quality, &jpg, &jpg_len);
    if (ret != 0) {
        LOGD("libjpeg_compress err\r\n");
        ret = -1;

        if (img.data) {
            free(img.data);
            img.data = NULL;
        }

        if (jpg) {
            free(jpg);
            jpg = NULL;
        }
        return ret;
    }

    if (img.data) {
        free(img.data);
        img.data = NULL;
    }

    // write jpg to file
    if (0 != (ret = _save_to_file(jpg, jpg_len, write_rgb888_to_jpg_path))) {
        LOGD("write_rgb888_to_jpg_path _save_to_file err\r\n");
        ret = -1;

        if (jpg) {
            free(jpg);
            jpg = NULL;
        }

        return ret ;
    }

    if (jpg) {
        free(jpg);
        jpg = NULL;
    }

    return ret;
}

int app_test()
{
    int ret = 0;
    int width = 0;
    int height = 0;
    int ch = 0;

#if TEST_JPG_TO_RGB888
    ret = _jpg_to_rgb888(&width, &height, &ch);
    if (ret != 0) {
        printf("_jpg_to_rgb888 err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

#if TEST_RGB888_TO_RGB565
    ret = _rgb888_to_rgb565_test(width, height, ch);
    if (ret != 0) {
        printf("_rgb888_to_rgb565_test err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

#if TEST_RGB565_TO_JPG
    ret = _rgb565_to_jpg_test(width, height, ch);
    if (ret != 0) {
        printf("_rgb565_to_jpg_test err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

#if TEST_JPG_TO_RGB565
    ret = _jpg_to_rgb565();
    if (ret != 0) {
        printf("_jpg_to_rgb565 err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

#if TEST_RGB888_TO_JPG
    ret = _rgb888_to_jpg(width, height, ch);
    if (ret != 0) {
        printf("_rgb888_to_jpg err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

#if TEST_RGB565_TO_RGB888
    ret = _rgb565_to_rgb888_test(width, height, ch);
    if (ret != 0) {
        printf("_rgb565_to_rgb888 err\r\n");
        return ret;
    }LOGD("\r\n");
#endif

    return 0;
}
