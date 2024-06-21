#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <time.h>


#define HOST_IP_INFO "183.2.172.42"
#define HOST_PORT    (80)

static int _http_create_fd(const char *ip, const int port, int *ofd)
{
    int ret = 0;

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        printf("[%s][%d]socket create err!\r\n", __func__, __LINE__);
        return -1;
    }

    struct sockaddr_in cli_addr = {
        .sin_addr.s_addr = inet_addr(ip),
        .sin_port = htons(port),
        .sin_family = AF_INET,
        .sin_zero = {0},
    };

    ret = connect(sockfd, (const struct sockaddr*)&cli_addr, sizeof(struct sockaddr_in));
    if (ret != 0) {
        printf("[%s][%d]connect err!\r\n", __func__, __LINE__);
        close(sockfd);
        return ret;
    }

    *ofd = sockfd;

    return ret;
}

static int _gen_http_get_request(const char *host, const int port, char **out, int *olen)
{
    if (!host) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    int len = snprintf(NULL, 0, "GET / HTTP/1.1\r\n"
                                "Host:%s:%d\r\n"
                                "Accept-Type:*/*\r\n"
                                "\r\n",
                                host, port) + 1;
    
    char *request = malloc(len);
    if (!request) {
        printf("[%s][%d]request malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    int request_len = 0;
    request_len = snprintf(request, len, "GET / HTTP/1.1\r\n"
                                "Host:%s:%d\r\n"
                                "Accept-Type:*/*\r\n"
                                "\r\n",
                                host, port);
    if (request_len != len - 1) {
        printf("[%s][%d]snprintf err!\r\n", __func__, __LINE__);
        if (request) {
            free(request);
            request = NULL;
        }
    }

    *out = request;
    *olen = request_len;

    return ret;
}

static int _get_http_response_header_len(const char *data, int *olen)
{
    if (!data || !olen) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    char *header_len_ptr = strstr(data, "\r\n\r\n");
    if (header_len_ptr == NULL) {
        printf("[%s][%d]get header len ptr err!\r\n", __func__, __LINE__);
        return -1;
    }

    *olen = header_len_ptr - data + 4;

    return 0;
}

static int _get_http_response_content_len(const char *data, int *olen)
{
    if (!data || !olen) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    char *content_len_ptr = strstr(data, "Content-Length:");
    if (content_len_ptr == NULL) {
        printf("[%s][%d]get content len err!\r\n", __func__, __LINE__);
        return -1;
    }

    *olen = content_len_ptr - data + strlen("Content-Length:");

    return 0;
}

static int _get_http_response_date_len(const char *data, int *olen)
{
    if (!data || !olen) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    char *date_len_ptr = strstr(data, "Date:");
    if (date_len_ptr == NULL) {
        printf("[%s][%d]get date len err!\r\n", __func__, __LINE__);
        return -1;
    }

    *olen = date_len_ptr - data;

    return 0;
}

static int _get_http_response_date(const char *data, char **date)
{
    if (!data) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    int date_len = 0;
    ret = _get_http_response_date_len(data, &date_len);
    if (ret != 0) {
        printf("[%s][%d]_get_http_response_date_len err!\r\n", __func__, __LINE__);
        return -1;
    }

    char *date_res_ptr = strstr(data, "Date:");
    if (date_res_ptr == NULL) {
        printf("[%s][%d]get date res ptr err!\r\n", __func__, __LINE__);
        return -1;
    }

    char *date_str = malloc(date_len);
    if (!date_str) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    strncpy(date_str, date_res_ptr, date_len);

    *date = date_str;

    return 0;
}

static int _remove_prefix(const char *src, const char *prefix, char *result, int result_len)
{
    if (!src || !prefix || !result) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }

    int ret = 0;

    const char *start = strstr(src, prefix);
    if (start != NULL) {
        start += strlen(prefix);
        while (*start == ' ')
            start++;
        
        size_t length = strlen(start);
        if (length >= result_len) {
            printf("[%s][%d]result buffer too small!\r\n", __func__, __LINE__);
            return -1;
        }

        strncpy(result, start, result_len - 1);
        result[result_len - 1] = '\0';
    } else {
        size_t length = strlen(src);
        if (length >= result_len) {
            printf("[%s][%d]result buffer too small!\r\n", __func__, __LINE__);
            return -1;
        }

        strcpy(result, src);
    }
    return ret;
}
static int _get_timestamp_from_date_string(const char *date, long *timestamp)
{
    if (!date || !timestamp) {
        printf("[%s][%d]invalid param!\r\n", __func__, __LINE__);
        return -1;
    }
printf("[%s][%d]\r\n", __func__, __LINE__);
    struct tm tm;
    memset(&tm, 0x00, sizeof(struct tm));
printf("[%s][%d]\r\n", __func__, __LINE__);
    char *result = NULL;
    result = strptime(date, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    if (result == NULL) {
        printf("[%s][%d]strptime err!\r\n", __func__, __LINE__);
        return -1;
    }
printf("[%s][%d]\r\n", __func__, __LINE__);
    time_t ts = mktime(&tm);
    if (ts == -1) {
        printf("[%s][%d]mktime err!\r\n", __func__, __LINE__);
        return -1;
    }
printf("[%s][%d]\r\n", __func__, __LINE__);
    *timestamp = (long)ts;
printf("[%s][%d]\r\n", __func__, __LINE__);
    return 0;
}

static int _get_ntp_ts()
{
    int ret = 0;

    const char *ip = HOST_IP_INFO;
    const int port = HOST_PORT;

    int fd = 0;
    ret = _http_create_fd(ip, port, &fd);
    if (ret != 0) {
        printf("[%s][%d]_http_create_fd err!\r\n", __func__, __LINE__);
        return -1;
    }

    char *request = NULL;
    int request_len = 0;
    ret = _gen_http_get_request(ip, port, &request, &request_len);
    if (ret != 0) {
        printf("[%s][%d]_gen_http_get_request err!\r\n", __func__, __LINE__);
        if (request) {
            free(request);
            request = NULL;
        }
        return -1;
    }

    ret = send(fd, request, request_len, MSG_NOSIGNAL);
    if (ret == -1 || ret != request_len) {
        printf("[%s][%d]send err!\r\n", __func__, __LINE__);
        if (request) {
            free(request);
            request = NULL;
        }
        return -1;
    }

    if (request) {
        free(request);
        request = NULL;
    }

    char recv_buff[1024] = {0};

    int offset = 0;
    int cur_recv_bytes;

    unsigned char need_parse_header = 1;

    int header_len = 0;

    cur_recv_bytes = recv(fd, &recv_buff, sizeof(recv_buff), 0);
    offset += cur_recv_bytes;

    if (fd >= 0) {
        close(fd);
    }

    ret = _get_http_response_header_len(recv_buff, &header_len);
    if (ret != 0) {
        printf("[%s][%d]_get_http_response_header_len err!\r\n", __func__, __LINE__);
        return -1;
    }

    char *header = malloc(header_len + 1);
    if (!header) {
        printf("[%s][%d]malloc err!\r\n", __func__, __LINE__);
        return -1;
    }

    memcpy(header, &recv_buff, header_len);

    char *date = NULL;
    ret = _get_http_response_date(header, &date);
    if (ret != 0) {
        printf("[%s][%d]_get_http_response_date err!\r\n", __func__, __LINE__);
        if (header) {
            free(header);
            header = NULL;
        }

        if (date) {
            free(date);
            date = NULL;
        }
        return -1;
    }

    if (header) {
        free(header);
        header = NULL;
    }

    char fmt_date[64] = {0};

    char prefix[] = "Date:";
    ret = _remove_prefix(date, "Date:", fmt_date, sizeof(fmt_date));
    if (ret != 0) {
        printf("[%s][%d]_remove_prefix err!\r\n", __func__, __LINE__);
        if (date) {
            free(date);
            date = NULL;
        }

        return -1;
    }

    printf("[%s][%d]fmt_date:%s\r\n", __func__, __LINE__, fmt_date);

    if (date) {
        free(date);
        date = NULL;
    }

    long ts = 0;
    ret = _get_timestamp_from_date_string(fmt_date, &ts);
    if (ret != 0) {
        printf("[%s][%d]_get_timestamp_from_date_string err!\r\n", __func__, __LINE__);
        return -1;
    }

    printf("[%s][%d]ts: %ld\r\n", __func__, __LINE__, ts);

    return ret;
}

int main()
{
    int ret = 0;

#if 1
    ret = _get_ntp_ts();

    if (ret != 0) {
        printf("[%s][%d]_get_ntp_ts err!\r\n", __func__, __LINE__);
        return ret;
    }
#endif

#if 0
    char buff[] = "Date: Fri, 21 Jun 2024 08:20:32 GMT";
    printf("[%s][%d]%s\r\n", __func__, __LINE__, buff);
    printf("[%s][%d]%d\r\n", __func__, __LINE__, sizeof(buff));
#endif
    return ret;
}

// usage
// gcc -g -o a.out 7_http_get_time.c
// valgrind --leak-check=full --show-leak-kinds=all ./a.out