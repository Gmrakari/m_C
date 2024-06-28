#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EN_TEST_CAST_1       (0)
#define EN_TEST_CAST_2       (0)
#define EN_TEST_CAST_3       (1)

static int _escape_string(const char *input, char **output) {
    if (!input) {
        fprintf(stderr, "invalid param!\n");
        return -1;
    }

    size_t len = strlen(input);
    size_t output_len = len * 2 + 1;
    *output = (char *)malloc(output_len);
    if (*output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    const char *src = input;
    char *dst = *output;
    while (*src) {
        switch (*src) {
            case '\"': *dst++ = '\\'; *dst++ = '\"'; break;
            case '\\': *dst++ = '\\'; *dst++ = '\\'; break;
            case '\b': *dst++ = '\\'; *dst++ = 'b'; break;
            case '\f': *dst++ = '\\'; *dst++ = 'f'; break;
            case '\n': *dst++ = '\\'; *dst++ = 'n'; break;
            case '\r': *dst++ = '\\'; *dst++ = 'r'; break;
            case '\t': *dst++ = '\\'; *dst++ = 't'; break;
            default: *dst++ = *src; break;
        }
        src++;
    }
    *dst = '\0';

    return 0;
}

static int _get_input(char *input, int len)
{
    if (!input || !len) {
        fprintf(stderr, "invalid param!\n");
        return -1;
    }

    printf("Enter a string: \r\n");
    if (fgets(input, len, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return -1;
    }

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    return 0;
}

static int _test_case_1()
{
    char input[1024] = {0};

    _get_input(input, sizeof(input));

    char *output = NULL;

    int ret = 0;

    ret = _escape_string(input, &output);
    if (ret != 0 || !output) {
        printf("[%s][%d]_escape_string err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (output != NULL) {
        // printf("Original string:\n%s\n", input);
        printf("Escaped string:\n%s\n", output);
        free(output);
    }

    return 0;
}

static int _test_case_2()
{
    // const char *input = "{\"msgId\":\"1795642337355018241\",\"ts\":1716949461,\"version\":\"1.0\",\"topic\":null,\"sys\":{\"ack\":1},\"data\":{\"subUuid\":null,\"operatorType\":2,\"pwdData\":{\"type\":null,\"index\":801,\"deviceUserId\":null,\"pwd\":null,\"timeType\":null,\"activeTime\":null,\"expireTime\":null,\"startTime\":null,\"endTime\":null,\"loops\":null}},\"code\":0}";

    const char *input = "{\"msgId\":\"1795642337355018241\",\"ts\":1716949461}";

    char *output = NULL;

    int ret = 0;

    printf("[%s][%d]\r\n", __func__, __LINE__);
    printf("%s\r\n", input);

    ret = _escape_string(input, &output);
    if (ret != 0 || !output) {
        printf("[%s][%d]_escape_string err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (output) {
        printf("Escaped string:\n%s\n", output);
        free(output);
    }

    return 0;
}

static int _test_case_3()
{
    const char *input = NULL;

    char *output = NULL;

    int ret = 0;

    ret = _escape_string(input, &output);
    if (ret != 0 || !output) {
        printf("[%s][%d]_escape_string err!\r\n", __func__, __LINE__);
        return -1;
    }

    if (output) {
        printf("Escaped string:\n%s\n", output);
        free(output);
    }

    return 0;
}

int main() {

    int ret = 0;

    #if EN_TEST_CAST_1

    ret = _test_case_1();
    if (ret != 0) {
        printf("[%s][%d]_test_case_1 err!\r\n", __func__, __LINE__);
        return ret;
    }

    #endif

    #if EN_TEST_CAST_2

    ret = _test_case_2();
    if (ret != 0) {
        printf("[%s][%d]_test_case_2 err!\r\n", __func__, __LINE__);
        return ret;
    }

    #endif

    #if EN_TEST_CAST_3

    ret = _test_case_3();
    if (ret != 0) {
        printf("[%s][%d]_test_case_3 err!\r\n", __func__, __LINE__);
        return ret;
    }

    #endif

    return 0;
}

// gcc -g -o a.out 1_fmt_escape_string.c
// valgrind --leak-check=full --show-leak-kinds=all ./a.out