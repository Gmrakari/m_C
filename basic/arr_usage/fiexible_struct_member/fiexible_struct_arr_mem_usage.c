
#include <stdio.h> // stderr printf size_t
#include <stdlib.h> // malloc


typedef struct {
    unsigned short int lcd_w;
    unsigned short int lcd_h;
    unsigned long int addr_size;
    unsigned char addr[0];  // 灵活数组成员
} lcd_info_t;

lcd_info_t* create_lcd_info(unsigned short int lcd_w, unsigned short int lcd_h, unsigned long int addr_size) {
    // 计算结构体的总大小，包括灵活数组的大小
    size_t total_size = sizeof(lcd_info_t) + addr_size;

    // 分配足够的内存
    lcd_info_t *lcd_info = (lcd_info_t*)malloc(total_size);
    if (!lcd_info) {
        return NULL;
    }

    // 初始化结构体成员
    lcd_info->lcd_w = lcd_w;
    lcd_info->lcd_h = lcd_h;
    lcd_info->addr_size = addr_size;

    return lcd_info;
}

void free_lcd_info(lcd_info_t *lcd_info) {
    free(lcd_info);
    lcd_info = NULL;
}

int main() {
    // 创建并初始化结构体实例
    unsigned short int lcd_w = 640;
    unsigned short int lcd_h = 480;
    unsigned long int addr_size = 20;

    lcd_info_t *lcd_info = create_lcd_info(lcd_w, lcd_h, addr_size);
    if (!lcd_info) {
        fprintf(stderr, "Failed to create lcd_info\n");
        return 1;
    }

    // 操作灵活数组
    unsigned char *addr = lcd_info->addr;
    strcpy(addr, "lcd addr pbuf info");

    // 打印结构体成员
    printf("lcd_w: %d\n", lcd_info->lcd_w);
    printf("lcd_h: %d\n", lcd_info->lcd_h);
    printf("addr_size: %lu\n", lcd_info->addr_size);
    printf("lcd_info->addr: %s\n", lcd_info->addr);

    // 释放内存
    free_lcd_info(lcd_info);

    return 0;
}
