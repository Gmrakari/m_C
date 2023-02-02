#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_char_strpbrk(const char *source, const char *chars) {
    if (source == NULL || chars == NULL) return NULL;
    
    while (*source != '\0') {
        const char *tmp = chars;
        while (*tmp != '\0') 
            if (*tmp++ == *source)
                return (char *)source;
        ++source;
    }
    return NULL;
}

int strlength(char *str) {
    if (str == NULL) return 0;
    int len = 0;
    while (*str++ != '\0') {
        ++len;
    }
    return len;
}

int find_StrStr(char *str, char *substr, char *retStr) {
    int ret = 0;
    if (str == NULL) {
        retStr = NULL;
        return 0;
    }

    char *tmpstr = str;
    char *tmpsubstr = substr;

    int tmpstrLen = strlength(tmpstr);
    printf("tmpstrLen:%d\n", tmpstrLen);
    int tmpsubstrLen = strlength(tmpsubstr);
    printf("tmpsubstrLen:%d\n", tmpsubstrLen);

    if (tmpstrLen < tmpsubstrLen || tmpsubstr == NULL) {
        while (*str != '\0') {
            *retStr++ = *str++;
        }
        return ret;
    }

    while (*tmpstr != '\0') {
        while (*tmpstr != *tmpsubstr && *tmpstr != '\0') {
            *retStr++ = *str++;
        }
        if (strncmp(tmpstr, tmpsubstr, tmpsubstrLen) != 0) {
            *retStr++ = *tmpstr++;
            continue;
        }
        else {
            tmpstr += tmpsubstrLen;
            ret++;
        }
    }
    *retStr = '\0';
    return ret;

}

int main() {
    char source[] = "ABCDEFG";
    char chars[] = "CDE";

    char tmpret[100] = {0};

    int ret = find_StrStr(source, chars, tmpret);

    printf("%p\n", tmpret);
    //printf("%p\n", find_StrStr(source, chars, tmpret));

    // if (retchar == NULL) {
    //     printf("11\n");
    //     printf("can not find chars src\n");
    // }
    // else {
    //     printf("find_StrStr(source, chars, retchar)%s\n", find_StrStr(source, chars, retchar));
    // }

    printf("end\n");
}