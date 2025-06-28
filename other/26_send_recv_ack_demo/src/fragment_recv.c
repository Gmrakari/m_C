#include "fragment_recv.h"
#include <stdlib.h>

void init_package_info(package_msg_t *package_info) {
    package_info->in_used = 0;
    package_info->total_len = 0;
    package_info->received_len = 0;
    package_info->data = NULL;
    package_info->last_frag_id = 0;
    package_info->frag_count = 0;
}

int fragment_receive(uint8_t *data, uint32_t len, uint8_t *last_frag, 
                   int *total_len, char **out, int *olen, package_msg_t *package_info) {
    fragment_t *fragment = (fragment_t *)data;

    if (!data || len < sizeof(fragment_t) - sizeof(fragment->frag_data)) {
        printf("[%s][%d]Invalid fragment data\n", __func__, __LINE__);
        return -1;
    }

    // 检查是否是第一个分片
    if (fragment->frag_seq_id == 1) {
        if (package_info->data) {
            free(package_info->data);
        }
        package_info->total_len = fragment->msg_len;
        package_info->received_len = 0;
        package_info->data = malloc(package_info->total_len);
        if (!package_info->data) {
            printf("[%s][%d]Memory allocation failed\n", __func__, __LINE__);
            return -1;
        }
        package_info->last_frag_id = 0;
        package_info->frag_count = 0;
        package_info->in_used = 1;
    }

    printf("[%s][%d]fragment->frag_seq_id: %d\r\n", __func__, __LINE__, fragment->frag_seq_id);
    printf("[%s][%d]package_info->last_frag_id: %d\r\n", __func__, __LINE__, package_info->last_frag_id);

    // 检查分片顺序
    if (fragment->frag_seq_id != package_info->last_frag_id + 1) {
        printf("[%s][%d] Fragment sequence error: expected %d, got %d\n", 
              __func__, __LINE__, package_info->last_frag_id + 1, fragment->frag_seq_id);
        return -1;
    }

    // 检查数据长度
    if (package_info->received_len + fragment->frag_len > package_info->total_len) {
        printf("[%s][%d] Fragment length overflow\n", __func__, __LINE__);
        return -1;
    }

    // 拷贝数据
    memcpy(package_info->data + package_info->received_len, 
          fragment->frag_data, fragment->frag_len);
    
    // 更新状态
    package_info->received_len += fragment->frag_len;
    package_info->last_frag_id = fragment->frag_seq_id;
    package_info->frag_count++;

    // 检查是否是最后一个分片
    if (fragment->last_frag) {
        if (package_info->received_len != package_info->total_len) {
            printf("[%s][%d] Incomplete message\n", __func__,__LINE__);
            return -1;
        }

        *out = (char *)package_info->data;
        *olen = package_info->total_len;
        *last_frag = 1;
        *total_len = package_info->total_len;

        package_info->in_used = 0;
        return 0;
    }

    return -2;
}