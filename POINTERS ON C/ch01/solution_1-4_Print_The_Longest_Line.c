/*
 * @Author: Gmrakari gmrakari@outlook.com
 * @Date: 2022-07-25 14:39
 * @func:
 * @Parm:
 * @return:
 * @Filename: solution_1-4_Print_The_Longest_Line.c
 * @Description:
 */

/*
** Reads lines of input from the standard input and prints the longest line that
** was found to the standard output. It is assumed that no line will exceed
** 1000 characters.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1001

int main()
{
    char input[MAX_LEN];
    int len;
    char longest[MAX_LEN];
    int longest_len;

    longest_len = -1;

    while (gets(input) != NULL)
    {
        len = strlen(input);
        if (len > longest_len)
        {
            longest_len = len;
            strcpy(longest, input);
        }
    }

    if (longest_len > 0)
        puts(longest);

    return 0;
}