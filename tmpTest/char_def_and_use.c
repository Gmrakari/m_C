#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc


// Segmentation fault (core dumped)
void test01() {
    int ret = 0;
    char *str;
    strcpy(str, "helloworld");
    printf("str:%s\r\n", str);
    return ;
}

// Segmentation fault (core dumped)
void test02() {
    char *str;
    memset(str, 0, sizeof(str));
    strcpy(str, "helloworld");
    printf("str:%s\r\n", str);
    return ;
}

// Segmentation fault (core dumped)
void test03() {
    char *str = NULL;
    memset(str, 0, sizeof(str));
    strcpy(str, "helloworld");
    printf("str:%s\r\n", str);
    return ;
}

void test04() {
    printf("start to run test04...\r\n");
    char *str = (char*)malloc(sizeof(char));
    memset(str, 0, sizeof(str));
    strcpy(str, "helloworld");
    printf("str:%s\r\n", str);

    if (str != NULL) {
        free(str);
        str = NULL;
    }
    return ;
}

char test05() {
    printf("start to run test05...\r\n");
    // char str[12] = {0};
    char str[8] = {0};
    int len = sizeof(str) / sizeof(str[0]); 
    printf("origin strlen:%d\r\n", strlen(str));
    printf("origin len:%d\r\n", len);

    char dest[] = "helloworld";
    printf("dest strlen len:%d\r\n", strlen(dest));
    printf("dest sizeof len:%d\r\n", sizeof(dest) / sizeof(dest[0]));
    if (len < strlen(dest)) {
        printf("origin len is too short\r\n");
        char str2[12] = {0};
        strcpy(str2, dest);
        printf("str2:%s\r\n", str2);
        return ;
    }
    strcpy(str, dest);
    printf("str:%s\r\n", str);
    return ; 
}

int main() {

    // test01();
    // test02();
    // test03();
    // test04();
    test05();
}
