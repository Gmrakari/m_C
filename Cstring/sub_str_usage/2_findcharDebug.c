#include <stdio.h>

char *find_char(char* const source, char* const chars) {
    if (source == NULL || chars == NULL) return NULL;
    if (*source == '\0' || *chars == '\0') return NULL;
    
    char *tmpsource = source;
    char *tmpchars = chars;

/*
    // 遍历目标串
    while (*tmpchars++ != '\0') {
        tmpsource = source;
        // 遍历原串
        while (*tmpsource++ != '\0') {
            if (*tmpsource == *tmpchars) return tmpsource;
        }
    }
*/

    while (*tmpsource != '\0') {
        // tmpsource = source;
        while (*tmpchars != '\0') {
            if (*tmpchars == *tmpsource) {
                return (char*)tmpsource;
            }
            tmpchars++;
        }
        tmpchars = chars;
        tmpsource++;
    }
    return NULL;
}

int main() {
    char *source = "ABCD";
    char *chars = "CD";

    char *ret = find_char(source, chars);
    printf("%p\n", ret);
    printf("%p\n", find_char(source, chars));

    if (ret == NULL) {
        printf("11\n");
        printf("can not find chars src\n");
    }
    else {
        printf("%s\n", (find_char(source, chars)));
    }

    printf("end\n");
}