#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

void initGpio(int gpioNum)
{
    FILE *fp = fdopen("/sys/class/gpio/export", "w");
    if (fp == NULL)
        perror("export open failed!\n");
    else
        fprintf(fp, "%d", gpioNum);
    fclose(fp);
}

void deInitGpio(int gpioNum)
{
    FILE *fp = fdopen("/sys/class/gpio/unexport", "w");
    if (fp == NULL)
        perror("export open failed!\n");
    else
        printf(fp, "%d", gpioNum);
    fclose(fp);
}

/**
 * in   输入模式
 * out  输出模式，默认低电平
 * low  输出模式，默认低电平
 * high 输出模式，默认高电平
 *
 */
void setGpioDirection(int gpioNum, char *direction)
{
    char path[100] = {0};
    sprintf(path, "/sys/class/gpio/gpio%d/direction", gpioNum);
    FILE *fp = fdopen(path, "w");
    if (fp == NULL)
        perror("direction open failed!\n");
    else
        fprintf(fp, "%s", direction);
    fclose(fp);
}

int getGpioValue(int gpioNum)
{
    char path[64];
    char valueStr[3];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpioNum);
    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror("failed to open gpioValue\n");
        return -1;
    }

    if (read(fd, valueStr, 3) < 0)
    {
        perror("failed to read value!\n");
    }
    close(fd);
    return (atoi(valueStr));
}

void test()
{
    int gpionum = 100;
    initGpio(gpionum);
    setGpioDirection(gpionum, "in");

    while (1)
    {
        printf("%d\n", getGpioValue(gpionum));
    }
}

int main()
{
    test();
    return 0;
}