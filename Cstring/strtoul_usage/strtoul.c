#include <stdio.h>
// #include <string.h> 
#include <stdlib.h> // strtoul

// unsigned long strtoul(const char *nptr, char **endptr, int base);
// unsigned long long strtoull(const char *nptr, char **endptr, int base);

static void strtoul_func(const char *str) {
    if (!str) return ;

    const char *ptr = str;

    printf("[%s] ptr: %s\r\n", __func__, ptr);

    char *endptr;
    unsigned long len = strtoul(ptr, &endptr, 10);
    printf("res: %ld\r\n\r\n", len);

    return ;
}

static void test_case() {
    const char *str[4] = {"123abc", "abc123", "abc", "123"};

    for (int i = 0; i < 4; i++) {
        printf("%s %d\r\n", __func__, i + 1);
        strtoul_func(str[i]);
    }
}

int main() {
    test_case();

    return 0;
}