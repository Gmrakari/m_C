#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义事件类型
typedef enum {
    RINO_AIGC_ASR_SEND_EVENT = 0,
    RINO_AIGC_ASR_RECV_EVENT,
    RINO_AIGC_CHAT_SEND_EVENT,
    RINO_AIGC_CHAT_RECV_EVENT,
    RINO_AIGC_TTS_SEND_EVENT,
    RINO_AIGC_TTS_RECV_EVENT,
    RINO_AIGC_MAX_EVENT,
} rino_aigc_event_t;

// 定义音频事件类型
typedef enum {
    RINO_AUDIO_MIC_RECORD_EVENT = 0,
    RINO_AUDIO_SPK_PLAY_EVENT,
    RINO_AUDIO_MAX_EVENT,
} rino_audio_event_type_t;

#define RINO_EVENT_MAX_NUM (RINO_AIGC_MAX_EVENT + RINO_AUDIO_MAX_EVENT)

// 定义事件联合类型
typedef union {
    rino_aigc_event_t aigc_event;
    rino_audio_event_type_t audio_event;
} rino_event_type_t;

// 定义事件信息结构体
typedef struct {
    rino_event_type_t event_type;
} rino_event_info_t;

// 定义事件处理函数类型
typedef void (*event_cb_func)(rino_event_info_t *);

// 定义事件处理器结构体
typedef struct {
    event_cb_func cb_func[RINO_EVENT_MAX_NUM + 1];
} event_hdl_t;

// 初始化事件处理器
void init_event_handler(event_hdl_t *hdl) {
    for (int i = 0; i <= RINO_EVENT_MAX_NUM; ++i) {
        hdl->cb_func[i] = NULL;
    }
}

// 注册事件处理函数
void register_event_handler(event_hdl_t *hdl, rino_event_type_t event_type, event_cb_func handler_func) {
    if (event_type.aigc_event >= 0 && event_type.aigc_event <= RINO_EVENT_MAX_NUM) {
        hdl->cb_func[event_type.aigc_event] = handler_func;
    }
}

// 触发事件处理
#if 0
void trigger_event(event_hdl_t *hdl, rino_event_info_t *event_info) {
    rino_event_type_t event_type = event_info->event_type;
    if (event_type.aigc_event >= 0 && event_type.aigc_event <= RINO_EVENT_MAX_NUM) {
        event_cb_func handler_func = hdl->cb_func[event_type.aigc_event];
        if (handler_func != NULL) {
            handler_func(event_info);
        } else {
            printf("No hdl registered for this event\n");
        }
    } else {
        printf("Invalid event type\n");
    }
}
#endif

void trigger_event(event_hdl_t *hdl, rino_event_info_t *info, void *event_data) {
    printf("[%s][%d]info->event_type.aigc_event:%d\r\n", info->event_type.aigc_event);
    if (info->event_type.aigc_event >= 0 && info->event_type.aigc_event < RINO_AIGC_MAX_EVENT) {
        event_cb_func handler_func = hdl->cb_func[info->event_type.aigc_event];
        if (handler_func != NULL) {
            handler_func(event_data);
        } else {
            printf("No handler registered for this event\n");
        }
        return ;
    }

    if (info->event_type.audio_event >= 0 && info->event_type.audio_event < RINO_AUDIO_MAX_EVENT) {
        event_cb_func handler_func = hdl->cb_func[RINO_AIGC_MAX_EVENT + info->event_type.audio_event];
        if (handler_func != NULL) {
            handler_func(event_data);
        } else {
            printf("No handler registered for this event\n");
        }
        return ;
    }
}

// 示例事件处理函数
void asr_send_event_hdl_func(rino_event_info_t *event_info) {
    printf("ASR send event handled\n");
}

void asr_recv_event_hdl_func(rino_event_info_t *event) {
    printf("ASR Receive Event Trigg-ered\n");
}

void chat_send_event_hdl_func(rino_event_info_t *event) {
    printf("Chat Send Event Triggered\n");
}

void chat_recv_event_hdl_func(rino_event_info_t *event) {
    printf("Chat Receive Event Triggered\n");
}

void tts_send_event_hdl_func(rino_event_info_t *event) {
    printf("TTS Send Event Triggered\n");
}

void tts_recv_event_hdl_func(rino_event_info_t *event) {
    printf("TTS Receive Event Triggered\n");
}

void audio_mic_event_hdl_func(rino_event_info_t *event) {
    printf("Audio record Event Triggered\n");
}

void audio_play_event_hdl_func(rino_event_info_t *event) {
    printf("Audio Play Event Triggered\n");
}

// void rino_event_register_add(event_hdl_t *hdl, rino_event_info_t *info, event_cb_func *event_cb_func_hdl)
// {
//     // 获取事件类型
//     rino_event_type_t event_type;
//     // 将事件处理函数添加到事件处理器中
//     // hdl->cb_func[event_type] = event_cb_func_hdl;

//     for (int i = 0; i < RINO_EVENT_MAX_NUM; i++) {
//         event_type = info[i].event_type;
//         hdl->cb_func[event_type] = event_cb_func_hdl[i];
//     }
// }

void rino_event_register_add(event_hdl_t *hdl, event_cb_func *event_cb_func_hdl, int num_hdls)
{
    for (int i = 0; i < num_hdls; i++) {
        hdl->cb_func[i] = event_cb_func_hdl[i];
    }
}

int main() {
    // 初始化事件处理器
    event_hdl_t hdl;
    init_event_handler(&hdl);

    rino_event_info_t *info = malloc(sizeof(rino_event_info_t));
    info->event_type.aigc_event = RINO_AIGC_ASR_SEND_EVENT;

    int max_event_num = RINO_AIGC_MAX_EVENT + RINO_AUDIO_MAX_EVENT;

    // event_cb_func *event_cb_func_hdl = malloc(sizeof(event_cb_func) * max_event_num);

    // event_cb_func event_cb_func_hdl[max_event_num] = {
    //     audio_mic_event_hdl_func,
    //     asr_send_event_hdl_func,
    //     asr_recv_event_hdl_func,
    //     chat_send_event_hdl_func,
    //     chat_recv_event_hdl_func,
    //     tts_send_event_hdl_func,
    //     tts_recv_event_hdl_func,
    //     audio_play_event_hdl_func
    // };

    event_cb_func asr_event_handlers[] = {
        audio_mic_event_hdl_func,
        asr_send_event_hdl_func,
        asr_recv_event_hdl_func,
        chat_send_event_hdl_func,
        chat_recv_event_hdl_func,
        tts_send_event_hdl_func,
        tts_recv_event_hdl_func,
        audio_play_event_hdl_func
    };

    rino_event_register_add(&hdl, asr_event_handlers, max_event_num);

    // // 创建并触发事件
    rino_event_info_t event;
    event.event_type.aigc_event= RINO_AIGC_ASR_SEND_EVENT;
    // event.event_type.aigc_event= RINO_AIGC_CHAT_RECV_EVENT + 1;

    #if 0
    trigger_event(&hdl, &event);
    #endif

    trigger_event(&hdl, &event, NULL);

    return 0;
}
