#include <stdio.h>
#include "../include/cal_sha256.h"

int get_file_sha256(const char *filepath, char *output) {
    if (!filepath || !output) return -1;

    FILE *fp = fopen(filepath, "rb");
    if (!fp) {
        perror("Failed to open file");
        return -1;
    }
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    size_t buffer_size = 8192; 
    unsigned char buffer[buffer_size];

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, buffer_size, fp)) > 0) {
        SHA256_Update(&sha256, buffer, bytesRead);
    }

    SHA256_Final((unsigned char*)output, &sha256);

    fclose(fp);
    return 0;
}

static void hex_string_to_binary(const char *hex_string, unsigned char *binary_data) {
    size_t len = strlen(hex_string);
    for (size_t i = 0; i < len / 2; i++) {
        sscanf(hex_string + 2 * i, "%02X", &binary_data[i]);
    }
}

int compare_sha256_value(const char *src, const char *dest) {
    if (!src || !dest) return -1;

    const char *src_sha256 = src;
    const char *dest_sha256 = dest;

    if (!memcmp(src_sha256, dest_sha256, SHA256_DIGEST_LENGTH)) {
        printf("Signatures are consistent!\r\n");
        return 0;
    }

    return -1;
}