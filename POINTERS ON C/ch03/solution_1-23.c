#include <stdio.h>

//见-23问题描述
//wrong

static char b = 2;

void funcX()
{
    static int a = 1;

    int c = 3;
    static float d = 4;
}

void funcY()
{
}

------------------------------------------

//right

#include <stdio.h>

static char b = 2;

void funcY()
{
}

int a = 1;

void funcX()
{
    int c = 3;
    static float d = 4;
}