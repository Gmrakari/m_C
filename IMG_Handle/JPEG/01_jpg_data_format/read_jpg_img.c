#include <stdio.h>
#include <bits/stdint-uintn.h>  //uint8/uint32
#include <jpeglib.h> // 1.确保安装了libjpeg-dev 2.编译的时候 需要-ljpeg

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t bpp;
    size_t jpg_size;
} jpg_img_info_t;

#define LOGI(format, ...) printf("(%d):"format, __LINE__, ##__VA_ARGS__)

static void _get_jpg_width_and_height(const char *filename, jpg_img_info_t *info)
{
    FILE *fp;

    if (NULL == (fp = fopen(filename, "r+")))
        return ;

    size_t file_end, file_start, file_len;

    fseek(fp, 0, SEEK_END);
    file_end = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    file_start = ftell(fp);
    file_len = file_end - file_start;
    info->jpg_size = file_len;

    // 1.初始化 libjpeg 解码器
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 2.指定输入文件
    jpeg_stdio_src(&cinfo, fp);

    // 3.读取 JPG 文件头
    jpeg_read_header(&cinfo, TRUE);

    // 4.启动压缩
    jpeg_start_decompress(&cinfo);

    // 获取图像宽度和高度
    info->width = cinfo.output_width;
    info->height = cinfo.output_height;
    info->bpp = cinfo.output_components;

    // 清理资源
    jpeg_destroy_decompress(&cinfo);
    fclose(fp);
}

static void _print_jpg_width_and_height(jpg_img_info_t *info)
{
    if (info == NULL)
        return ;

    LOGI("jpg height:%d\r\n", info->height);
    LOGI("jpg width:%d\r\n", info->width);
    LOGI("jpg bpp:%d\r\n", info->bpp);

    // JPEG文件的大小和使用libjpeg计算出来的图像宽度、高度以及位深度（bpp）之间没有直接的关系 
    // 1.JPEG文件的大小只表示压缩后的数据量
    // 2.图像的宽度、高度和位深度则是解码后的图像属性
    LOGI("jpg height * width * bpp size:%d\r\n", info->height * info->width * info->bpp);
    LOGI("jpg file size:%d\r\n", (int)info->jpg_size);
}

static void test_case()
{
    const char *file_path = "/home/gmrakari/github/m_C/IMG_Handle/JPEG/01_jpg_data_format/pic_1.jpg";
    jpg_img_info_t info = {.width = 0, .height = 0};
    _get_jpg_width_and_height(file_path, &info);
    _print_jpg_width_and_height(&info);
}

int main()
{
    test_case();
    return 0;
}
