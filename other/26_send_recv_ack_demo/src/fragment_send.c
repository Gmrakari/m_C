#include "fragment_send.h"
#include "common.h"

int fragment_send(uint8_t *message, uint16_t msg_len, uint8_t cmd, send_callback_t callback) {
    typedef struct {
        uint32_t len;
        uint8_t data[500]; // len + data_len = 504
    } data_buffer_t;

    if (!message || !msg_len || !callback) {
        printf("[%s] Invalid parameters\n", __func__);
        return -1;
    }

    data_buffer_t buffer;
    fragment_t *fragment = (fragment_t *)&buffer.data[1];
    uint8_t *msg_pos = message;
    uint16_t remaining_len = msg_len;
    uint16_t frag_id = 1;
    int ret = 0;

    while (remaining_len > 0) {
        // 设置分片头
        fragment->msg_type = 0xFF;
        fragment->msg_len = msg_len;
        fragment->frag_seq_id = frag_id;

        if (remaining_len > MAX_FRAGMENT_SIZE) {
            fragment->last_frag = 0;
            fragment->frag_len = MAX_FRAGMENT_SIZE;
        } else {
            fragment->last_frag = 1;
            fragment->frag_len = remaining_len;
        }

        // 拷贝数据
        memcpy(fragment->frag_data, msg_pos, fragment->frag_len);

        // 计算校验和 (简化版，实际应使用CRC16等)
        fragment->frag_data[fragment->frag_len] = 0;
        fragment->frag_data[fragment->frag_len+1] = 0;

        // 设置缓冲区
        buffer.data[0] = cmd;
        buffer.len = 1 + sizeof(fragment_t) - sizeof(fragment->frag_data) + fragment->frag_len + FRAGMENT_CHKSUM_SIZE;

        print_data("buffer", (uint8_t *)&buffer, sizeof(data_buffer_t));

        // 调用发送回调
        ret = callback((uint8_t *)&buffer, buffer.len + sizeof(buffer.len));
        if (ret != 0) {printf("[%s][%d]\r\n", __func__, __LINE__);
            break;
        }

        // 更新状态
        remaining_len -= fragment->frag_len;
        msg_pos += fragment->frag_len;
        frag_id++;
    }

    return ret;
}