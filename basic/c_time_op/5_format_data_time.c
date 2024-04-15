#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char* format_time(time_t raw_time) {
    int buffer_len = 64;
    char *buffer = (char*)malloc(buffer_len);
    if (!buffer) {
      printf("[%s][%d]\r\n", __func__, __LINE__);
      return NULL;
    }

    memset(buffer, 0x00, buffer_len);
    struct tm* time_info;
    time_info = gmtime(&raw_time);
    strftime(buffer, buffer_len - 1, "%a, %d %b %Y %H:%M:%S GMT", time_info);

    return buffer;
}

char *time_to_string(time_t time) {
  struct tm *tm = localtime(&time);

  // 定义时间格式化字符串
//   char buf[128];
  char *buf = malloc(128);
  sprintf(buf, "%d-%d-%d %d:%d:%d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
          tm->tm_hour, tm->tm_min, tm->tm_sec);

  return buf;
}

int main() {
    // time_t raw_time = 26;
    time_t cur_time = time(NULL);
    printf("time:%ld\r\n", cur_time);

    char *ptr = malloc(24);
    if (!ptr) {
        free(ptr);
        ptr = NULL;
    }
    memset(ptr, 0, 24);

    char str_time_buf[] = "1711185064";
    snprintf(ptr, 24, "%ld", cur_time);
    printf("ptr:%s\r\n", ptr);
    if (ptr) {
        free(ptr);
        ptr = NULL;
    }

    char *str = time_to_string(cur_time);
    printf("str:%s\r\n", str);
    if (str) {
        free(str);
        str = NULL;
    }

    char* formatted_time = format_time(cur_time);
    printf("fmt time: %s\n", formatted_time);
    if (formatted_time) {
      free(formatted_time);
      formatted_time = NULL;
    }

    return 0;
}
