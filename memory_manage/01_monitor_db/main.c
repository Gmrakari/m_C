#include "db.h"
#include <stdio.h>

#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// 4m
#define MEM_SIZE (4 * 1024 * 1024)

int main()
{
    int fd = open("../4m_mem_file", O_RDWR);
    if (fd == -1) {
        printf("[%s][%d]open err!\r\n", __func__, __LINE__);
        return -1;
    }

    void *ptr = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        printf("[%s][%d]mmap err!\r\n", __func__, __LINE__);
        return -1;
    }

    // sprintf(ptr, "Hello, Memory!");

    printf("[%s][%d]address: %p\n", __func__ , __LINE__, ptr);

    memset(ptr, 0x00, MEM_SIZE);

    // printf("Content of memory: %s\n", (char*)ptr);

    munmap(ptr, MEM_SIZE);
    close(fd);

    printf("[%s][%d]\r\n", __func__, __LINE__);

    return 0;
}
