#include <string.h>
#include <openssl/sha.h>

#include "../include/http.h"
#include "../include/host_to_ip.h"

// static void (*download_cb)(const char *filepath, const char *response, const size_t len) = NULL;

static char *create_http_get_request(const char *path, const char *host, const char *port) {
    if (!path || !host || !port) {
        return NULL;
    }

    size_t request_len = snprintf(NULL, 0, "GET %s HTTP/1.1\r\nHost:%s:%s\r\n\r\n", path, host, port);

    char *request = NULL;
    request = malloc(request_len + 1);
    if (!request) { DEBUG_MSG();
        perror("req_header malloc err");
        return NULL;
    }

    snprintf(request, request_len + 1, "GET %s HTTP/1.1\r\nHost:%s:%s\r\n\r\n", path, host, port);
    return request;
}

static int cal_file_sha256(const char *filepath, char *output) {
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

static int save_file_to_local(const char *filepath, const char *response, const size_t len) {
    if (!filepath || !response || len == 0) return -1;

#if 1
    FILE *fp = NULL;

    fp = fopen(filepath, "wb+");
    if (!fp) {
        perror("Failed to open file");
        return -1;
    }

    size_t bytes_written = fwrite(response, 1, len, fp);
    if (bytes_written != len) {
        perror("Failed to write to file");
        fclose(fp);
        return -1;
    }

    fclose(fp);

    int res = -1;

    char downfile_sha256[SHA256_DIGEST_LENGTH];
    char origin_digest[SHA256_DIGEST_LENGTH];
    res = cal_file_sha256(filepath, downfile_sha256);
    char origin_sha256_key[] = "5b2eab8b319301688260a52f04ff1a606033e6597c07cb36e464097bbf385c7e";

    hex_string_to_binary(origin_sha256_key, origin_digest);

    if (res == 0) {
        if (!memcmp(origin_digest, downfile_sha256, SHA256_DIGEST_LENGTH)) {
            printf("Signatures are consistent!\r\n");
        } else {
            printf("Check~ Inconsistent signatures!\r\n");
        }
    }
#endif

    return 0;
}

static void print_download_process(size_t total_len, size_t cur_len) {
    printf("%d/%d (%2.2f%%)\r\n", cur_len, total_len, (float)cur_len / total_len * 100);
}

static size_t get_http_response_header_length(const char *data) {
    if (!data) return 0;

    const char *str = data;
    size_t ret = 0;

    size_t header_length = 0;
    char *header_end = strstr(str, "\r\n\r\n");
    if (header_end == NULL) {
        ret = 0;
        return ret;
    }
    header_length = header_end - str + 4;

    return header_length;
}

static size_t get_http_response_content_length(const char *data) {
    if (!data) return 0;

    const char *str = data;

    size_t ret = 0;
    size_t content_length = 0;

    char *content_length_start = strstr(str, "Content-Length:");
    if (content_length_start == NULL) {
        ret = 0;
        return ret;
    }

    sscanf(content_length_start + strlen("Content-Length:"), "%zu", &content_length);
    if (content_length <= 0) {
        ret = 0;
        return ret;
    }

    return content_length;
}

static uint32_t handle_http_response_header(const char *data, size_t *out_header_len, size_t *out_content_len) {
    if (!data) return 0;

    size_t header_len = 0;
    size_t content_len = 0;

    uint32_t ret = 1;
    header_len = get_http_response_header_length(data);
    if (header_len == 0) { ret = 0; return ret;}

    *out_header_len = header_len;

    content_len = get_http_response_content_length(data);
    if (content_len == 0) { ret = 0; return ret;}

    *out_content_len = content_len;

    return ret;
}

uint32_t http_get(const char *url) {
    if (!url) return -1;

    int ret = -1;

    url_package_t url_info = {0};
    if (0 != (ret = parse_url(url, strlen(url), &url_info))) { ret = -1; return NULL; }

    uint8_t *ip_buf = NULL;
    uint8_t ip[16] = {0};
    if (NULL == (ip_buf = host_to_ip(url_info.host)))
        return NULL;

    memcpy(ip, ip_buf, sizeof(ip));
    if (!ip_buf) { free(ip_buf); ip_buf = NULL; }

    int sockfd = -1;
    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))) { ret = -1; goto _exit; }

    // tcp client
    uint16_t port = 0;
    sscanf(url_info.port, "%d", &port);

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(server_addr.sin_zero), 0, sizeof(server_addr.sin_zero));

    if (-1 == connect(sockfd, (struct sockadd *)&server_addr, sizeof(struct sockaddr))) { ret = -1; goto _exit; }

    char *request = NULL;
    request = create_http_get_request(url_info.path, url_info.host, url_info.port);
    if (!request) { ret = -1; goto _exit; }

    size_t req_header_len = strlen(request);
    size_t write_to_net_len = send(sockfd, request, req_header_len, 0);

    if (req_header_len != write_to_net_len) { DEBUG_MSG();
        ret = -1;
        free(request);
        request = NULL;
        goto _exit;
    }

    free(request);
    request = NULL;

    char response[BUFF_SIZE] = {0};

    ssize_t bytes_received = 0;
    size_t header_length = 0;
    size_t content_length = 0;
    uint8_t *http_data = NULL;
    size_t cur_cpy_len = 0;
    size_t total_len = 0;
    uint8_t need_handle_rsp_header = 1;
    uint8_t need_save_resp_data = 0;
    size_t offset = 0;

    while (1) {
        // 接收http响应
        bytes_received = recv(sockfd, response, BUFF_SIZE, 0);
        offset += bytes_received;

        if (offset == BUFF_SIZE) {
            if (need_handle_rsp_header) {
                ret = handle_http_response_header(response, &header_length, &content_length);
                if (ret == 0) { ret = -1; break;}

                http_data = malloc(content_length + 1);
                if (http_data == NULL) { ret = -1; break; }

                need_handle_rsp_header = 0;
                need_save_resp_data = 1;
                bytes_received = 0;
                offset = 0;
                cur_cpy_len += (BUFF_SIZE - header_length); 
                memcpy(http_data, response + header_length, cur_cpy_len);
                print_download_process(content_length, cur_cpy_len);
            } else if (need_save_resp_data) {
                memcpy(http_data + cur_cpy_len, response, bytes_received);
                cur_cpy_len += bytes_received;
                offset = 0;
                print_download_process(content_length, cur_cpy_len);
            } else {
                break;
            }
        } else if (offset < BUFF_SIZE) { 
            // HTTP 传输完成
            if (need_save_resp_data && offset + cur_cpy_len == content_length) {
                memcpy(http_data + cur_cpy_len, response, offset);
                cur_cpy_len += offset;
                print_download_process(content_length, cur_cpy_len);

                char path[64] = {0};
                snprintf(path, sizeof(path), "/home/rakari/github/m_C/http_project/bin/%s", url_info.path);
                save_file_to_local(path, http_data, cur_cpy_len);
                free(http_data);
                http_data = NULL;
                break;
            }
        } else {
            break;
        }
    }

_exit:
    if (sockfd >= 0) close(sockfd);
    return ret;
}
