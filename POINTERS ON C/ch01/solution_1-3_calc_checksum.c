#include <stdio.h>
#include <stdlib.h>

/*
** This program copies its standard input to the standard output, and computes
** a checksum of the characters. The checksum is printed after the input.
*/

void func()
{
    int c;
    char checksum = -1;

    // press Ctrl + D to stop input
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        checksum += c;
    }
    printf("checksum:%d\n", checksum);
    return;
}

int main()
{
    func();
}