#include <stdio.h>

enum Liquid
{
    OUNCE = 1,
    CUP = 8,
    PINT = 16,
    QUART = 32,
    GALLON = 128
};

//实际上错误的是打印信息的数据格式%s，枚举类型在内存是以整型数据类型存储，
//打印枚举类型变量应该使用整型数据格式%d，把printf里的%s全部改成%d，程序就可以正常运行
void funcTest()
{
    enum Liquid jar;
    jar = QUART;
    // printf("%s\n", jar); //warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘unsigned int’ [-Wformat=]
    printf("%d\n", jar);

    jar = jar + PINT;
    // printf("%s\n", jar); //warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘unsigned int’ [-Wformat=]
    printf("%d\n", jar);
}

int main()
{
    funcTest();
}
