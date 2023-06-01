#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void p2p_func(char **str, size_t len)
{
    if (str == NULL || len < 0) return ;
    int j = 0;
    char *dest = NULL;
    dest = (char *)malloc(sizeof(char) * (len + 1));
    if (dest == NULL) return ;

    for (int i = len - 1; i >= 0; i--) {
        dest[j] = (*str)[i];
        j++;
    }
    dest[len] = '\0';
    *str = dest;
}

static void print(char *str) {
    if (str == NULL) return ;
    while (*str != '\0') {
        printf("%c", *str++);
    }
    printf("\r\n");
}

static size_t _get_str_len(char *str) {
    if (str == NULL) return -1;
    size_t len = 0;
     while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

void _test_reverse(void)
{
    char *str = "abcdefg";
    size_t len = _get_str_len(str);

    char *dest = malloc(sizeof(char) * len);
    if (dest == NULL) return ;
    int k = 0;
    while (len--) {
        dest[k++] = str[len]; 
    }

    dest[k] = '\0';

    char *ptr = dest;

    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
    }

    // while (*dest != '\0') {
    //     printf("%c", *dest);
    //     dest++;
    // }
    printf("\r\n");

    free(dest);
    dest = NULL;
}

int main() {
    // char *str = "abcdefg";
    // size_t len = _get_str_len(str);
    // printf("str before: %s\r\n", str);
    // p2p_func(&str, len);

    // printf("str afer  : ");
    // print(str);

    // free(str);
    // str = NULL;

    _test_reverse();

    return 0;
}

